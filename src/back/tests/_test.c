#include "./_test.h"

int main() {
    Suite* suites[] = {
        suite_validate(),
        suite_infix_to_postfix(),
        suite_arithmetic(),
        suite_trigonometric(),
    };
    // int total = 0;
    for (int i = 0; i < 4; i++) {
        SRunner *sr = srunner_create(suites[i]);
        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_run_all(sr, CK_NORMAL);
        // total += srunner_ntests_failed(sr);
        srunner_free(sr);
        putchar('\n');
    }
    // printf("Total errors: %d\n\n", total);
    return 0;
}
