#pragma once
class B {
public:
    int a;
    B() : a(0) {}
    B(int n) : a(n) {}    
    friend int c(const B &b1, const B &b2);
};

int c(const B &b1, const B &b2) {
    if (b1.a < b2.a)
        return -1;
    if (b1.a > b2.a)
        return 1;
    return 0;
}
