#include <stdio.h>
#include <time.h>

// 반복문을 사용하여 거듭제곱을 계산하는 함수
// a: 밑
// b: 지수
double power_iter(double a, double b);

// 재귀적으로 거듭제곱을 계산하는 함수
// a: 밑
// b: 지수
double power_rec(double a, double b);


//분할정복방식으로 재귀적으로 거듭제곱을 계산하는 함수
// a: 밑
// b: 지수
double power_rec2(double a, int b);

int main(void) {
    clock_t start, stop;

    start = clock();
    double result_iter = power_iter(13, 21); // 반복문을 사용하여 거듭제곱 계산
    stop = clock();
    printf(" %.0f,   시간: %f 초\n", result_iter, (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    double result_rec = power_rec(13, 21); // 재귀적으로 거듭제곱 계산
    stop = clock();
    printf("%.0f,   시간: %f 초\n", result_rec, (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    double result_rec2 = power_rec2(13, 21); // 분할정복방식으로 재귀적으로 거듭제곱 계산
    stop = clock();
    printf("%.0f,   시간: %f 초\n", result_rec2, (double)(stop - start) / CLOCKS_PER_SEC);

    return 0;
}

// 반복문을 사용하여 거듭제곱을 계산하는 함수
double power_iter(double a, double b) {
    double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

// 재귀적으로 거듭제곱을 계산하는 함수
double power_rec(double a, double b) {
    if (b == 0) {
        return 1;
    }
    else {
        return a * power_rec(a, b - 1);
    }
}

//분할정복방식으로 재귀적으로 거듭제곱으로 계산하는 함수
double power_rec2(double a, int b) {
    if (b == 0)
        return 1;
    double half = power_rec2(a, b / 2);
    if (b % 2 == 0)
        return half * half; // b가 짝수인 경우
    else
        return a * half * half; // b가 홀수인 경우
}