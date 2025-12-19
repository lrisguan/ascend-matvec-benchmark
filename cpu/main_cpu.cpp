#include <vector>
#include <chrono>
#include <iostream>

constexpr int M = 2048;
constexpr int N = 2048;

int main() {
    std::vector<int> A(M * N, 1);
    std::vector<int> B(N, 1);
    std::vector<int> C(M, 0);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < M; ++i) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            sum += A[i * N + j] * B[j];
        }
        C[i] = sum;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "CPU Time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    return 0;
}
