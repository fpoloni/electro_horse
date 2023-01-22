
#include "Timer.h"

#include <chrono>

namespace medicalhorse::hardware::device {
Timer::Timer(const std::string &name)
    : mDeviceName(name), mCountTime(0), mSeconds(0), mIsStarded(false) {}

bool Timer::Start() {
  if (!mIsStarded) {
    mIsStarded = true;
    mpThreadTime = std::make_unique<std::thread>(&Timer::Clock, this);
    mpThreadTime->detach();
  }

  return true;
}

void Timer::Stop() {
  if (mIsStarded) {
    mIsStarded = false;
    mCountTime = 0;
    mSeconds = 0;
  }
}

bool Timer::SetParameter(const int parameter) {
  mCountTime = static_cast<uint8_t>(parameter);
  return true;
}

bool Timer::GetParameter(int *parameter) {
  if (nullptr != parameter) {
    *parameter = (mCountTime * 100) + mSeconds;

    return true;
  }

  return false;
}

std::string Timer::GetName() { return mDeviceName; }

void Timer::Clock() {
  while (mIsStarded) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (mSeconds == 59) {
      mSeconds = 0;
      if (mCountTime) {
        mCountTime--;
      } else {
        mIsStarded = false;
      }
    } else {
      mSeconds++;
    }
  }
}

}  // namespace medicalhorse::hardware::device
