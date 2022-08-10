#include "smart_calc.h"

int main(int argc, char* argv[]) {
    // [name, func, xmin, xmax, step]
    if (argc == 5) {
        double xmin = atof(argv[argc - 3]);
        double xmax = atof(argv[argc - 2]);
        double step = atof(argv[argc - 1]);
        if (step > 0 && (xmin < xmax)) {
            printf("{ points: [ ");
            for (double i = xmin; i <= xmax; i += step) {
                double ans = calc_input(argv[argc - 4], i);
                if (i + step > xmax) {
                    printf("[%.6f, %.6f] ", i, ans);
                } else {
                    printf("[%.6f, %.6f], ", i, ans);
                }
            }
            printf("]}");
        } else {
            fprintf(stderr, "wrong options");
            exit(1);
        }
    // [name, func, x]
    } else {
        double x = atof(argv[argc - 1]);
        double ans = calc_input(argv[argc - 2], x);
        printf("%f", ans);
    }

    return 0;
}