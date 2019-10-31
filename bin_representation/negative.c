#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHAR_BIT_SZ 8

void intToBin(int32_t x) {
    int len = (x != 0 && x != -1) ? 0 : 1;
    int l_x = x;
    int limit = (x < 0) ? -1 : 0;

    // get length of binary representation
    while (l_x != limit) {
        l_x >>= 1;
        len++;
    }

    // calculate number of CHAR_BIT_SZ groups
    int groups = 0;
    int l_len = len;
    while (l_len > 0) {
        l_len -= CHAR_BIT_SZ;
        groups++;
    }

    // allocate array for storing individual bits
    uint8_t *arr_x = (uint8_t*)malloc(groups * CHAR_BIT_SZ * sizeof(uint8_t));
    l_x = x;
    int idx = 0;
    while (l_x != limit) {
        arr_x[idx++] = l_x & 1;
        l_x >>= 1;
    }
    while (idx < groups * CHAR_BIT_SZ * sizeof(uint8_t)) {
        arr_x[idx++] = (x >= 0) ? 0 : 1;
    }

    // print binary representation
    for (idx = idx - 1; idx >= 0; idx--) {
        printf("%d", arr_x[idx]);
        if (idx % CHAR_BIT_SZ == 0)
            printf(" ");
    }
    printf("\n");
    free(arr_x);
}

int main(void) {
    for (int i = 0; i < 256; i++) {
        printf("%4d : ", i);
        intToBin(i);
    }

    return 0;
}
