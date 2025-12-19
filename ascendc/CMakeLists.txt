# ===== 基本信息 =====
set(SOC_VERSION "${SOC_VERSION}" CACHE STRING "SoC version" FORCE)
set(ASCEND_CANN_PACKAGE_PATH "${ASCEND_CANN_PACKAGE_PATH}" CACHE PATH "Ascend toolkit root" FORCE)

# ===== 定位 ascendc cmake =====
if(EXISTS ${ASCEND_CANN_PACKAGE_PATH}/tools/tikcpp/ascendc_kernel_cmake)
    set(ASCENDC_CMAKE_DIR ${ASCEND_CANN_PACKAGE_PATH}/tools/tikcpp/ascendc_kernel_cmake)
elseif(EXISTS ${ASCEND_CANN_PACKAGE_PATH}/compiler/tikcpp/ascendc_kernel_cmake)
    set(ASCENDC_CMAKE_DIR ${ASCEND_CANN_PACKAGE_PATH}/compiler/tikcpp/ascendc_kernel_cmake)
elseif(EXISTS ${ASCEND_CANN_PACKAGE_PATH}/ascendc_devkit/tikcpp/samples/cmake)
    set(ASCENDC_CMAKE_DIR ${ASCEND_CANN_PACKAGE_PATH}/ascendc_devkit/tikcpp/samples/cmake)
else()
    message(FATAL_ERROR "ascendc_kernel_cmake not found under ${ASCEND_CANN_PACKAGE_PATH}")
endif()

# =====【关键：host 对象路径必须固定】=====
set(KERNELS_HOST_DIR "${CMAKE_CURRENT_BINARY_DIR}/kernels_host_dir" CACHE PATH "" FORCE)
set(KERNELS_HOST_INSTALL_DIR "${KERNELS_HOST_DIR}" CACHE PATH "" FORCE)

# ===== ascendc cmake 内部依赖变量 =====
set(BUILD_MODE "${CMAKE_BUILD_TYPE}" CACHE STRING "" FORCE)
set(DYNAMIC_MODE "off" CACHE STRING "" FORCE)

file(MAKE_DIRECTORY ${KERNELS_HOST_DIR})

# ===== 引入 AscendC 规则 =====
include(${ASCENDC_CMAKE_DIR}/ascendc.cmake)

# ===== Ascend C kernel =====
ascendc_library(matvec_kernels STATIC
    matvec_kernel.cpp
)

# ===== Host 可执行程序 =====
add_executable(matvec_ascend main_ascend.cpp)
target_include_directories(matvec_ascend PRIVATE
    ${CMAKE_BINARY_DIR}/include
)
target_link_libraries(matvec_ascend PRIVATE matvec_kernels)

install(TARGETS matvec_ascend
        RUNTIME DESTINATION bin)
