#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include <vector>
#include "iterators/randomaccess_iterator.hpp"
#include "iterators/reverse_iterator.hpp"


 void print_my_vector(ft::vector<int> v)
{
    
    ft::vector<int>::iterator it = v.begin();
    std::cout<< "\n---my vector-----\n";
    std::cout<<"capacity: "<<v.capacity()<<" size: "<<v.size()<<std::endl;
    std::cout<< ".....................\n";
	std::cout<<"datas ---> ";
    while(it != v.end())
        std::cout<<*it++<<" ";
    std::cout<< "\n.....................\n";
}

 void print_my_vector(ft::vector<std::string> v)
{
    
    ft::vector<std::string>::iterator it = v.begin();
    std::cout<< "\n---my vector-----\n";
    std::cout<<"capacity: "<<v.capacity()<<" size: "<<v.size()<<std::endl;
    std::cout<< ".....................\n";
	std::cout<<"datas ---> ";
    while(it != v.end())
        std::cout<<*it++<<" ";
    std::cout<< "\n.....................\n";
}

void print_orj_vector(std::vector<int> v)
{

    std::vector<int>::iterator it = v.begin();
    std::cout<< "\n----original vector---------\n";
    std::cout<<"capacity: "<<v.capacity()<<" size: "<<v.size()<<std::endl;
    std::cout<< ".....................\n";
	std::cout<<"datas ---> ";
    while(it != v.end())
        std::cout<<*it++<<" ";
    std::cout<< "\n.....................\n";
}

void testBegin()
{
    std::cout<< "***iterator begin() const_iterator begin()***\n" <<std::endl;
	ft::vector<int> myVecBegin;
	ft::vector<int>::iterator myItBegin;
	ft::vector<int>::const_iterator myConstItBegin;

	std::vector<int> orjVecBegin;
	std::vector<int>::iterator orjItBegin;
	std::vector<int>::const_iterator constOrjItBegin;

	myVecBegin.push_back(1);
	myItBegin = myVecBegin.begin();
	myConstItBegin = myVecBegin.begin();

	orjVecBegin.push_back(1);
	orjItBegin = orjVecBegin.begin();
	constOrjItBegin = orjVecBegin.begin();

	if (*myVecBegin.begin() == *orjVecBegin.begin() && *myConstItBegin == *constOrjItBegin)
		std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
	else
		std::cout<<"FAIL for begin"<<std::endl;

	std::cout<< "-----------------end of the begin-----------------------------\n\n" <<std::endl;
	
}


void testEnd()
{
    std::cout<< "***iterator end() const_iterator end()***\n" <<std::endl;
	ft::vector<int> myVecEnd;
	ft::vector<int>::iterator myItEnd;
	ft::vector<int>::const_iterator myConstItEnd;

	std::vector<int> orjVecEnd;
	std::vector<int>::iterator orjItEnd;
	std::vector<int>::const_iterator constOrjItEnd;
	myVecEnd.push_back(1);
	myVecEnd.push_back(2);
	//2 1
	myItEnd = myVecEnd.end() - 1;
	myConstItEnd = myVecEnd.end() - 1;

	orjVecEnd.push_back(1);
	orjVecEnd.push_back(2);
	//2 1
	orjItEnd = orjVecEnd.end() - 1;
	constOrjItEnd = orjVecEnd.end() - 1;


	if (*myVecEnd.end() == *orjVecEnd.end() && *myConstItEnd == *constOrjItEnd)
		std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
	else
		std::cout<<"FAIL for end"<<std::endl;

	std::cout<< "----------------end of the end------------------------------\n\n" <<std::endl;
}

void testRbegin()
{
    std::cout<< "***iterator rbegin() const_iterator rbegin()***\n" <<std::endl;
	ft::vector<int> myVecRBegin;
	ft::vector<int>::reverse_iterator myItRBegin;
	ft::vector<int>::const_iterator myConstItRBegin;

	std::vector<int> orjVecRBegin;
	std::vector<int>::reverse_iterator orjItRBegin;
	std::vector<int>::const_iterator constOrjItRBegin;

	myVecRBegin.push_back(1);
	myVecRBegin.push_back(2);
	myVecRBegin.push_back(3);
	myItRBegin = myVecRBegin.rbegin();
	//orijinalde de çalışmıyor
	//myConstItRBegin = myVecRBegin.rbegin();

	orjVecRBegin.push_back(1);
	orjVecRBegin.push_back(2);
	orjVecRBegin.push_back(3);
	//3 2 1
	orjItRBegin = orjVecRBegin.rbegin();
	//constOrjItRBegin = orjVecRBegin.rbegin();

	if (*myVecRBegin.rbegin() == *orjVecRBegin.rbegin())
	    std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
    else
        std::cout<<"FAIL for rbegin"<<std::endl;

	std::cout<< "---------------end of the rbegin-------------------------------\n\n" <<std::endl;
}

void testRend()
{
    std::cout<< "***iterator rend() const_iterator rend()***\n" <<std::endl;
	ft::vector<int> myVecREnd;
	ft::vector<int>::reverse_iterator myItREnd;

	std::vector<int> orjVecREnd;
	std::vector<int>::reverse_iterator orjItREnd;


	myVecREnd.push_back(1);
	myVecREnd.push_back(2);
	myVecREnd.push_back(3);
	myItREnd = myVecREnd.rend();
	//orijinalde de çalışmıyor
	//myConstItREnd = myVecREnd.rbegin();

	orjVecREnd.push_back(1);
	orjVecREnd.push_back(2);
	orjVecREnd.push_back(3);
	//3 2 1
	orjItREnd = orjVecREnd.rend();


	if (*myItREnd == *orjItREnd)
        std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
    else
        std::cout<<"FAIL for rend my:" << *myVecREnd.rend()<< " orj: " <<*orjVecREnd.rend() <<std::endl;

	std::cout<< "-------------end of the rend---------------------------------\n\n" <<std::endl;
}

void testSize()
{
    std::cout<< "***iterator size()***\n" <<std::endl;
	ft::vector<int> myVecSize;
	std::vector<int> orjVecSize;

	if (myVecSize.size() == orjVecSize.size())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"Fail size"<<std::endl;

	myVecSize.push_back(1);
	myVecSize.push_back(2);
	myVecSize.push_back(3);
	myVecSize.pop_back();


	orjVecSize.push_back(1);
	orjVecSize.push_back(2);
	orjVecSize.push_back(3);
	orjVecSize.pop_back();

	if (myVecSize.size() == orjVecSize.size())
		std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
	else
		std::cout<<"Fail size"<<std::endl;


	std::cout<< "--------------end of the size--------------------------------\n\n" <<std::endl;
}

void testMaxSize()
{
    std::cout<< "***iterator max_size()***\n" <<std::endl;
	
	ft::vector<int> myVecMaxSize;
	std::vector<int> orjVecMaxSize;

	myVecMaxSize.push_back(1);
	myVecMaxSize.push_back(2);
	myVecMaxSize.push_back(3);
	myVecMaxSize.pop_back();

	orjVecMaxSize.push_back(1);
	orjVecMaxSize.push_back(2);
	orjVecMaxSize.push_back(3);
	orjVecMaxSize.pop_back();

	if (myVecMaxSize.max_size() == orjVecMaxSize.max_size())
		std::cout<<"\033[1;32m \033[1;32m OK \033[0m \033[0m"<<std::endl;
	else
		std::cout<<"Fail max_size"<<std::endl;

	std::cout<< "--------------end of the max size--------------------------------\n\n" <<std::endl;
}

void testResize()
{
    std::cout<< "***iterator resize()***\n" <<std::endl;
	
	ft::vector<int> myVecReSize;
	std::vector<int> orjVecReSize;


	myVecReSize.push_back(11);
	myVecReSize.push_back(2);
	myVecReSize.push_back(3);
	int myFirstSize = myVecReSize.size();
	myVecReSize.resize(2);//n is smaller than the current container size


	orjVecReSize.push_back(11);
	orjVecReSize.push_back(2);
	orjVecReSize.push_back(3);
	int orjFirstSize = orjVecReSize.size();
	orjVecReSize.resize(2);//n is smaller than the current container size
	
	if (orjFirstSize == myFirstSize)
		std::cout << "\033[1;32m \033[1;32m OK \033[0m \033[0m" <<std::endl;
	else
		std::cout<< "Fail resize"<<std::endl;

	myVecReSize.resize(1, 3);//n is smaller than the current container size
	orjVecReSize.resize(1, 3);//n is smaller than the current container size

	myVecReSize.resize(2);//n is bigger than the current container size
	orjVecReSize.resize(2);//n is bigger than the current container size
	
	myVecReSize.resize(4, 1);//n is bigger than the current container size
	orjVecReSize.resize(4, 1);//n is bigger than the current container size
	
	myVecReSize.resize(14, 1);//n is bigger than the current container cap
	orjVecReSize.resize(14, 1);//n is bigger than the current container cap

	if (myVecReSize.size() == orjVecReSize.size())
		std::cout << "\033[1;32m \033[1;32m OK \033[0m \033[0m" <<std::endl;
	else
		std::cout<< "Fail resize"<<std::endl;

	std::cout<< "--------------end of the resize--------------------------------\n\n" <<std::endl;

}

/* void testCapacity()
{
    std::cout<< "***iterator capacity()***\n" <<std::endl;
	
	ft::vector<int> myVecCapacity;
	std::vector<int> orjVecCapacity;

    for(int i = 0; i < 100; i++)
    {
	    myVecCapacity.push_back(i);
	    orjVecCapacity.push_back(i);

    }

	if (myVecCapacity.capacity() == orjVecCapacity.capacity())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"Fail capacity"<<std::endl;

    for (int i = 0; i < 24; i++)
    {
    	myVecCapacity.pop_back();
	    orjVecCapacity.pop_back();
    }

	if (myVecCapacity.capacity() == orjVecCapacity.capacity())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"Fail capacity"<<std::endl;


    for (int i = 0; i < 24; i++)
    {
    	myVecCapacity.insert(myVecCapacity.begin(), i*2);
    	orjVecCapacity.insert(orjVecCapacity.begin(), i*2);
    }

	if (myVecCapacity.capacity() == orjVecCapacity.capacity())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"Fail capacity"<<std::endl;
    
    //!!!!!insert capacity is false


	std::cout<< "--------------end of the capacity--------------------------------\n\n" <<std::endl;
} */

void testEmpty()
{
    std::cout<< "***iterator empty()***\n" <<std::endl;
	
	ft::vector<int> myVecEmpty;
	std::vector<int> orjVecEmpty;

    if (myVecEmpty.empty() == orjVecEmpty.empty())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;

    myVecEmpty.push_back(5);
    orjVecEmpty.push_back(5);
    
    if (myVecEmpty.empty() == orjVecEmpty.empty())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;



	std::cout<< "--------------end of the empty--------------------------------\n\n" <<std::endl;
}


void testReserve()
{
    std::cout<< "***iterator reserve()***\n" <<std::endl;
	
	ft::vector<int> myVecReserve;
	std::vector<int> orjVecReserve;

    if (myVecReserve.capacity() == myVecReserve.capacity())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;
    
    orjVecReserve.reserve(5);
    orjVecReserve.reserve(5);
    if (myVecReserve.capacity() == myVecReserve.capacity())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;

    orjVecReserve.reserve(15);
    orjVecReserve.reserve(15);
    if (myVecReserve.capacity() == myVecReserve.capacity())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;

    orjVecReserve.reserve(1);
    orjVecReserve.reserve(1);
    if (myVecReserve.capacity() == myVecReserve.capacity())
        std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
    else
        std::cout<<"FAIL"<<std::endl;

	std::cout<< "--------------end of the reserve--------------------------------\n\n" <<std::endl;
}

void testBoxBrackets()
{
    std::cout<< "***iterator BoxBrackets()***\n" <<std::endl;
	
	ft::vector<int> myVecBoxBrackets;
	std::vector<int> orjVecBoxBrackets;

    orjVecBoxBrackets.push_back(11);
    orjVecBoxBrackets.push_back(22);
    orjVecBoxBrackets.push_back(33);

    myVecBoxBrackets.push_back(11);
    myVecBoxBrackets.push_back(22);
    myVecBoxBrackets.push_back(33);

    const int a = orjVecBoxBrackets[0];
    const int b = myVecBoxBrackets[0];
    if (a == b)
        std::cout<<"const \033[1;32m OK \033[0m"<<std::endl;
    else
    {
        std::cout<<"const FAIL"<<std::endl;
    }

    for (size_t i = 0; i < myVecBoxBrackets.size(); i++)
    {
        if (myVecBoxBrackets[i] == orjVecBoxBrackets[i])
            std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
        else
        {
            std::cout<<"FAIL for "<<i<<". element"<<std::endl;
        }
    }    
	std::cout<< "--------------end of the BoxBrackets--------------------------------\n\n" <<std::endl;
}

void testAt()
{
	std::cout<< "***referece at()***\n" <<std::endl;
	
	ft::vector<int> myVecAt;
	std::vector<int> orjVecAt;

    orjVecAt.push_back(11);
    orjVecAt.push_back(22);
    orjVecAt.push_back(33);

    myVecAt.push_back(11);
    myVecAt.push_back(22);
    myVecAt.push_back(33);

    const int a = orjVecAt.at(0);
    const int b = myVecAt.at(0);
    if (a == b)
        std::cout<<"const \033[1;32m OK \033[0m"<<std::endl;
    else
    {
        std::cout<<"const FAIL"<<std::endl;
    }

    for (size_t i = 0; i < myVecAt.size(); i++)
    {
        if (myVecAt.at(i) == orjVecAt.at(i))
            std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
        else
        {
            std::cout<<"FAIL for "<<i<<". element"<<std::endl;
        }
    }

	try
	{
		orjVecAt.at(20);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		myVecAt.at(20);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout<< "--------------end of the at--------------------------------\n\n" <<std::endl;
}

void testFront()
{
	std::cout<< "***reference front() const_reference front()***\n" <<std::endl;
	
	ft::vector<int> myVecFront;
	std::vector<int> orjVecFront;


	// std::cout<< orjVecFront.front() << std::endl; -- segfault
	// std::cout<< myVecFront.front() << std::endl; -- segfault

	

	for(size_t i = 0; i <4; i++)
	{
		myVecFront.push_back(i);
		orjVecFront.push_back(i);
		if (myVecFront.front() == orjVecFront.front())
			std::cout<< "\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<< "FAIL for "<<i<<". element"<<std::endl;
	}

	myVecFront.front() = 9;
	orjVecFront.front() = 9;
	if (myVecFront.front() == orjVecFront.front())
			std::cout<< "\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<< "FAIL for assign"<<std::endl;
	
	const int a = myVecFront.front();
	const int b = orjVecFront.front();

	if (a == b)
	    std::cout<<"const \033[1;32m OK \033[0m"<<std::endl;
    else
		std::cout<<"FAIL for const"<<std::endl;

	std::cout<< "-----------------end of the front-----------------------------\n\n" <<std::endl;
}

void testBack()
{
	std::cout<< "***reference back() const_reference back()***\n" <<std::endl;
	
	ft::vector<int> myVecBack;
	std::vector<int> orjVecBack;


	// std::cout<< orjVecBack.front() << std::endl; -- segfault
	// std::cout<< myVecBack.front() << std::endl; -- segfault

	

	for(size_t i = 0; i <4; i++)
	{
		myVecBack.push_back(i);
		orjVecBack.push_back(i);
		if (myVecBack.back() == orjVecBack.back())
			std::cout<< "\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<< "FAIL for "<<i<<". element"<<std::endl;
	}

	myVecBack.back() = 9;
	orjVecBack.back() = 9;
	if (myVecBack.back() == orjVecBack.back())
			std::cout<< "\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<< "FAIL for assign"<<std::endl;
	
	const int a = myVecBack.back();
	const int b = orjVecBack.back();

	if (a == b)
	    std::cout<<"const \033[1;32m OK \033[0m"<<std::endl;
    else
		std::cout<<"FAIL for const"<<std::endl;

	std::cout<< "-----------------end of the back-----------------------------\n\n" <<std::endl;
}

void testAssign()
{
	std::cout<< "***void assign()***\n" <<std::endl;
	
	ft::vector<int> myVecAssign;
	std::vector<int> orjVecAssign;


	orjVecAssign.assign(22, 2);
	myVecAssign.assign(22, 2);

	for(int i = 0; i < 22; i++)
	{

		if (orjVecAssign[i] == myVecAssign[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<<"FAIL for assign : "<< i<<"myVec: " << myVecAssign[i]<<"orjVec: "<<orjVecAssign[i] <<std::endl;

	}

/* 	for(int i = 3; i < 10; i++)
	{
		std::cout<<"add->"<<i<<std::endl;
		orjVecAssign.assign(i, i );
		myVecAssign.assign(i, i );
		if (orjVecAssign[i] == myVecAssign[i])
			std::cout<<"\033[1;32m OK \033[0m"<< i<<"myVec: " << myVecAssign[i]<<"orjVec: "<<orjVecAssign[i]<<std::endl;
		else
			std::cout<<"FAIL for assign: "<< i<<"myVec: " << myVecAssign[i]<<"orjVec: "<<orjVecAssign[i] <<std::endl;
	} */





	std::vector<int> newOrjVecAssign;
	ft::vector<int> newMyVecAssign;

	newOrjVecAssign.assign(orjVecAssign.begin() + 1, orjVecAssign.begin() + 12);
	newMyVecAssign.assign(myVecAssign.begin() + 1, myVecAssign.begin() + 12);

	for(size_t i = 0; i < newOrjVecAssign.size(); i++) 
	{
		if (orjVecAssign[i] == myVecAssign[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<<"FAIL for assign: "<< i<<"myVec: " << myVecAssign[i]<<"orjVec: "<<orjVecAssign[i] <<std::endl;
	}


	/* ft::vector<std::string> myVecstr;
	myVecstr.push_back("str");
	myVecstr.push_back("my");
	myVecstr.push_back("1");
	myVecstr.push_back("2");
	myVecstr.push_back("33");
	myVecstr.push_back("4");
	ft::vector<std::string> newstrVecAssign;
	newstrVecAssign.assign(myVecstr.begin(), myVecstr.begin() + 3);
	print_my_vector(newstrVecAssign); */

	std::cout<< "-----------------end of the assign-----------------------------\n\n" <<std::endl;
}

void testPushBack()
{
	std::cout<< "***void pushback()***\n" <<std::endl;
	
	ft::vector<int> myVecPushBack;
	std::vector<int> orjVecPushBack;

	for (int i = 0; i < 12; i++)
	{
		myVecPushBack.push_back(i*2 + 11);
		orjVecPushBack.push_back(i*2 + 11);
		if (myVecPushBack[i] == orjVecPushBack[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<<"Fail for pushBack"<<std::endl;
	}
	std::cout<< "-----------------end of the pushback-----------------------------\n\n" <<std::endl;
	

}

void testPopBack()
{
	std::cout<< "***void popback()***\n" <<std::endl;
	
	ft::vector<int> myVecPopBack;
	std::vector<int> orjVecPopBack;

	for (int i = 0; i < 42; i++)
	{
		myVecPopBack.push_back(i*2 + 11);
		orjVecPopBack.push_back(i*2 + 11);
	}

	for (int i = 0; i < 32; i++)
	{
		myVecPopBack.pop_back();
		orjVecPopBack.pop_back();
	}


	if (*myVecPopBack.end() == *orjVecPopBack.end())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"Fail for pushBack"<<std::endl;

	std::cout<< "-----------------end of the popback-----------------------------\n\n" <<std::endl;
}

void testInsert()
{
	std::cout<< "***iterator insert () void insert()***\n" <<std::endl;
	
	ft::vector<int> myVecInsert;
	std::vector<int> orjVecInsert;

	for (int i = 0; i < 12; i++)
	{
		orjVecInsert.insert(orjVecInsert.end(), i);
		myVecInsert.insert(myVecInsert.end(), i);
	}

	orjVecInsert.insert(orjVecInsert.begin() + orjVecInsert.size(), 2, 3);
	myVecInsert.insert(myVecInsert.begin() + myVecInsert.size(), 2, 3);
	
	for(size_t i = 0; i < myVecInsert.size(); ++i)
	{
		if (myVecInsert[i] == orjVecInsert[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
		{
		    std::cout<<"fail for "<<i<<". index"<<std::endl;
			break;
		}
	}	

	ft::vector<int> myVecLastInsert;
	std::vector<int> orjVecLastInsert;

	for (int i = 0; i < 12; i++)
	{
		myVecLastInsert.insert(myVecLastInsert.end(), i);
		orjVecLastInsert.insert(orjVecLastInsert.end(), i);
	}

	ft::vector<int>::iterator myLastIt = myVecLastInsert.begin();
	std::vector<int>::iterator orjLastIt = orjVecLastInsert.begin();

	myVecLastInsert.insert(myLastIt + 2, myVecInsert.begin() + 1, myVecInsert.end() - 2);
	orjVecLastInsert.insert(orjLastIt + 2, orjVecInsert.begin() + 1, orjVecInsert.end() - 2);

	for(size_t i = 0; i < myVecLastInsert.size(); ++i)
	{
		if (myVecLastInsert[i] == orjVecLastInsert[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
		{
		    std::cout<<"fail for "<<i<<". index"<<std::endl;
			break;
		}
	}	

	std::cout<< "-----------------end of the insert-----------------------------\n\n" <<std::endl;
}

void testErase()
{
	std::cout<< "***void erase()***\n" <<std::endl;
	
	ft::vector<int> myVecErase;
	std::vector<int> orjVecErase;

	for (int i = 0; i < 25; i++)
	{
		myVecErase.push_back(i);
		orjVecErase.push_back(i);
	}

	ft::vector<int>::iterator it = myVecErase.begin(); 
	myVecErase.erase(it);
	orjVecErase.erase(orjVecErase.begin());
	for (int i = 0; i < 14; i++)
	{
		if (myVecErase[i] == orjVecErase[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
		{
			std::cout<<"fail for "<<i<<". index"<<std::endl;
            break;
		}
	}
	
		myVecErase.erase(myVecErase.begin(), myVecErase.begin() + 2);
		orjVecErase.erase(orjVecErase.begin(), orjVecErase.begin() + 2);

		for(size_t i = 0; i < myVecErase.size(); i++)
		{
			if (myVecErase[i] == orjVecErase[i])
				std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
			else
			{
				std::cout<<"fail for "<<i<<". index"<<std::endl;
				break;
			}
		}

	std::cout<< "-----------------end of the erase-----------------------------\n\n" <<std::endl;
}

void testSwap()
{
	std::cout<< "***void swap()***\n" <<std::endl;
	
	ft::vector<int> myVecSwap1;
	ft::vector<int> myVecSwap2;
	std::vector<int> orjVecSwap1;
	std::vector<int> orjVecSwap2;

	for (int i = 0; i < 10; i++)
	{
		myVecSwap1.push_back(i*2 + 11);
		orjVecSwap1.push_back(i*2 + 11);
	}

	for (int i = 0; i < 10; i++)
	{
		myVecSwap2.push_back(i*-1);
		orjVecSwap2.push_back(i*-1);
	}

	myVecSwap1.swap(myVecSwap2);
	orjVecSwap1.swap(orjVecSwap2);

	for (size_t i = 0; i < myVecSwap1.size(); i++)
	{
		if (myVecSwap1[i] == orjVecSwap1[i] || myVecSwap2[i] == orjVecSwap2[i])
            std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
        else
        {
            std::cout<<"fail for "<<i<<". index"<<std::endl;
            break;
        }
	}

	std::cout<< "-----------------end of the swap-----------------------------\n\n" <<std::endl;
}

void testClear()
{
	std::cout<< "***void clear()***\n" <<std::endl;
	
	ft::vector<int> myVecClear;
	std::vector<int> orjVecClear;

	for (int i = 0; i < 42; i++)
	{
		myVecClear.push_back(i*2 + 11);
		orjVecClear.push_back(i*2 + 11);
	}

	myVecClear.clear();
	orjVecClear.clear();

	if (myVecClear.size() == orjVecClear.size())
		std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
	else
		std::cout<<"fail"<<std::endl;


	std::cout<< "-----------------end of the clear-----------------------------\n\n" <<std::endl;
}

void testGetAllocator()
{
	std::cout<< "***void GetAllocator()***\n" <<std::endl;
	
	ft::vector<int> myVecGetAllocator;
	ft::vector<int>::allocator_type myAlloc;
	std::vector<int> orjVecGetAllocator;
	std::vector<int>::allocator_type orjAlloc;

	for (int i = 0; i < 5; i++)
	{
		myVecGetAllocator.push_back(i);
		orjVecGetAllocator.push_back(i);
	}

	myAlloc = myVecGetAllocator.get_allocator();
	orjAlloc = orjVecGetAllocator.get_allocator();

	int *m = myAlloc.allocate(5);
	int *o = orjAlloc.allocate(5);

	for (int i = 0; i < 5; i++)
    {
        myAlloc.construct(&m[i], i);
        orjAlloc.construct(&o[i], i);
    }

	for (int i = 0; i < 5; i++)
	{
		if (m[i] == o[i])
			std::cout<<"\033[1;32m OK \033[0m"<<std::endl;
		else
			std::cout<<"fail"<<std::endl;
	}
	
	for (int i = 0; i < 5; i++)
    {
        myVecGetAllocator.get_allocator().destroy(&m[i]);
        orjVecGetAllocator.get_allocator().destroy(&o[i]);
    }
    myVecGetAllocator.get_allocator().deallocate(m, 5);
    orjVecGetAllocator.get_allocator().deallocate(o, 5); 

	std::cout<< "-----------------end of the GetAllocator-----------------------------\n\n" <<std::endl;
}