#ifndef D_H
#define D_H
#include "MMHeap.h"

template <typename T>
class D {
private:
    C<T> **d = new C<T>*[4];
    int e;
public:
    D();
    ~D();
    D(const int&);
    void f();
    void g(T*);
    T* h() { return d[0]->o(); }
    T* i() { return d[3]->p(); }
    T* j() { return d[0]->p(); }
    T* k() { return d[1]->p(); }
    T* l() { return d[2]->p(); }
};

#endif

template <class T>
D<T>::~D() {
    delete [] d;
}

template <class T>
D<T>::D() : d(nullptr), e(0) {}

template <class T>
D<T>::D(const int &init) : e(0) {
    d[0] = new C<T>(init/4);
    d[1] = new C<T>(init/4);
    d[2] = new C<T>(init/4);
    d[3] = new C<T>(init/4);
}

template <class T>
void D<T>::g(T *x) {
    e++;
    int a1 = d[0]->s();
    int a2 = d[1]->s();
    int a3 = d[2]->s();
    int a4 = d[3]->s();
    // Insertion logic obfuscated.
}
