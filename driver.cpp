#include "QHeap.h"
#include "Int4MMH.h"
#include <vector>
#include <stdlib.h>
//#include "CensusCity.h"

void test1()
{
	// Testing small cases
	//MMHeap<int> *mmH = new MMHeap<int>(30);
	MMHeap<Int4MMH>* mmH = new MMHeap<Int4MMH>(30);

	mmH->insert(new Int4MMH(18));
	mmH->insert(new Int4MMH(94));
	mmH->insert(new Int4MMH(74));
	mmH->dump();
	mmH->deleteMax();
	mmH->dump();

	delete mmH;
	mmH = new MMHeap<Int4MMH>(90);

	// Figure 6->57 from Weiss 3/e 
	mmH->insert(new Int4MMH(6));
	mmH->insert(new Int4MMH(81));
	mmH->insert(new Int4MMH(87));
	mmH->insert(new Int4MMH(14));
	mmH->insert(new Int4MMH(17));
	mmH->insert(new Int4MMH(12));
	mmH->insert(new Int4MMH(28));
	mmH->insert(new Int4MMH(71));
	mmH->insert(new Int4MMH(25));
	mmH->insert(new Int4MMH(80));
	mmH->insert(new Int4MMH(20));
	mmH->insert(new Int4MMH(52));
	mmH->insert(new Int4MMH(78));
	mmH->insert(new Int4MMH(31));
	mmH->insert(new Int4MMH(42));
	mmH->insert(new Int4MMH(31));
	mmH->insert(new Int4MMH(59));
	mmH->insert(new Int4MMH(16));
	mmH->insert(new Int4MMH(24));
	mmH->insert(new Int4MMH(79));
	mmH->insert(new Int4MMH(63));
	mmH->insert(new Int4MMH(18));
	mmH->insert(new Int4MMH(19));
	mmH->insert(new Int4MMH(32));
	mmH->insert(new Int4MMH(13));
	mmH->insert(new Int4MMH(15));
	mmH->insert(new Int4MMH(48));

	mmH->dump();

	mmH->insert(new Int4MMH(53));
	mmH->insert(new Int4MMH(57));
	mmH->insert(new Int4MMH(13));
	mmH->insert(new Int4MMH(12));
	mmH->insert(new Int4MMH(9));
	mmH->insert(new Int4MMH(10));

	mmH->dump();
	std::cout << "begin delete" << std::endl;
	mmH->deleteMin();
	mmH->deleteMin();
	mmH->deleteMin();
	mmH->dump();
	std::cout << "begin delete" << std::endl;
	mmH->deleteMax();
	mmH->deleteMax();
	mmH->deleteMax();

	mmH->dump();

	delete mmH;
}

void test2()
{
	QHeap<Int4MMH>* q = new QHeap<Int4MMH>(2000);
	for (int j = 0; j < 20; j++) {
		int i = (rand() % 100);
		//std::cout << i << std::endl;
		q->insert(new Int4MMH(i));
	}
	q->insert(new Int4MMH(70));
	q->dump();
	delete q;
}





int main()
{
	//bool test = true;
	//int t;
	//What is this?

	//test1();
	test2();
//	test3();

	/*
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
*/

	return 0;
}