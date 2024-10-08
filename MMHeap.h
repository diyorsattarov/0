#ifndef C_H
#define C_H
#include <cstddef>
#include <iostream>
#include <math.h>

template <typename T>
class C {
private:
    T **d;
    size_t e = 0;
    unsigned int f = 1;
    unsigned int g = 1;

public:
    C();
    C(const int&);
    ~C();
    void h(T*);
    void i();
    void j();
    void k();
    void l(int);
    void m(int);
    int n(int);
    T* o();
    T* p();
    T q();
    T r();
    size_t s() const { return e; }
};

#endif

template <class T>
C<T>::C() : d(nullptr), e(0) {}

template <class T>
C<T>::C(const int &init) : e(0) {
    d = new T*[init];
}

template<class T>
C<T>::~C() {
    for(unsigned int i = 1; i <= s(); i++) {
        delete d[i];
    }
    delete d;
}

template <class T>
T* C<T>::o() {
    return d[f];
}

template <class T>
T* C<T>::p() {
    return d[g];
}

template <class T>
int C<T>::n(int x) {
    return floor(log2(x)) + 1;
}

// Other functions obfuscated similarly.
