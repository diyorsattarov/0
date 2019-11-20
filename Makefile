proj: driver.o
	g++ -Wall -std=c++11 driver.o -o proj
driver.o: driver.cpp QHeap.h
	g++ -Wall -std=c++11 -c driver.cpp
# QHeap.o: QHeap.h
# 	g++ -Wall -std=c++11 -c QHeap.cpp
# MMHeap.o: MMHeap.h
# 	g++ -Wall -std=c++11 -c MMHeap.cpp
run:
	./proj
clean:
	rm -f *.o
	rm -f proj