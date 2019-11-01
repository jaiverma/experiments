#include <iostream>
#include "ll/ll.hpp"

int main() {
    LL<int> *l = new LL<int>();
    l->add(1);
    l->add(2);
    std::cout << "sz: " << l->size() << std::endl;
    l->release();
    delete(l);
}
