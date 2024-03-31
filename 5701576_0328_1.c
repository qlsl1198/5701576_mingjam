#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEGREE 101 //최고 차수를 101까지로 제한하여 정의

// 다항식을 구조체로 정의
typedef struct polynomial {
    int degree;         // 최고 차수
    float coef[MAX_DEGREE];  // 계수들의 배열
} polynomial;

// 함수 선언
void print_polynomial(polynomial p);
polynomial poly_mult(polynomial A, polynomial B);

// 주어진 두 다항식
polynomial a = { 6, {7,0,0,5,9,0,1} };
polynomial b = { 3, {5,2,1,10} };

int main(void) {
    // 주어진 다항식 출력
    print_polynomial(a);
    print_polynomial(b);
    printf("--------------------------------------------------------------------------------\n");

    // 다항식 곱셈
    polynomial c = poly_mult(a, b);
    print_polynomial(c);

    return 0;
}

// 다항식을 출력하는 함수
void print_polynomial(polynomial p) {
    for (int i = p.degree; i > 0; i--) {
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%3.1f\n", p.coef[p.degree]);
}


// 두 다항식을 곱하는 함수
polynomial poly_mult(polynomial A, polynomial B) {
    polynomial C; // 결과 다항식
    memset(C.coef, 0, sizeof(float) * MAX_DEGREE); // C 배열을 0으로 초기화

    C.degree = A.degree + B.degree; // C 의 최고 차수

    for (int i = 0; i <= A.degree; i++) {
        for (int j = 0; j <= B.degree; j++) {
            C.coef[i + j] += A.coef[i] * B.coef[j];
        }
    }
    return C;
}
