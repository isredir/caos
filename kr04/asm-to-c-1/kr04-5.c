
#include <stdio.h>

void computation(const float *a, int n, float *res) {
    if (n == 0) {
        *res = (float)0;
        return;
    }
    float res0 = *(a);
    if (n == 1) {
        *res = res0;
        return;
    }
    float res1 = *(a + 1);
    if (n == 2) {
        *res = res0 + res1;
        return;
    }
    float res2 = *(a + 2);
    if (n == 3) {
        *res = res0 + res1 + res2;
        return;
    }
    float res3 = *(a + 3);
    for (int i = 4; i < n; ++i) {
        if (i % 4 == 0) {
            res0 *= a[i];
        }
        if (i % 4 == 1) {
            res1 *= a[i];
        }
        if (i % 4 == 2) {
            res2 *= a[i];
        }
        if (i % 4 == 3) {
            res3 *= a[i];
        }
    }
    *res = res0 + res1 + res2 + res3;
}
//void computation(const float *a, int n, float *res);

int main() {
    float a[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float res;
    computation(a, 8, &res);
    printf("%f", res);
}
