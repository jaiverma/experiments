#include <iostream>
#include "ll/ll.hpp"

int main() {
    LL<int> *l = new LL<int>();
    for (int i = 0; i < 5; i++)
        l->add(i);
    l->print();
    for (int i = 5; i < 10; i++)
        l->addRecursive(i);
    l->print();
    l->printRecursive();
    std::cout << "sz: " << l->size() << std::endl;
    l->release();
    delete(l);
}
