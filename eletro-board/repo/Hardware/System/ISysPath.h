#ifndef MEDICALHORSE_SYSPATH_INTERFACE_H_
#define MEDICALHORSE_SYSPATH_INTERFACE_H_

namespace medicalhorse {
namespace hardware {
namespace interface {

class ISysPath {
 public:
  /**
   * @brief Method to open the local path to onewire
   * bus access.
   * @param True when successfuly or false for otherwise
   */
  virtual bool Open() = 0;
  /**
   * @brief Method to close the system path to onewire
   * bus access.
   * @param True when successfuly or false for otherwise
   */
  virtual bool Close() = 0;

  /**
   * @brief Method to open the system path to onewire
   * bus access.
   * @param True when successfuly or false for otherwise
   */
  virtual bool Read(const int reg, int* parameter) = 0;

  /**
   * @brief Method to open the system path to onewire
   * bus access.
   * @param True when successfuly or false for otherwise
   */
  virtual bool Write(const int reg, const int parameter) = 0;
};

}  // namespace interface
}  // namespace hardware
}  // namespace medicalhorse

#endif  // MEDICALHORSE_SYSPATH_INTERFACE_H_
