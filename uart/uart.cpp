#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

int main()
{
	wiringPiSetup();
	int fd = serialOpen("/dev/ttyAMA1", 9600);

	while(1)
	{
		serialPrintf(fd, "Hello World\n");
		delay(3000);
	}
}
