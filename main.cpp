#include <iostream>
#include <omp.h>
#include <cmath>
#include <iomanip>

// Функция для интегрирования (например, sin(x))
double f(double x) {
    return sin(x);
}

// Численное интегрирование методом трапеций в диапазоне [a, b] с n шагами
double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    sum += (f(a) + f(b)) / 2.0;
    return sum * h;
}

int main() {
    double a = 0.0;  // Начало диапазона
    double b = 3.14159265359;  // Конец диапазона (π)
    int n = 1000000;  // Количество шагов
    int num_threads = 4;

    // Устанавливаем количество потоков
    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();
    double result = integrate(a, b, n);
    double end_time = omp_get_wtime();

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
#pragma omp critical
        {
            std::cout << "Thread " << thread_id << " finished its part of the computation." << std::endl;
        }
    }

    // Выводим результат интегрирования
    std::cout << "Integral result: " << std::fixed << std::setprecision(6) << result << std::endl;
    std::cout << "Computation time: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}