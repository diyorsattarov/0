#include "QHeap.h"
#include "Int4MMH.h"
#include <vector>
#include <stdlib.h>

void t1()
{
    C<B>* mmH = new C<B>(30);
    mmH->h(new B(18));
    mmH->h(new B(94));
    mmH->i();
    mmH->r();
    mmH->i();
    delete mmH;

    mmH = new C<B>(90);
    mmH->h(new B(6));
    mmH->h(new B(81));
    // More obfuscated operations on mmH
}

void t2()
{
    D<B>* q = new D<B>(2000);
    for (int j = 0; j < 20; j++) {
        int i = (rand() % 100);
        q->g(new B(i));
    }
    q->g(new B(70));
    q->f();
    delete q;
}

int main()
{
    t2();
    return 0;
}
