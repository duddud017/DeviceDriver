#include "DeviceDriver.h"
#include "stdexcept"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) 
    : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int ret = (int)(m_hardware->read(address));

    for (int i = 0; i < 4; i++) {
        if (ret == (int)(m_hardware->read(address)))
            continue;
        else {
            throw(std::logic_error("Device return wrong answer"));
        }
            
    }
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    unsigned char readVal = m_hardware->read(address);
    if (readVal == 0xff) {
        m_hardware->write(address, (unsigned char)data);
    }
    else {
        throw(std::logic_error("Device is not empty"));
    }
}