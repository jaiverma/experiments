#include <iostream>
#include <iomanip>

int nSum(int n) {
    if (n == 0)
        return 0;
    return n + nSum(n-1);
}

int main(void) {
    for (int i = 0; i < 10; i++) {
        std::cout << "f(" << std::setw(2) << i << ") = " << std::setw(2) << nSum(i) << std::endl;
    }

    return 0;
}
