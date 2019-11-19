#include <dlfcn.h>
#include <stdio.h>

int main() {
    int (*add)(int, int) = NULL;
    int (*subtract)(int, int) = NULL;
    int (*divide)(int, int) = NULL;
    int (*multiply)(int, int) = NULL;
    int (*modulo)(int, int) = NULL;
    void *handle = NULL;
    char *error = NULL;

    handle = dlopen("./arithmetic.so.out", RTLD_LAZY);
    if (!handle) {
        printf("%s\n", dlerror());
        return -1;
    }

    dlerror();
    
    add = (int (*)(int, int)) dlsym(handle, "add");
    subtract = (int (*)(int, int)) dlsym(handle, "subtract");
    divide = (int (*)(int, int)) dlsym(handle, "divide");
    multiply = (int (*)(int, int)) dlsym(handle, "multiply");
    modulo = (int (*)(int, int)) dlsym(handle, "modulo");

    error = dlerror();
    if (error) {
        printf("%s\n", error);
        return -1;
    }

    printf("add(%d, %d) = %d\n", 1, 2, add(1, 2));
    printf("subtract(%d, %d) = %d\n", 1, 2, subtract(1, 2));
    printf("multiply(%d, %d) = %d\n", 2, 2, multiply(2, 2));
    printf("divide(%d, %d) = %d\n", 6, 2, divide(6, 2));
    printf("modulo(%d, %d) = %d\n", 9, 5, modulo(9, 5));

    dlclose(handle);
    return 0;
}
