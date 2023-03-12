#include <float.h>
#include <stdint.h>
#include <stdio.h>

typedef enum FPClass {
    FFP_ZERO,
    FFP_DENORMALIZED,
    FFP_NORMALIZED,
    FFP_INF,
    FFP_NAN
} FPClass;

typedef union FloatNumber {
    float f;

    struct {
        unsigned mnt : 23;
        unsigned exp : 8;
        unsigned sgn : 1;
    };
} FloatNumber;

enum { LIM_EXP_1 = 0xff, LIM_MNT_1 = 0x7fffff };

FPClass fpclassf(float value, int *psign) {
    FloatNumber num;
    num.f = value;
    *psign = num.sgn;
    if (num.exp == LIM_EXP_1) {
        if (num.mnt != 0) {
            *psign = 0;
            return FFP_NAN;
        } else {
            return FFP_INF;
        }
    } else if (num.exp == 0) {
        if (num.mnt != 0) {
            return FFP_DENORMALIZED;
        } else {
            return FFP_ZERO;
        }
    } else {
        return FFP_NORMALIZED;
    }
}

void sat_mul8(float *f) {
    FloatNumber fnum;
    fnum.f = *f;
    int sign = fnum.sgn;
    if (fpclassf(*f, &sign) == FFP_INF || fpclassf(*f, &sign) == FFP_NAN) {
        return;
    }
    uint32_t mnt = 0 | fnum.mnt;
    if (fnum.exp == 0) {
        for (int i = 3; i >= 1; --i) {
            mnt <<= 1;
            fnum.mnt <<= 1;
            if (mnt > LIM_MNT_1) {
                fnum.exp += i;
                *f = fnum.f;
                return;
            }
        }
        *f = fnum.f;
        return;
    }
    if (fnum.exp < LIM_EXP_1 - 3) {
        fnum.exp += 3;
        *f = fnum.f;
        return;
    }
    fnum.exp = LIM_EXP_1 - 1;
    fnum.mnt = LIM_MNT_1;
    *f = fnum.f;
}

union Number {
    float f;
    int32_t i;
};

int main() {
    float f = 10.;
    union Number number;
    for (int i = 0; i != 0x007ffff; ++i) {
        number.i = i;
        f = number.f;
        sat_mul8(&f);
        printf("%.100f\n", f);
    }
}