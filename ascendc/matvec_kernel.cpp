#include "kernel_operator.h"

using namespace AscendC;

constexpr int M = 2048;
constexpr int N = 2048;

class MatVecKernel {
private:
  GlobalTensor<int> aGM;
  GlobalTensor<int> bGM;
  GlobalTensor<int> cGM;

public:
  __aicore__ inline MatVecKernel() {}

  __aicore__ inline void Init(GM_ADDR A, GM_ADDR B, GM_ADDR C) {
    aGM.SetGlobalBuffer(reinterpret_cast<__gm__ int*>(A));
    bGM.SetGlobalBuffer(reinterpret_cast<__gm__ int*>(B));
    cGM.SetGlobalBuffer(reinterpret_cast<__gm__ int*>(C));
  }

  __aicore__ inline void Process() {
    int row = GetBlockIdx();
    if (row >= M) {
        return;
    }

    int sum = 0;

    // 直接 GM 访存（baseline / correctness）
    for (int j = 0; j < N; ++j) {
        sum += aGM(row * N + j) * bGM(j);
    }

    cGM(row) = sum;
  }
};

extern "C" __global__ __aicore__
void matvec_kernel(GM_ADDR A, GM_ADDR B, GM_ADDR C) {
  MatVecKernel kernel;
  kernel.Init(A, B, C);
  kernel.Process();
}
