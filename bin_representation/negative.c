#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHAR_BIT_SZ 8

char *intToBin(int32_t x) {
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

    // allocate array for storing individual bits (includes \0)
    int arr_sz = groups * CHAR_BIT_SZ * sizeof(uint8_t) + groups;
    uint8_t *arr_x = (uint8_t*)malloc(arr_sz);
    l_x = x;
    int idx = 0;
    while (l_x != limit) {
        arr_x[idx++] = (l_x & 1) + '0';
        l_x >>= 1;
        if (idx % CHAR_BIT_SZ == 0 && idx != arr_sz - 1)
            arr_x[idx++] = ' ';
    }
    // exclude space for \0
    while (idx < arr_sz - 1) {
        arr_x[idx++] = (x >= 0) ? 0 + '0' : 1 + '0';
    }
    arr_x[idx] = 0;

    // TODO: fill array in right order instead of reversing
    int i = 0, j = arr_sz - 2; // skip \0 at end of arrary
    while (i < j) {
        char tmp = arr_x[i];
        arr_x[i] = arr_x[j];
        arr_x[j] = tmp;
        i++;
        j--;
    }

    return arr_x;
}

int main(void) {
    for (int i = 0; i < 512; i++) {
        char *pos = intToBin(i);
        char *neg = intToBin(-i);
        printf("%4d : [%s] , %4d : [%s]\n", i, pos, -i, neg);
        free(pos);
        free(neg);
    }

    return 0;
}
