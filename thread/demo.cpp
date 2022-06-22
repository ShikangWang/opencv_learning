#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void thread01()
{
	while(1)
	{
		cout<<"01"<<endl;
		usleep(500000);
	}
}

void thread02()
{
	while(1)
	{
		cout<<"02"<<endl;
		sleep(1);
	}
}

int main()
{
	thread task01(thread01);
	thread task02(thread02);

	task01.detach();
	task02.detach();
	while(1)
	{
		cout<<"main"<<endl;
		sleep(1);
	}
	//system("pause");
}
