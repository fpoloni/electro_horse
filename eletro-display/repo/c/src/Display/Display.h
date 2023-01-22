#ifndef MEDICALHORSE_DISPLAY_H_
#define MEDICALHORSE_DISPLAY_H_

#include <functional>

#include "HandlePackage.h"
#include "Package.h"
#include "Queue.h"
#include "TcpIpComm.h"

namespace medicalhorse::display {
class Display {
public:
  /**
   * @brief Constructor
   */
  Display();

  /**
   * @brief Destructor
   */
  virtual ~Display() = default;

  void Start();
  void Stop();
  int Get(util::pdu_t *output);
  void Set(const std::vector<int8_t> &package);

private:
  connection::TcpIpComm mEthConnection;
  util::Queue<std::shared_ptr<medicalhorse::util::Package>> mDataFromDisplay;
  bool mIsStarted;
};
} // namespace medicalhorse::display

#endif // MEDICALHORSE_DISPLAY_HANDLEPACKAGE_H_