
#include "Pwm.h"

#include <chrono>
#include <cstdio>

#include "Interface/IO/GPIO.h"
#include "Interface/IO/IODefinition.h"

namespace medicalhorse::hardware::interface {

PWM::PWM(const int frequency)
    : mStarted(false),
      mSignalLevel(false),
      mIsOutputEnabled(false),
      mPwmLevel(0) {
  mPwmValues.frequency = frequency;
  mPwmValues.timeH = 0;
  mPwmValues.timeL = 0;

  RegisterIO(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::PWM_1));
  RegisterIO(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::PWM_2));
}

void PWM::Start() {
  mStarted = true;
  mListOfIO.clear();

  mpThread = std::make_shared<std::thread>(&PWM::Execute, this);
  mpThread->detach();

#ifdef PLOT_SIGNAL_DISPLAY
  mpThreadPlotScreen =
      std::make_shared<std::thread>(&PWM::PlotSignalToScreen, this);
  mpThreadPlotScreen->detach();
#endif
}

void PWM::Stop() { mStarted = false; }

int PWM::GetDutyCycle() { return mPwmLevel; }

bool PWM::SetDutyCycle(const pwmdefinition::Level level) {
  double period = 0.00;
  bool retVal = false;

  if (mPwmValues.frequency >= 1000 && mPwmValues.frequency <= 3000) {
    period =
        static_cast<double>(1.0 / static_cast<double>(mPwmValues.frequency)) *
        1000000;
    mPwmValues.timeH =
        static_cast<int>((period * static_cast<int>(level)) / 100.0);
    mPwmValues.timeL = static_cast<int>(period - mPwmValues.timeH);
    retVal = true;

    mPwmLevel = level;
  }

  return retVal;
}

void PWM::RegisterIO(const int io) { mListOfIO.push_back(io); }

void PWM::SetIO(const int value) {
  interface::GPIO::Set(mListOfIO[0], value);
#ifdef PLOT_SIGNAL_DISPLAY
  mSignalLevel = value;
#endif
}

void PWM::Enable(const bool state) { mIsOutputEnabled = state; }

void PWM::Execute() {
  while (mStarted) {
    if (mIsOutputEnabled) {
      SetIO(1);
      std::this_thread::sleep_for(std::chrono::microseconds(mPwmValues.timeH));
      SetIO(0);
      std::this_thread::sleep_for(std::chrono::microseconds(mPwmValues.timeL));
    } else {
      SetIO(0);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }
}
#ifdef PLOT_SIGNAL_DISPLAY
void PWM::PlotSignalToScreen() {
  int idx = 100;
  while (mStarted) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    printf("%d", mSignalLevel);
    fflush(stdout);

    if (0 == idx) {
      printf("\33[2K\r");
      fflush(stdout);
      idx = 100;
    }
    idx--;
  }
}
#endif

}  // namespace medicalhorse::hardware::interface
