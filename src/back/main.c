#include "smart_calc.h"

int main(int argc, char* argv[]) {
    double x = atof(argv[argc - 1]);
    double ans = calc_input(argv[argc - 2], x);
    printf("%f", ans);
    return 0;
}