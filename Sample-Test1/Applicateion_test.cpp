#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Project1/Application.cpp"

using namespace testing;
using namespace std;

class DeviceDriverMock : public DeviceDriver {
public:
	//DeviceDriverMock():DeviceDriver(nullptr){
	//}
	MOCK_METHOD(int, read, (long address), ());
	MOCK_METHOD(void, write, (long address, int data), ());
};

TEST(AppTest, ReadTest1) {
	DeviceDriverMock dd;
	Application testApp{ dd };

	EXPECT_CALL(*dd, read(0x0)).WillOnce(Return(0x5));
	//Start~ End addr 까지 읽기
	testApp.ReadAndPrint(0x0, 0x0);
}
