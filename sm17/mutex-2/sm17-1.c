#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { SCANF_ARGS = 5 };

struct Parameters {
    int it;
    int idx1, idx2;
    double sum1, sum2;
    double *accs;
    pthread_mutex_t *muts;
};

void *f(void *arg) {
    struct Parameters *p = (struct Parameters *)arg;
    pthread_mutex_lock(&p->muts[p->idx1]);
    pthread_mutex_lock(&p->muts[p->idx2]);
    for (int i = 0; i < p->it; ++i) {
        p->accs[p->idx1] += p->sum1;
        p->accs[p->idx2] += p->sum2;
    }
    pthread_mutex_unlock(&p->muts[p->idx1]);
    pthread_mutex_unlock(&p->muts[p->idx2]);
    return NULL;
}

int main() {
    int acc_count, thr_count;
    if (scanf("%d %d", &acc_count, &thr_count) != 2) {
        return 1;
    }
    struct Parameters *p = calloc(thr_count, sizeof(*p));
    pthread_t *threads = calloc(thr_count, sizeof(*threads));
    double *accs = calloc(acc_count, sizeof(*accs));
    pthread_mutex_t *muts = calloc(acc_count, sizeof(*muts));
    for (int i = 0; i < acc_count; ++i) {
        pthread_mutex_init(&muts[i], NULL);
        accs[i] = 0;
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);
    for (int i = 0; i < thr_count; ++i) {
        if (scanf("%d %d %lg %d %lg", &p[i].it, &p[i].idx1, &p[i].sum1,
                  &p[i].idx2, &p[i].sum2) != SCANF_ARGS) {
            return 1;
        }
        if (p[i].idx1 > p[i].idx2) {
            int temp = p[i].idx1;
            p[i].idx1 = p[i].idx2;
            p[i].idx2 = temp;
            double temp1 = p[i].sum1;
            p[i].sum1 = p[i].sum2;
            p[i].sum2 = temp1;
        }
        p[i].muts = muts;
        p[i].accs = accs;
        pthread_create(&threads[i], &attr, f, (void *)&p[i]);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < thr_count; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < acc_count; ++i) {
        pthread_mutex_destroy(&muts[i]);
        printf("%.10g\n", accs[i]);
    }
    free(p);
    free(threads);
    free(accs);
    free(muts);
    return 0;
}
