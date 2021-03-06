#include "stdafx.h"
#include <iostream>
#include <string>              // overrided << operator for cout 
#include <windows.h>
#include <thread>
#include <mutex>


using namespace std;

mutex m;

void shared_print(string msg, int id) {
	//m.lock();   
	lock_guard<mutex> lock(m);  //exception safe way to lock shared variable
	cout << msg << id << endl;   
	//m.unlock();
}
void foo() {
	for (int i = 0; i < 100; i++)
	{
		//using race condition safe to print
		shared_print("From foo(): ", i);
	}
}
int main()
{
	thread t1(foo);

	for (int i = 0; i < 100; i++)
	{
		shared_print("From main():", i);
	}

	Sleep(10000);			//gives time for t1 to finish excute function foo
	//t1.detach();			//t1 will freely on its own; Daemon process; once detached forever detached

	if (t1.joinable()) {    //prevent program to be crashed by detached t1
		t1.join();
	}

	return 0;
}

