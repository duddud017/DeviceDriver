#include <iostream>
#include "DeviceDriver.h"


class Application{
public:
	Application(DeviceDriver* device):
	myDevice(device){

	}

	void ReadAndPrint(long startAddr, long endAddr) {
		for (long addr = startAddr; addr <= endAddr; addr++) {
			int result = myDevice->read(addr);
			std::cout << result << std::endl;
		}
	}

	void writeAll(int value) {

	}

private:
	DeviceDriver* myDevice;
};