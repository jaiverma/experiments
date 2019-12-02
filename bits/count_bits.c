#include <stdio.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint8_t u8;

// 8 bytes MAP_SIZE corresponds to two 32-bit integers
#define MAP_SIZE 8

// AFL implementation of count_bits
static u32 count_bits(u8* mem) {
  u32* ptr = (u32*)mem;
  u32  i   = (MAP_SIZE >> 2);
  u32  ret = 0;

  while (i--) {
    u32 v = *(ptr++);

    /* This gets called on the inverse, virgin bitmap; optimize for sparse
       data. */

    if (v == 0xffffffff) {
      ret += 32;
      continue;
    }

    v -= ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    ret += (((v + (v >> 4)) & 0xF0F0F0F) * 0x01010101) >> 24;

  }
  return ret;
}

// my implementation to verify AFL's implementation of count_bits
static u32 count_bits_mine(u8 *mem) {
    u32 *ptr = (u32*)mem;
    u32 i = MAP_SIZE >> 2;
    u32 ret = 0;

    while (i--) {
        u32 v = *(ptr++);
        while (v) {
            ret += v & 1;
            v >>= 1;
        }
    }
    return ret;
}

int main() {
    u32 a[] = { 0x01010101, 0x0f0f0f0f }; // 4 bits set, 16 bits set
    printf("count_bits(a) = %d\n", count_bits((u8*)&a));
    printf("count_bits_mine(a) = %d\n", count_bits_mine((u8*)&a));

    u32 b[] = { 0xdeadbeef, 0xcafebabe }; // 24 bits set, 22 bits set
    printf("count_bits(b) = %d\n", count_bits((u8*)&b));
    printf("count_bits_mine(b) = %d\n", count_bits_mine((u8*)&b));

    return 0;
}
