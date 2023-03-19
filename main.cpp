#include "containers/vector.hpp"
#include "containers/map.hpp"
#include "containers/stack.hpp"
#include <vector>
#include "iterators/randomaccess_iterator.hpp"
#include "iterators/reverse_iterator.hpp"


int main()
{
	std::cout<<"Vector test is starting..."<<std::endl;
	
	/* Iterators */
	testBegin();
	
	testPushBack();
 	testEnd();
	testRbegin();
	testRend();

	/* Capacity */
	testSize();
	testMaxSize();
	testResize(); 
	testEmpty();
 	testReserve();

	/* Element Access */
	testBoxBrackets();
	testAt();
	testFront();
	testBack();

	/* Modifiers */
	testAssign();
 	testPushBack();
	testPopBack();
	testInsert();
	testErase();
	testSwap();
	testClear();
	testGetAllocator(); 
	std::cout<<"Vector test finished"<<std::endl;


	std::cout<<"Map test is starting..."<<std::endl;
	mapBegin();
	mapEnd();
 	mapRBegin();
	mapREnd();
	mapEmpty();
 	mapSize();
	mapMaxSize();
	
	mapBoxBrackets();
	mapInsert(); 
	mapErase();
	mapSwap(); 
	mapClear();

	mapKeyComp();
	mapValueComp();
	
	mapFind();
	mapCount();
	mapLowerBound();
	mapUpperBound();
	mapEqualRange(); 
	std::cout<<"Map test finished"<<std::endl; 

	/* while(1)
		; */
}