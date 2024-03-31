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
polynomial add_polynomial(polynomial A, polynomial B);
polynomial multiply_polynomial(polynomial A, polynomial B);

// 주어진 두 다항식
polynomial a = { 5, {3.0, 6.0, 0.0, 0.0, 0.0, 10.0} };
polynomial b = { 4, {7.0, 0.0, 5.0, 0.0, 1.0} };

int main(void) {
    // 주어진 다항식 출력
    printf("Polynomial a           :");
    print_polynomial(a);
    printf("Polynomial b           :");
    print_polynomial(b);

    // 다항식 덧셈
    polynomial sum = add_polynomial(a, b);
    printf("Sum of polynomials     :");
    print_polynomial(sum);

    // 다항식 곱셈
    polynomial product = multiply_polynomial(a, b);
    printf("Product of polynomials :");
    print_polynomial(product);

    return 0;
}

// 다항식을 출력하는 함수
void print_polynomial(polynomial p) {
    for (int i = p.degree; i > 0; i--) {
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%3.1f\n", p.coef[p.degree]);
}

// 두 다항식을 더하는 함수
polynomial add_polynomial(polynomial A, polynomial B) {
    polynomial C; //결과 다항식
    memset(C.coef, 0, sizeof(float) * MAX_DEGREE); // C 배열을 0으로 초기화

    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    // C의 최고 차수
    C.degree = (A.degree > B.degree) ? A.degree : B.degree;

    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--; degree_b--;
        }
        else {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

// 두 다항식을 곱하는 함수
polynomial multiply_polynomial(polynomial A, polynomial B) {
    polynomial D; // 결과 다항식
    memset(D.coef, 0, sizeof(float) * MAX_DEGREE); // D 배열을 0으로 초기화

    D.degree = A.degree + B.degree; // D 의 최고 차수

    for (int i = 0; i <= A.degree; i++) {
        for (int j = 0; j <= B.degree; j++) {
            D.coef[i + j] += A.coef[i] * B.coef[j];
        }
    }
    return D;
}
