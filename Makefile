proj: a.o
    g++ -Wall -std=c++11 a.o -o proj
a.o: driver.cpp D_H
    g++ -Wall -std=c++11 -c driver.cpp
run:
    ./proj
clean:
    rm -f *.o
    rm -f proj
