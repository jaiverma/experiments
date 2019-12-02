#include <stdio.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

int main() {
#ifdef __x86_64__
    u64 a = 0xcafebabedeadbeef;
    u64 *x = &a;
    printf("*x = 0x%016lx\n", *x);
#else
    uint32_t a = 0xdeadbeef;
    u32 *x = &a;
    printf("*x = 0x%08x\n", *x);
#endif

    u8 *y = (u8*)x;
#ifdef __x86_64__
    int n = 8;
#else
    int n = 4;
#endif
    for (int i = 0; i < n; i++) {
        printf("y[%d] = 0x%02x\n", i, y[i]);
    }
}
