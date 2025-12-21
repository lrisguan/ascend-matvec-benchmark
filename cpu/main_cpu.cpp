#include <vector>
#include <chrono>
#include <iostream>

constexpr int M = 2048;
constexpr int N = 2048;

inline void matvec(const std::vector<float>& A, const std::vector<float>& B, std::vector<float>& C) {
  for (int i = 0; i < M; ++i) {
    float sum = 0;
    for (int j = 0; j < N; ++j) {
      sum += A[i * N + j] * B[j];
    }
    C[i] = sum;
  }
}

int main() {
  std::vector<float> A(M * N, 1);
  std::vector<float> B(N, 1);
  std::vector<float> C(M, 0);

  // warm-up
  matvec(A, B, C);
  
  auto start = std::chrono::high_resolution_clock::now();

  // Perform matrix-vector multiplication 10000 times
  for (int k = 0; k < 10000; ++k) {
    matvec(A, B, C);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "CPU MatVec Average Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() / 10000
            << " ms\n";

  return 0;
}
