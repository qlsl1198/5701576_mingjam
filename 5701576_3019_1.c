#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 반복문을 사용하여 팩토리얼을 계산하는 함수
// a: 계산할 수
long factorial_iter(int a);

// 재귀적으로 팩토리얼을 계산하는 함수
// a: 계산할 수
long factorial_rec(int a);

int main(void) {
    clock_t start, stop;

    // 반복문을 사용하여 팩토리얼 계산
    start = clock();
    long result_iter = factorial_iter(20);
    stop = clock();
    printf(" %ld, Elapsed time: %.6f seconds\n", result_iter, (double)(stop - start) / CLOCKS_PER_SEC);

    // 재귀적으로 팩토리얼 계산
    start = clock();
    long result_rec = factorial_rec(20);
    stop = clock();
    printf("%ld, Elapsed time: %.6f seconds\n", result_rec, (double)(stop - start) / CLOCKS_PER_SEC);

    return 0;
}

// 반복문을 사용하여 팩토리얼을 계산하는 함수
long factorial_iter(int a) {
    long i, fac = 1;
    // 반복문을 통해 팩토리얼 계산
    for (i = 2; i <= a; i++) {
        fac *= i;
    }
    return fac;
}

// 재귀적으로 팩토리얼을 계산하는 함수
long factorial_rec(int a) {
    // 종료 조건: a가 1 이하일 때 1 반환
    if (a <= 1) {
        return 1;
    }
    else {
        // 재귀 호출을 통해 팩토리얼 계산
        return a * factorial_rec(a - 1);
    }
}
