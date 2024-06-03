#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Project1/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceTestFixture : public Test {
public:
	FlashDeviceMock flashMem;
	DeviceDriver *testDD = new DeviceDriver(&flashMem);
};


TEST_F(DeviceTestFixture, ReadTest) {
	// Read 를 호출 하면 5번 불려야 한다.
	EXPECT_CALL(flashMem, read)
		.Times(5);

	// Device drive 호출
	testDD->read(0xA);
}

TEST_F(DeviceTestFixture, ReadTest2) {
	// Read 를 호출 하면 5번 불려야 한다.
	// 5번 불렀을 때 모두 같은 값이 return 되도록 한다.
	EXPECT_CALL(flashMem, read)
		.WillRepeatedly(Return(0x3));

	// Device drive 호출
	int actual = testDD->read(0xA);
	EXPECT_EQ(3, actual);
}

TEST_F(DeviceTestFixture, ReadTest3) {
	// Read 를 호출 하면 5번 불려야 한다.
	// 1번 다른 값이 불리면 exception이 호출 되어야 한다.
	EXPECT_CALL(flashMem, read(0xA))
		.WillOnce(Return(0x5))
		.WillOnce(Return(0x5))
		.WillOnce(Return(0x5))
		.WillOnce(Return(0x5))
		.WillOnce(Return(0x3));

	try {
		int actual = testDD->read(0xA);
		FAIL();
	}
	catch(exception &e) {
		e.what();
		//Success
	}
}

TEST_F(DeviceTestFixture, WriteTest) {
	// write 를 호출한다.
	EXPECT_CALL(flashMem, read)
		.WillRepeatedly(Return(0xff));

	EXPECT_CALL(flashMem, write)
		.Times(1);

	testDD->write(0xA, 0xaa);
}

TEST_F(DeviceTestFixture, WriteTest2) {
	// write 를 호출한다.
	EXPECT_CALL(flashMem, read)
		.WillRepeatedly(Return(0x03));

	try {
		testDD->write(0xA, 0xaa);
		FAIL();
	}
	catch (exception& e) {
		e.what();
		//Success
	}
}