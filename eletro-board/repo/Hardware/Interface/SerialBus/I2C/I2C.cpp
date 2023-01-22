
#include "I2C.h"

#include <chrono>
#include <thread>

namespace medicalhorse::hardware::interface {
I2C::I2C(const uint8_t deviceAddress)
    : mDeviceAddress(deviceAddress), mIsOpened(false) {}

I2C::~I2C() { Close(); }

bool I2C::Open() {
  bool retVal = false;

  if (false == mIsOpened) {
    char *filename = (char *)"/dev/i2c-1";

    if ((mI2CFile = open(filename, O_RDWR)) < 0) {
      printf("Failed to open the i2c bus");
      return false;
    }

    if (ioctl(mI2CFile, I2C_SLAVE, mDeviceAddress) < 0) {
      printf("Failed to acquire bus access and/or talk to slave.\n");
      return false;
    }

    mIsOpened = true;
    retVal = true;
  }

  return retVal;
}

bool I2C::Close() {
  bool retVal = false;

  if (true == mIsOpened) {
    close(mI2CFile);
    mIsOpened = false;
    retVal = true;
  }

  return retVal;
}

bool I2C::Read(const int reg, int *parameter) {
  bool retVal = false;

  if (nullptr != parameter) {
    /* Write internal address to devide  */
    if (write(mI2CFile, &reg, 1) != 1) {
      printf("Write i2c internal address error");
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));

      if (read(mI2CFile, parameter, 1) != 1) {
        printf("Failed to read from the i2c bus.\n");
      } else {
        retVal = true;
      }
    }
  }
  return retVal;
}

bool I2C::Write(const int reg, const int parameter) {
  int outlen = 0;
  bool retVal = false;
  uint8_t buffer[2] = {(uint8_t)reg, (uint8_t)parameter};

  if ((outlen = write(mI2CFile, buffer, 1)) != 1) {
    printf("Failed to write from the i2c bus. - outcome: %d - register: 0x%x - "
           "parameter: 0x%x\n",
           outlen, buffer[0], buffer[1]);
  } else {
    retVal = true;
  }

  return retVal;
}
} // namespace medicalhorse::hardware::interface
