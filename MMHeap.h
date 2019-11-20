/************************************************
**  File        : MMHeap.h
**  Project     : CSCE 221 Project 2, Fall 2019
**  Author      : Diyor Sattarov
**  Date        : 10/28/2019
**  Section     : 501
**  Email       : diyor@tamu.edu
**
**  This file is contains the definitions for
**  the MMHeap class
************************************************/
#ifndef MMHEAP_H
#define MMHEAP_H
#include <cstddef>
#include <iostream>
#include <math.h>

template <typename T>
class MMHeap {
    private:
        T **pData;

        size_t length = 0;

        unsigned int minpos = 1;
        
        unsigned int maxpos = 1;

    public:
        MMHeap();

        MMHeap(const int&);

        ~MMHeap();

        void insert(T*);

        void dump();

        void newMin();

        void newMax();
        
        void percolateUp(int);

        void percolateDown(int);

        int findLevel(int);

        T* getMin();

        T* getMax();

        T deleteMin();

        T deleteMax();
        
        size_t size() const { return length; }


};
#endif

template <class T>
MMHeap<T>::MMHeap() : pData(nullptr), length(0) { }

template <class T>
MMHeap<T>::MMHeap(const int &initialsize) : length(0) {
    pData = new T*[initialsize];
}

template<class T>
MMHeap<T>::~MMHeap() {
    //dump();
    for(unsigned int i = 1; i <= size(); i++) {
        delete pData[i];
    }
    delete pData;
}

template <class T>
T* MMHeap<T>::getMin() {
    return pData[minpos];
}

template <class T>
T* MMHeap<T>::getMax() {
    return pData[maxpos];
}

template <class T>
int MMHeap<T>::findLevel(int n) {
    return floor(log2(n))+1;
}

template <class T>
void MMHeap<T>::newMin() {
    unsigned int i = 1;
    minpos = 1;
    //check for new min
    while(i <= size()) {
        if(findLevel(i)%2 == 0) {
            i = pow(2, findLevel(i));
        }
        else {
            if(compare(*getMin(), *pData[i]) == 1) {
                minpos = i;
            }
            i++;
        }
    }
}

template <class T>
void MMHeap<T>::newMax() {
    unsigned int i = 1;
    maxpos = 1;
    while(i <= size()) {
        if(findLevel(i)%2 != 0) {
            i = pow(2, findLevel(i));
        }
        else {
            if(compare(*getMax(), *pData[i]) == -1) {
                maxpos = i;
            }
            i++;
        }
    }
}

template <class T>
T MMHeap<T>::deleteMax() {
    T temp = *pData[maxpos];
    int i = 4*maxpos;
    //choose smallest percolate down
    if(i <= size()) {
        delete pData[maxpos];
        pData[maxpos] = pData[length];
        length--;
        for(unsigned int j = 0; j < 4; j++) {
            //find biggest grandchild
            if(compare(*pData[minpos], *pData[minpos+j]) == -1 || compare(*pData[minpos], *pData[minpos+j]) == 0) {
                i = minpos+j;
                //std::cout << *pData[i] << std::endl;
            }
        }
        if(compare(*pData[i], *pData[maxpos]) == 1) {
            T *temp = pData[maxpos];
            pData[minpos] = pData[i];
            pData[i] = temp;
        }
        percolateDown(maxpos);
        newMax();
    }
    else {
        if(length == 1) {
            delete pData[maxpos];
            length--;
        }
        else {
            if(length == 2) {
                if(maxpos == 1) {
                    delete pData[maxpos];
                    pData[maxpos] = pData[length];
                    length--;
                }
                else {
                    delete pData[maxpos];
                    length--;
                }
            }
        }
        newMax();
    }
    return temp;
}

template <class T>
T MMHeap<T>::deleteMin() {
    newMin();
    //first save the value of the min to return
    //delete and replace with the newest node
    T temp = *pData[minpos];   
    delete pData[minpos];
    int i = 4*minpos;
    if(i <= size()) {
        pData[minpos] = pData[length];
        length--;
        //choose smallest percolate down
        for(unsigned int j = 0; j < 4; j++) {
            //find smallest grandchild
            if((compare(*pData[minpos], *pData[minpos+j]) == 0) || (compare(*pData[minpos], *pData[minpos+j]) == 1)) {
            //if(*pData[minpos] >= *pData[minpos+j]) {
                i = minpos+j;
                //std::cout << *pData[i] << std::endl;
            }
        }
        if(compare(*pData[i], *pData[minpos]) == -1) {
        //if(*pData[i] < *pData[minpos]) {
            T *temp = pData[minpos];
            pData[minpos] = pData[i];
            pData[i] = temp;
        }
        percolateDown(minpos);
        newMin();
    }
    else {
        if(length > 0) {
            pData[minpos] = pData[length];
            length--;
            newMin();
            percolateDown(minpos);
        }
    }
    //std::cout << temp << std::endl;
    return temp;
}

template<class T>
void MMHeap<T>::insert(T *px) {
    length++;
    pData[length] = px;
    if(length > 1) {
        if(compare(*pData[length], *getMax()) == 1) {
            maxpos = length;
        }
        else if(compare(*pData[length], *getMin()) == -1) {
            minpos = length;
        }
        percolateUp(length);
        newMin();
        newMax();
    }
}

template <class T>
void MMHeap<T>::percolateDown(int n) {
    int i = 2*n;
    //std::cout << "Percolate : " << *pData[n] << std::endl;
    if(n*2 > size()) {
        //std::cout << "base case" << std::endl;
        percolateUp(n);
    }
    else if(n*4 > size()) {
        //std::cout << "no grandchildren case" << std::endl;
        if(findLevel(n)%2 == 0) {
            if((compare(*pData[i], *pData[i+1]) == 1) && (compare(*pData[i], *pData[n]) == 1)) {
                //std::cout << "swap1" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i];
                pData[i] = temp;
                percolateDown(i);
            }
            else if(((compare(*pData[i+1], *pData[i]) == 1) || (compare(*pData[i+1], *pData[i]) == 0)) && (compare(*pData[i+1], *pData[n]) == 1)) {
                //std::cout << "before swap" << *pData[i] << " " << *pData[n] << std::endl;
                dump();
                //std::cout << "swap2" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i+1];
                pData[i+1] = temp;
                percolateDown(i+1);
            }
        }
        else {
            if((compare(*pData[i], *pData[i+1]) == -1) && (compare(*pData[i], *pData[n]) == -1)) {
            //if(*pData[i] < *pData[i+1] && *pData[i] < *pData[n]) {
                //std::cout << "swap1" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i];
                pData[i] = temp;
                percolateDown(i);
            }
            else if(((compare(*pData[i+1], *pData[i]) == 0) || (compare(*pData[i+1], *pData[i]) == -1))  && (compare(*pData[i+1], *pData[n]) == -1)) {
            //else if(*pData[i+1] <= *pData[i] && *pData[i+1] < *pData[n]) {
                //std::cout << "before swap" << *pData[i] << " " << *pData[n] << std::endl;
                //dump();
                //std::cout << "swap2" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i+1];
                pData[i+1] = temp;
                percolateDown(i+1);
            }
        }
    }
    else {
        //std::cout << "has children and grandchildren" << std::endl;
        if(findLevel(n)%2 == 0) {
            //max level
            //std::cout << "check children" << std::endl;
            if((compare(*pData[i], *pData[i+1]) == 1) && (compare(*pData[i], *pData[n]) == 1)) {
            //if(*pData[i] > *pData[i+1] && *pData[i] > *pData[n]) {
                //swap
                //std::cout << "left child is smaller" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i];
                pData[i] = temp;
                percolateDown(i);
            }
            else if(((compare(*pData[i+1], *pData[i]) == 0) || (compare(*pData[i+1], *pData[i]) == 1)) && (compare(*pData[i+1], *pData[n]) == 1)) {
            //else if(*pData[i+1] >= *pData[i] && *pData[i+1] > *pData[n]) {
                //swap
                //std::cout << "right child is smaller" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i+1];
                pData[i+1] = temp;
                percolateDown(i+1);
            }
            else {
                //children are not larger so move to grand children
                //std::cout << "check grandchildren1" << std::endl;
                i = 2*i;
                int max = i;
                //std::cout << min << std::endl;
                if(i <= size()) {
                    for(unsigned int j = 0; j < size()-i; j++) {
                        //find smallest grandchild
                        if(compare(*pData[max], *pData[i+j]) == -1) {
                        //if(*pData[max] < *pData[i+j]) {
                            max = i+j;
                            //std::cout << *pData[max] << std::endl;
                        }
                    }
                    if(compare(*pData[max], *pData[n]) == 1) {
                    //if(*pData[max] > *pData[n]) {
                        //swap
                        //std::cout << "swap: " << *pData[max] << " and " << *pData[n] << std::endl;
                        T *temp = pData[n];
                        pData[n] = pData[max];
                        pData[max] = temp;
                        percolateDown(max);
                    }
                }
            }
        }
        else {
            //min level
            //std::cout << "check children" << std::endl;
            if((compare(*pData[i], *pData[i+1]) == -1) && (compare(*pData[i], *pData[n]) == -1)) {
            //if(*pData[i] < *pData[i+1] && *pData[i] < *pData[n]) {
                //swap
                //std::cout << "left child is smaller" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i];
                pData[i] = temp;
                percolateDown(i);
            }
            else if(((compare(*pData[i+1], *pData[i]) == 0) || (compare(*pData[i+1], *pData[i]) == -1)) && (compare(*pData[i+1], *pData[n]) == -1)) {
            //else if(*pData[i+1] <= *pData[i] && *pData[i+1] < *pData[n]) {
                //swap
                //std::cout << "right child is smaller" << std::endl;
                T *temp = pData[n];
                pData[n] = pData[i+1];
                pData[i+1] = temp;
                percolateDown(i+1);
            }
            else {
                //children are not smaller so move to grand children
                //std::cout << "check grandchildren2" << std::endl;
                i = 2*i;
                int min = i;
                if(i <= size()) {
                    //std::cout << min << std::endl;
                    for(unsigned int j = 0; j < size()-i; j++) {
                        //find smallest grandchild
                        if(compare(*pData[min], *pData[i+j]) == 1) {
                        //if(*pData[min] > *pData[i+j]) {
                            min = i+j;
                            //std::cout << *pData[min] << std::endl;
                        }
                    }
                    if(compare(*pData[min], *pData[n]) == -1) {
                    //if(*pData[min] < *pData[n]) {
                        //swap
                        //std::cout << "swap: " << *pData[min] << " and " << *pData[n] << std::endl;
                        T *temp = pData[n];
                        pData[n] = pData[min];
                        pData[min] = temp;
                        percolateDown(min);
                    }
                }
            }
        }
    }
}
template <class T>
void MMHeap<T>::percolateUp(int n) {
    //check level if odd or even
    //then check parent to see if its less than or greater than
    //if it is then swap, and return percolate up with new index
    //if it isn't check grandparent to see if val is greater or less than
    //if it is swap, percolate up
    //even nubers are max
    if(findLevel(n)%2 == 0) {
        //this case checks if node is smaller than the parent at the max level
        //if it is, swap then check grandparent
        if((pData[n/2]) && (compare(*pData[n], *pData[n/2]) == -1)) {
        //if(pData[n/2] && *pData[n] < *pData[n/2]) {
            T *temp = pData[n];
            pData[n] = pData[n/2];
            pData[n/2] = temp;
            percolateUp(n/2);
        }
        //if it isnt check the grandparent
        else {
            if((pData[n/4]) && (compare(*pData[n], *pData[n/4]) == 1)) {
            //if(pData[n/4] && *pData[n] > *pData[n/4]) {
                T *temp = pData[n];
                pData[n] = pData[n/4];
                pData[n/4] = temp;
                percolateUp(n/4);
            }
        }
    }
    //odd numbers are min
    else {
        //same idea but for min level
        if((pData[n/2]) && (compare(*pData[n], *pData[n/2]) == 1)) {
        //if(pData[n/2] && *pData[n] > *pData[n/2]) {
            T *temp = pData[n];
            pData[n] = pData[n/2];
            pData[n/2] = temp;
            percolateUp(n/2);
        }
        //if it isnt check the grandparent
        else {
            if((pData[n/4]) && (compare(*pData[n], *pData[n/4]) == -1)) {
            //if(pData[n/4] && *pData[n] < *pData[n/4]) {
                T *temp = pData[n];
                pData[n] = pData[n/4];
                pData[n/4] = temp;
                percolateUp(n/4);
            }
        }
    }
}

template <class T>
void MMHeap<T>::dump() {
    std::cout << "---------------------------------------" << std::endl << "--- min-max heap dump --- " << std::endl;
    std::cout << "Size = " << size() << std::endl;
    if(size() > 0) {
        std::cout << "Minimum = " << getMin()->i << std::endl << "Maximum = " << getMax()->i << std::endl << "Last level: " << findLevel(size()) << std::endl;
    }
    if(length == 0) {
        std::cout << "Empty Heap" << std::endl;
    }
    else {
        std::cout << "--- heap data items --- " << std::endl;
        for(unsigned int i = 1; i <= size(); i++) {
            std::cout << "H[" << i << "] = " << pData[i]->i << std::endl;
        }
    }
    std::cout << "---------------------------------------" << std::endl;
}