#include "ll.hpp"

template<class T>
Node<T>::Node(T val) : val(val), next(nullptr) {}

template<class T>
LL<T>::LL() : head(nullptr) {} 
