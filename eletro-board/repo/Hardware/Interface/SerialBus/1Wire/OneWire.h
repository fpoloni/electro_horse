
#ifndef MEDICALHORSE_ONEWIRE_H_
#define MEDICALHORSE_ONEWIRE_H_

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "System/ISysPath.h"
#include "System/SysPathDefinition.h"

namespace medicalhorse {
namespace hardware {
namespace interface {

class OneWire : public interface::ISysPath {
public:
  /**
   * @brief Constructor method
   */
  OneWire() = default;
  /**
   * @brief Destructor method
   */
  virtual ~OneWire() = default;

  /**
   * @brief Method to add the legacy modules to onewire
   * and sensor device in the raspberry board.
   * @param List of modprobe list to provide some already implemented
   * module for 1-Wire bus.
   */
  void StartLegacyModules(const std::vector<std::string> modProbeList);

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
  int Size();

  void Show();

private:
  std::vector<std::string> mListOfDevicesPath;
};

} // namespace interface
} // namespace hardware
} // namespace medicalhorse
#endif // MEDICALHORSE_ONEWIRE_H_
