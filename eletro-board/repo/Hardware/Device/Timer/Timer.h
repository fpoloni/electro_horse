

#ifndef MEDICALHORSE_TIMER_H_
#define MEDICALHORSE_TIMER_H_

#include <memory>
#include <thread>

#include "Device/IDevices.h"

namespace medicalhorse::hardware::device {

class Timer : public IDevices {
 public:
  Timer(const std::string &name);
  virtual ~Timer() = default;

  bool Start() override;
  void Stop() override;
  bool SetParameter(const int parameter) override;
  bool GetParameter(int *parameter) override;
  std::string GetName() override;

 private:
  void Clock();

 private:
  std::unique_ptr<std::thread> mpThreadTime;
  std::string mDeviceName;

  uint8_t mCountTime;
  uint8_t mSeconds;

  bool mIsStarded;
};
}  // namespace medicalhorse::hardware::device

#endif  // MEDICALHORSE_TIMER_H_
