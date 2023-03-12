#include <stdio.h>

typedef struct BSearchResult {
    size_t low;
    size_t high;
    int result;
} BSearchResult;

struct BSearchResult
bsearch2(const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar)(const void *p1, const void *p2, void *user),
         void *user) {
    BSearchResult res;
    int l = 0;
    int r = (int)nmemb;
    if (nmemb == 0 || compar((char *)base, key, user) > 0) {
        res.low = 0;
        res.high = 0;
        res.result = 0;
        return res;
    }
    if (compar((char *)base + (nmemb - 1) * size, key, user) < 0) {
        res.low = nmemb;
        res.high = nmemb;
        res.result = 0;
        return res;
    }
    while (l + 1 < r) {
        int d = (l + r - 1) / 2;
        if (compar((char *)base + d * size, key, user) >= 0) {
            r = d + 1;
        } else {
            l = d + 1;
        }
    }
    if (compar((char *)base + l * size, key, user) == 0) {
        res.result = 1;
        res.low = l;
        l = 0;
        r = (int)nmemb;
        while (l + 1 < r) {
            int d = (l + r) / 2;
            if (compar((char *)base + d * size, key, user) <= 0) {
                l = d;
            } else {
                r = d;
            }
        }
        if (compar((char *)base + l * size, key, user) == 0) {
            res.high = l + 1;
        } else {
            res.high = l;
        }
    } else {
        res.result = 0;
        res.high = l;
        res.low = res.high;
    }
    return res;
}
