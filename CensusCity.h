#pragma once
#include <string>

class A
{
    std::string a1;
    std::string a2;
    int a3;
    int a4;
    bool a5;

public:
    A() : a1(""), a2(""), a3(0), a4(0), a5(false) {};
    A(std::string b1, std::string b2, int n1, int n2, bool c) : a1(b1), a2(b2), a3(n1), a4(n2), a5(c) {};
    ~A() {};

    std::string b() { return a1 + ", " + a2 + " (" + std::to_string(a3) + ", " + std::to_string(a4) + ")"; }

    friend int c(const A& d1, const A& d2);
};

int c(const A& d1, const A& d2)
{
    if (d1.a5)
    {
        if (d1.a4 < d2.a4)
            return -1;
        if (d1.a4 > d2.a4)
            return 1;
        return 0;
    }
    else {
        if (d1.a3 < d2.a3)
            return -1;
        if (d1.a3 > d2.a3)
            return 1;
        return 0;
    }
}
