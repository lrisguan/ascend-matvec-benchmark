#!/bin/bash

CURRENT_DIR=$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)
cd "${CURRENT_DIR}"

SOC_VERSION="Ascend310P3"
BUILD_TYPE="Release"

SHORT=v:,t:
LONG=soc-version:,build-type:
OPTS=$(getopt -a --options ${SHORT} --longoptions ${LONG} -- "$@")
eval set -- "${OPTS}"

while :; do
	case "$1" in
	-v | --soc-version)
		SOC_VERSION="$2"
		shift 2
		;;
	-t | --build-type)
		BUILD_TYPE="$2"
		shift 2
		;;
	--)
		shift
		break
		;;
	*)
		echo "[ERROR] Unexpected option: $1"
		exit 1
		;;
	esac
done

if [ -n "${ASCEND_INSTALL_PATH:-}" ]; then
	_ASCEND_INSTALL_PATH=${ASCEND_INSTALL_PATH}
elif [ -n "${ASCEND_HOME_PATH:-}" ]; then
	_ASCEND_INSTALL_PATH=${ASCEND_HOME_PATH}
elif [ -d "$HOME/Ascend/ascend-toolkit/latest" ]; then
	_ASCEND_INSTALL_PATH=$HOME/Ascend/ascend-toolkit/latest
else
	_ASCEND_INSTALL_PATH=/usr/local/Ascend/ascend-toolkit/latest
fi

if [ ! -f "${_ASCEND_INSTALL_PATH}/bin/setenv.bash" ]; then
	echo "[ERROR] Cannot find Ascend toolkit at ${_ASCEND_INSTALL_PATH}"
	exit 1
fi

echo "Using Ascend toolkit: ${_ASCEND_INSTALL_PATH}"
source "${_ASCEND_INSTALL_PATH}/bin/setenv.bash"

echo "[STEP] Clean build/out ..."
rm -rf build out
mkdir -p build

echo "[STEP] CMake configure ..."
cmake -S "${CURRENT_DIR}" -B build \
	-DSOC_VERSION="${SOC_VERSION}" \
	-DASCEND_CANN_PACKAGE_PATH="${_ASCEND_INSTALL_PATH}" \
	-DCMAKE_BUILD_TYPE="${BUILD_TYPE}"

echo "[STEP] Build CPU matvec_cpu ..."
cmake --build build -j --target matvec_cpu

echo "[STEP] Build AscendC matvec_kernels (first try, may fail) ..."
cmake --build build -j --target matvec_kernels || true

HOST_OBJ_DIR="${CURRENT_DIR}/build/ascendc/matvec_kernels_host_dir"
if [ -d "${HOST_OBJ_DIR}" ]; then
	echo "[STEP] Fix host obj in ${HOST_OBJ_DIR} ..."
	# 将 objects-Release/ 或 objects-Debug/ 下面的 .o 复制到 HOST_OBJ_DIR 根目录
	find "${HOST_OBJ_DIR}" -type f -name "*.o" -path "*/objects-*/*" -exec cp {} "${HOST_OBJ_DIR}/" \; || true
fi

echo "[STEP] Build AscendC matvec_kernels (second try) ..."
cmake --build build -j --target matvec_kernels

echo "[STEP] Build AscendC host matvec_ascend ..."
cmake --build build -j --target matvec_ascend

echo "[STEP] Install to out/ ..."
cmake --install build

echo "[STEP] Run CPU matvec ..."
if [ -x "${CURRENT_DIR}/out/bin/matvec_cpu" ]; then
	"${CURRENT_DIR}/out/bin/matvec_cpu"
else
	echo "[WARN] CPU sample not built."
fi

echo "[STEP] Run AscendC matvec ..."
if [ -x "${CURRENT_DIR}/out/bin/matvec_ascend" ]; then
	"${CURRENT_DIR}/out/bin/matvec_ascend"
else
	echo "[WARN] AscendC sample not built."
fi

echo "MatVec build and run completed."