#pragma once
class Int4MMH {
public:
    int i;
    Int4MMH() : i(0) {}
    Int4MMH(int n) : i(n) {}    
    friend int compare(const Int4MMH &c1, const Int4MMH &c2);
};

int compare(const Int4MMH &c1, const Int4MMH &c2) {
    if (c1.i < c2.i)
        return -1;
    if (c1.i > c2.i)
        return 1;
    return 0;
}