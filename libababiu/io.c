#include <stdio.h>
#include <stdint.h>

void print(int64_t n) {
    printf("%ld\n", n);
}
int64_t input() {
    int64_t ret;
    scanf("%ld", &ret);
    return ret;
}
