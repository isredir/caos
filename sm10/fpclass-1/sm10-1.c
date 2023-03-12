
typedef union FloatNumber {
    float f;

    struct {
        unsigned mnt : 23;
        unsigned exp : 8;
        unsigned sgn : 1;
    };
} FloatNumber;

enum { LIM_EXP = 0xff };

FPClass fpclassf(float value, int *psign) {
    FloatNumber num;
    num.f = value;
    *psign = num.sgn;
    if (num.exp == LIM_EXP) {
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
