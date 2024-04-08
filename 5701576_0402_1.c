#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

// 다항식의 각 항을 나타내는 구조체
struct term {
    float coef; // 계수
    int expon;  // 지수
};

// 입력된 다항식을 나타내는 배열
struct term terms[MAX_TERMS] = { {4.0, 3}, {3.0, 2}, {2.0, 1}, {1.0, 0},
                                 {3.0, 2}, {2.0, 1}, {8.0, 0} };
int avail = 7; // 다항식의 현재 길이를 나타내는 변수

// 다항식 출력 함수 선언
void print_poly(int s, int e);
// 다항식 곱셈 함수 선언
void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep);


int main() {
    int As = 0, Ae = 3, Bs = 4, Be = 6, Cs, Ce;

    // 입력된 다항식 출력
    printf("A = ");
    print_poly(As, Ae);
    printf("B = ");
    print_poly(Bs, Be);

    // 다항식의 곱셈 수행
    poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
    printf("A * B = ");
    print_poly(Cs, Ce);

    return 0;
}

// 다항식 곱셈 함수
void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep) {
    struct term result[MAX_TERMS]; // 결과 다항식을 저장할 배열
    int avail_result = 0; // 결과 다항식의 현재 길이를 나타내는 변수

    // 결과 다항식 계산
    for (int i = As; i <= Ae; i++) {
        for (int j = Bs; j <= Be; j++) {
            float coef = terms[i].coef * terms[j].coef; // 계수 곱셈
            int expon = terms[i].expon + terms[j].expon; // 지수 합

            // 같은 지수를 가진 항을 찾아 계수를 더함
            int found = 0;
            for (int k = 0; k < avail_result; k++) {
                if (result[k].expon == expon) {
                    result[k].coef += coef;
                    found = 1;
                    break;
                }
            }
            // 같은 지수를 가지는 항이 없으면 결과 다항식에 추가
            if (!found) {
                result[avail_result].coef = coef;
                result[avail_result].expon = expon;
                avail_result++;
            }
        }
    }

    // 결과 다항식을 기존 다항식에 복사
    *Csp = avail;
    for (int i = 0; i < avail_result; i++) {
        terms[avail].coef = result[i].coef;
        terms[avail].expon = result[i].expon;
        avail++;
    }
    *Cep = avail - 1;
}

// 다항식 출력 함수
void print_poly(int s, int e) {
    for (int i = s; i < e; i++) {
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon);
}
