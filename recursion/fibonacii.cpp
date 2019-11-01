#include <iostream>
#include <unordered_map>

class Fibonacii {
public:
    Fibonacii() {}
    int generate(int n);
    void dbgPrint();
private:
    std::unordered_map<int, int> m;
};

int Fibonacii::generate(int n) {
    if (n == 0 || n == 1)
        return n;
    auto it = m.find(n);
    if (it != m.end()) {
        return it->second;
    }
    
    m.emplace(n, generate(n-1) + generate(n-2));
    return m[n];
}

int main(void) {
    auto f = Fibonacii();
    for (int i = 0; i < 10; i++) {
        std::cout << f.generate(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
