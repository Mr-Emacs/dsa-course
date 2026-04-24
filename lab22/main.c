#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void linear_loop(int n) {
    volatile int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
}

void quadratic_loop(int n) {
    volatile long long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += i * j;
        }
    }
}

void log_loop(int n) {
    volatile int sum = 0;
    for (int i = 1; i < n; i *= 2) {
        sum += i;
    }
}

int main() {
    int test_sizes[] = {10, 100, 10000};
    int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
    LARGE_INTEGER frequency, start, end;
    double time_taken;

    QueryPerformanceFrequency(&frequency);

    printf("Time Complexity Analysis\n");
    printf("------------------------\n\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = test_sizes[s];
        printf("N = %d\n", n);
        printf("----------------------------------------\n");

        QueryPerformanceCounter(&start);
        linear_loop(n);
        QueryPerformanceCounter(&end);
        time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        printf("O(n)     : %.9f seconds\n", time_taken);

        QueryPerformanceCounter(&start);
        quadratic_loop(n);
        QueryPerformanceCounter(&end);
        time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        printf("O(n^2)   : %.9f seconds\n", time_taken);

        QueryPerformanceCounter(&start);
        log_loop(n);
        QueryPerformanceCounter(&end);
        time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        printf("O(log n) : %.9f seconds\n\n", time_taken);
    }

    return 0;
}
