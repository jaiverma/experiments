#include <iostream>
#include <unordered_map>
#include <iomanip>

// __int128 is a gcc extension
// allow __int128 to work with cout
typedef unsigned __int128 __uint128;

std::ostream &operator<<(std::ostream &os, __uint128 x) {
    std::string s;
    while (x > 0) {
        s = std::to_string((unsigned int)(x % 10)) + s;
        x /= 10;
    }
    return os << s;
}

class Factorial {
public:
    Factorial() {};
    __uint128 generate(int);
private:
    std::unordered_map<int, __uint128> m;
};

__uint128 Factorial::generate(int n) {
    if (n == 0 || n == 1)
        return 1;
    auto it = m.find(n);
    if (it != m.end()) {
        return it->second;
    }
    m.emplace(n, n * generate(n - 1));
    return m[n];
}

int main(void) {
    auto f = Factorial();
    for (int i = 0; i <= 34; i++) {
        std::cout << "f(" << std::setw(2) << i << ") = " << f.generate(i) << std::endl;
    }

    return 0;
}
