cmake_minimum_required(VERSION 3.16)
project(MatVecBenchmark C CXX)

# ===== 全局配置 =====
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOC_VERSION "Ascend310P3" CACHE STRING "SoC version, e.g. Ascend310P3")
set(ASCEND_CANN_PACKAGE_PATH "/usr/local/Ascend/ascend-toolkit/latest" CACHE PATH "Ascend CANN toolkit root")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type Release/Debug" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/out" CACHE PATH "Install prefix for samples" FORCE)

option(BUILD_CPU "Build CPU sample" ON)
option(BUILD_ASCENDC "Build AscendC sample" ON)

if(BUILD_CPU)
	add_subdirectory(cpu)
endif()

if(BUILD_ASCENDC)
	add_subdirectory(ascendc)
endif()
