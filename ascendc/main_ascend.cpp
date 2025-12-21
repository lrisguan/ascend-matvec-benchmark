#include <acl/acl.h>
#include <chrono>
#include <iostream>
#include "matvec_kernels/aclrtlaunch_matvec_kernel.h"

constexpr int M = 2048;
constexpr int N = 2048;

int main()
{
  aclError ret = aclInit(nullptr);
  if (ret != ACL_ERROR_NONE) {
    std::cerr << "aclInit failed, ret = " << ret << std::endl;
    return 1;
  }

  int32_t deviceId = 0;
  ret = aclrtSetDevice(deviceId);
  if (ret != ACL_ERROR_NONE) {
    std::cerr << "aclrtSetDevice failed, ret = " << ret << std::endl;
    aclFinalize();
    return 1;
  }

  aclrtStream stream = nullptr;
  ret = aclrtCreateStream(&stream);
  if (ret != ACL_ERROR_NONE) {
    std::cerr << "aclrtCreateStream failed, ret = " << ret << std::endl;
    aclrtResetDevice(deviceId);
    aclFinalize();
    return 1;
  }

  size_t aSize = static_cast<size_t>(M) * static_cast<size_t>(N) * sizeof(float);
  size_t bSize = static_cast<size_t>(N) * sizeof(int);
  size_t cSize = static_cast<size_t>(M) * sizeof(int);

  void* A = nullptr;
  void* B = nullptr;
  void* C = nullptr;

  ret = aclrtMalloc(&A, aSize, ACL_MEM_MALLOC_HUGE_FIRST);
  ret |= aclrtMalloc(&B, bSize, ACL_MEM_MALLOC_HUGE_FIRST);
  ret |= aclrtMalloc(&C, cSize, ACL_MEM_MALLOC_HUGE_FIRST);
  if (ret != ACL_ERROR_NONE) {
    std::cerr << "aclrtMalloc failed, ret = " << ret << std::endl;
    aclrtDestroyStream(stream);
    aclrtResetDevice(deviceId);
    aclFinalize();
    return 1;
  }

  // Launch the MatVec kernel for warm-up
  uint32_t blockDim = (M + 15) / 16;
  uint32_t launchRet = aclrtlaunch_matvec_kernel(blockDim, stream, A, B, C);
  if (launchRet != 0) {
    std::cerr << "aclrtlaunch_matvec_kernel failed, ret = " << launchRet << std::endl;
  }
  aclrtSynchronizeStream(stream);

  // Measure execution time over 10,000 iterationss
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 10000; ++i) {
    launchRet = aclrtlaunch_matvec_kernel(blockDim, stream, A, B, C);
    if (launchRet != 0) {
      std::cerr << "aclrtlaunch_matvec_kernel failed, ret = " << launchRet << std::endl;
    }
  }
  aclrtSynchronizeStream(stream);
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "AscendC MatVec Average Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() / 10000
            << " ms" << std::endl;

  aclrtFree(A);
  aclrtFree(B);
  aclrtFree(C);

  aclrtDestroyStream(stream);
  aclrtResetDevice(deviceId);
  aclFinalize();
  return 0;
}
