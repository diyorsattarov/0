/************************************************
**  File        : QHeap.h
**  Project     : CSCE 221 Project 2, Fall 2019
**  Author      : Diyor Sattarov
**  Date        : 10/28/2019
**  Section     : 501
**  Email       : diyor@tamu.edu
**
**  This file is contains the definitions for
**  the QHeap class
************************************************/
#ifndef QHEAP_H
#define QHEAP_H
#include "MMHeap.h"
template <typename T>
class QHeap {
    private:
        MMHeap<T> **heaps = new MMHeap<T>*[4];

        int length;
    public:
        QHeap();

        ~QHeap();

        QHeap(const int&);

        void dump();

        void insert(T*);

        T* getMin() { return heaps[0]->getMin(); }

        T* getMax() { return heaps[3]->getMax(); }

        T* get25() { return heaps[0]->getMax(); }

        T* get50() { return heaps[1]->getMax(); }

        T* get75() { return heaps[2]->getMax(); }
};
#endif

template <class T>
QHeap<T>::~QHeap() {
    delete [] heaps;
}

template <class T>
QHeap<T>::QHeap() : heaps(nullptr), length(0) {}

template <class T>
QHeap<T>::QHeap(const int &initialsize) : length(0) {
        heaps[0] = new MMHeap<T>(initialsize/4);
        heaps[1] = new MMHeap<T>(initialsize/4);
        heaps[2] = new MMHeap<T>(initialsize/4);
        heaps[3] = new MMHeap<T>(initialsize/4);
}

template <class T>
void QHeap<T>::insert(T *px) {
    length++;
    int Q1 = heaps[0]->size();
    int Q2 = heaps[1]->size();
    int Q3 = heaps[2]->size();
    int Q4 = heaps[3]->size();
    if(Q1 == 0) {
        //insert into first heap if its the first node
        heaps[0]->insert(px);
    }
    else {
        /*
         * if first heap is filled then check for an empty 2nd, 3rd and fourth heap 
         */
        if(Q2 == 0) {
            if(compare(*px, *heaps[0]->getMin()) == -1)  {
            //if(*px < *(heaps[0]->getMin())) {
                heaps[1]->insert(new T(heaps[0]->deleteMin()));
                heaps[0]->insert(px);
            }
            else {
                heaps[1]->insert(px);
            }
        }
        else if(Q3 == 0) {
            if(compare(*px, *heaps[0]->getMin()) == -1) {
            //if(*px < *(heaps[0]->getMin())) {
                heaps[2]->insert(new T(heaps[1]->deleteMin()));
                heaps[1]->insert(new T(heaps[0]->deleteMin()));
                heaps[0]->insert(px);
            }
            else if(compare(*px, *heaps[1]->getMin()) == -1) {
            //else if(*px < *(heaps[1]->getMin())) {
                heaps[2]->insert(new T(heaps[1]->deleteMin()));
                heaps[1]->insert(px);
            }
            else {
                heaps[2]->insert(px);
            }
        }
        else if(Q4 == 0) {
            if(compare(*px, *heaps[0]->getMin()) == -1) {
            //if(*px < *(heaps[0]->getMin())) {
                heaps[3]->insert(new T(heaps[2]->deleteMin()));
                heaps[2]->insert(new T(heaps[1]->deleteMin()));
                heaps[1]->insert(new T(heaps[0]->deleteMin()));
                heaps[0]->insert(px);
            }
            else if(compare(*px, *heaps[1]->getMin()) == -1) {
            //else if(*px < *(heaps[1]->getMin())) {
                heaps[3]->insert(new T(heaps[2]->deleteMin()));
                heaps[2]->insert(new T(heaps[1]->deleteMin()));
                heaps[1]->insert(px);
            }
            else if(compare(*px, *heaps[2]->getMin()) == -1) {
            //else if(*px < *(heaps[2]->getMin())) {
                heaps[3]->insert(new T(heaps[2]->deleteMin()));
                heaps[2]->insert(px);
            }
            else {
                heaps[3]->insert(px);
            }
        }
        /* empty qheap cases are done, now to move onto qheaps with items */
        else {
            //node goes to 1Q
            //-1 is less than
            //1 is more than
            //0 is equal
            int _1Qmin = compare(*px, *heaps[0]->getMin());
            int _1Qmax = compare(*px, *heaps[0]->getMax());
            int _2Qmin = compare(*px, *heaps[1]->getMin());
            int _2Qmax = compare(*px, *heaps[1]->getMax());
            int _3Qmin = compare(*px, *heaps[2]->getMin());
            int _3Qmax = compare(*px, *heaps[2]->getMax());
            int _4Qmin = compare(*px, *heaps[3]->getMin());
            int _4Qmax = compare(*px, *heaps[3]->getMax());

            if(_2Qmin == -1) {
            //if(*px < *(heaps[0]->getMin()) || (*px >= *heaps[0]->getMin() && *px < *heaps[1]->getMin())) {
                if((Q4-Q3 == 0) && (Q3-Q2 == 0) && (Q2-Q1 == 0)) {
                    heaps[0]->insert(px);
                }
                else if((Q4-Q3 == 0) && (Q3-Q2 == 0)) {
                    heaps[1]->insert(new T(heaps[0]->deleteMax()));
                    heaps[0]->insert(px);
                }
                else if(Q4-Q3 == 0) {
                    heaps[2]->insert(new T(heaps[1]->deleteMax()));
                    heaps[1]->insert(new T(heaps[0]->deleteMax()));
                    heaps[0]->insert(px);
                }
                else {
                    heaps[3]->insert(new T(heaps[2]->deleteMax()));
                    heaps[2]->insert(new T(heaps[1]->deleteMax()));
                    heaps[1]->insert(new T(heaps[0]->deleteMax()));
                    heaps[0]->insert(px);
                }
            }
            // node goes to 2Q
            // ((compare(*px, *heaps[0]->getMax()) == 0) || (compare(*px, *heaps[0]->getMax()) == 1 && compare(*px, *heaps[2]->getMin()) == -1))
            else if((_1Qmax >= 0 && _3Qmin == -1)) {
            //else if(*px >= *heaps[0]->getMax() && *px < *heaps[2]->getMin()) {
                if((Q1-Q2 == 0) && (Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[0]->insert(new T(heaps[1]->deleteMin()));
                    heaps[1]->insert(px);
                }
                else if((Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[1]->insert(px);
                }
                else if((Q3-Q4 == 0))  {
                    heaps[2]->insert(new T(heaps[1]->deleteMax()));
                    heaps[1]->insert(px);
                }
                else {
                    heaps[3]->insert(new T(heaps[2]->deleteMax()));
                    heaps[2]->insert(new T(heaps[1]->deleteMax()));
                    heaps[1]->insert(px);
                }
            }
            //node goes to 3Q
            else if((_2Qmax >= 0) && (_4Qmin == -1)) {
            //else if(*px >= *heaps[1]->getMax() && *px < *heaps[3]->getMin()) {
                if((Q1-Q2 == 0) && (Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[0]->insert(new T(heaps[1]->deleteMin()));
                    heaps[1]->insert(new T(heaps[2]->deleteMin()));
                    heaps[2]->insert(px);
                }
                else if((Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[1]->insert(new T(heaps[2]->deleteMin()));
                    heaps[2]->insert(px);
                }
                else if(Q3-Q4 == 0) {
                    heaps[2]->insert(px);
                }
                else {
                    heaps[3]->insert(new T(heaps[2]->deleteMax()));
                    heaps[2]->insert(px);
                }
            }
            //node goes to 4Q
            else if(_3Qmax >= 0) {
            //else if(*px >= *heaps[3]->getMin()) {
                if((Q1-Q2 == 0) && (Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[2]->insert(new T(heaps[3]->deleteMin()));
                    heaps[1]->insert(new T(heaps[2]->deleteMin()));
                    heaps[0]->insert(new T(heaps[1]->deleteMin()));
                    heaps[3]->insert(px);
                }
                else if((Q2-Q3 == 0) && (Q3-Q4 == 0)) {
                    heaps[2]->insert(new T(heaps[3]->deleteMin()));
                    heaps[1]->insert(new T(heaps[2]->deleteMin()));
                    heaps[3]->insert(px);
                }
                else if((Q3-Q4 == 0)) {
                    heaps[2]->insert(new T(heaps[3]->deleteMin()));
                    heaps[3]->insert(px);
                }
                else {
                    heaps[3]->insert(px);
                }
            }
        }
    }
}

template <class T>
void QHeap<T>::dump() {
    std::cout << "***********************************" << std::endl;
    std::cout << "***** Quartile heap statistics ..." << std::endl;
    std::cout << "Minimum: " << getMin()->i << std::endl;
    std::cout << "25th percentile: " << get25()->i << std::endl;
    std::cout << "Median: " << get50()->i << std::endl;
    std::cout << "75th percentile: " << get75()->i << std::endl;
    std::cout << "Maxium: " << getMax()->i << std::endl;
    std::cout << "***** First Quartile heap dump ..." << std::endl;
    heaps[0]->dump();
    std::cout << "***** Second Quartile heap dump ..." << std::endl;
    heaps[1]->dump();
    std::cout << "***** Third Quartile heap dump ..." << std::endl;
    heaps[2]->dump();
    std::cout << "***** Fourth Quartile heap dump ..." << std::endl;
    heaps[3]->dump();
}