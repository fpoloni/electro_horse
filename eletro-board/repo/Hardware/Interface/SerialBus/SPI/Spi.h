#ifndef MEDICALHORSE_SPI_H_
#define MEDICALHORSE_SPI_H_

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#include "System/ISysPath.h"
#include "System/SysPathDefinition.h"
#include "Interface/IO/IODefinition.h"

#define SPI_BUFFER 2
#define SPI_FREQ 1000000
#define SPI_WORD 8
#define SPI_DELAY 20

#define OPEN true
#define CLOSE false

namespace medicalhorse::hardware::interface {
class Spi : public interface::ISysPath {
public:
  /**
   * @brief Constructor
   */
  Spi(const iodefinition::SENSOR_SPI Channel);

  /**
   * @brief Destructor
   */
  virtual ~Spi() = default;

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

  private:
    std::string m_device_path;
    iodefinition::SENSOR_SPI m_channel;
    bool m_state;
    int mFile;


};

} // namespace medicalhorse::hardware::interface

#endif // MEDICALHORSE_SPI_H_