#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p1 = malloc(10); // Line 5
    if (!p1) {
        printf("malloc failed at line %d\n", __LINE__);
        return 1;
    }
    int *p2 = malloc(20 * sizeof(int)); // Line 10
    if (!p2) {
        printf("malloc failed at line %d\n", __LINE__);
        return 1;
    }
    char *p3 = malloc(30); // Line 15
    if (!p3) {
        printf("malloc failed at line %d\n", __LINE__);
        return 1;
    }
    free(p1);
    free(p2);
    free(p3);
    return 0;
}