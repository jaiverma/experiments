#include <iostream>

template<class T>
struct Node {
    T val;
    Node<T> *next;
    Node<T>(T);
    Node<T>() = delete;
};

template<class T>
class LL{
public:
    LL();
    void add(T val);
    void addRecursive(T val);
    void del(T val);
    void print();
    void printRecursive();
    void rev();
    int size();
    void release();
private:
    Node<T> *head;
    int sz;
    Node<T> *newNode(T val);
    void _addRecursive(Node<T> *n, Node<T> *x);
    void _printRecursive(Node<T> *n);
};

template<class T>
Node<T> *LL<T>::newNode(T val) {
    return new Node<T>(val);
}

template<class T>
Node<T>::Node(T val) : val(val), next(nullptr) {}

template<class T>
LL<T>::LL() : head(nullptr), sz(0) {}

template<class T>
void LL<T>::add(T val) {
    sz++;
    auto n = newNode(val);
    if (head == nullptr)
        head = n;
    else {
        Node<T> *cur = head;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = n;
    }
}

template<class T>
void LL<T>::addRecursive(T val) {
    sz++;
    auto n = newNode(val);
    if (head == nullptr)
        head = n;
    else
        _addRecursive(head, n);
}

template<class T>
void LL<T>::_addRecursive(Node<T> *n, Node<T> *x) {
    if (n->next == nullptr)
        n->next = x;
    else
        _addRecursive(n->next, x);
}

template<class T>
int LL<T>::size() {
    return sz;
}

template<class T>
void LL<T>::release() {
    Node<T> *cur = head, *next = nullptr;
    while (cur != nullptr) {
        next = cur->next;
        cur->next = nullptr;
        delete(cur);
        cur = next;
    }
    head = nullptr;
    sz = 0;
}

template<class T>
void LL<T>::print() {
    Node<T> *cur = head;
    while (cur != nullptr) {
        std::cout << cur->val << " -> ";
        cur = cur->next;
    }
    std::cout << "NULL\n";
}

template<class T>
void LL<T>::printRecursive() {
    _printRecursive(head);
}

template<class T>
void LL<T>::_printRecursive(Node<T> *n) {
    if (n == nullptr) {
        std::cout << "NULL\n";
        return;
    }
    std::cout << n->val << " -> ";
    _printRecursive(n->next);
}
