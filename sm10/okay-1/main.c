
#include <stdio.h>
 
void okay(double x, double y, double *r);
 
int main() {
    double result;
    okay(4., 3., &result);
    printf("%.10g\n", result);
    return 0;
}
