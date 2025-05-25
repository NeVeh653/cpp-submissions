#include <iostream>
#include <omp.h>

int main() {
    int num_threads = 4;
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
#pragma omp critical
        {
            std::cout << "Thread " << thread_id << " completed its task." << std::endl;
        }
    }

    // Простое вычисление для демонстрации
    int sum = 0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 1000; i++) {
        sum += 1;
    }

    std::cout << "Sum result: " << sum << std::endl;

    return 0;
}