#ifndef MEDICALHORSE_I2C_H_
#define MEDICALHORSE_I2C_H_

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <vector>

#include "System/ISysPath.h"
#include "System/SysPathDefinition.h"

namespace medicalhorse::hardware::interface {
class I2C : public interface::ISysPath {
public:
  /**
   * @brief Constructor
   */
  I2C(const uint8_t deviceAddress);

  /**
   * @brief Destructor
   */
  virtual ~I2C();

  /**
   * @brief Method to open the local path to onewire
   * bus access.
   * @return True when successfuly or false for otherwise
   */
  bool Open() override;

  /**
   * @brief Method to close the system path to onewire
   * bus access.s
   * @return True when successfuly or false for otherwise
   */
  bool Close() override;

  /**
   * @brief Method to open the system path to onewire
   * bus access.
   * @return True when successfuly or false for otherwise
   */
  bool Read(const int reg, int *parameter) override;

  /**
   * @brief Method to open the system path to onewire
   * bus access.
   * @return True when successfuly or false for otherwise
   */
  bool Write(const int reg, const int parameter) override;

  /**
   * @brief Method to verify ther onewire bus exist
   * as well.
   * @return True when successfuly or false for otherwise
   */
  bool IsBusExist();

  /**
   * @brief Method to get the data collection from the all
   * exitent sensors in the 1-wire bus.
   * @return List of device data collection
   */
  std::vector<std::vector<char>> GetListOfDeviceData();

private:
  std::vector<std::string> mListOfDevicesPath;
  std::vector<std::vector<char>> mListOfDevicesData;

  int mI2CFile;
  std::vector<char> mBuffer;
  uint8_t mDeviceAddress;

  bool mIsOpened;
};

} // namespace medicalhorse::hardware::interface

#endif // MEDICALHORSE_I2C_H_
