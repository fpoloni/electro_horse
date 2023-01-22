
#ifndef MEDICALHORSE_PWMSIGNAL_H_
#define MEDICALHORSE_PWMSIGNAL_H_

#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Device/DeviceDefinition.h"
#include "PwmDefinition.h"

namespace medicalhorse::hardware::interface
{
    class PWM
    {
    public:
        PWM(const int frequency);
        virtual ~PWM() = default;

        void Start();
        void Stop();
        bool SetDutyCycle(const pwmdefinition::Level level);
        void RegisterIO(const int io);
        void Enable(const bool state);
        int GetDutyCycle();

    private:
#ifdef PLOT_SIGNAL_DISPLAY
        void PlotSignalToScreen();
#endif
        void Execute();
        void SetIO(const int value);

    private:
        std::shared_ptr<std::thread> mpThread;
        std::shared_ptr<std::thread> mpThreadPlotScreen;
        pwmdefinition::PWMValues_t mPwmValues;

        bool mStarted;
        bool mSignalLevel;
        bool mIsOutputEnabled;
        int mPwmLevel;

        mutable std::mutex mMutex;
        std::condition_variable mConditionVariable;
        std::vector<int> mListOfIO;
    };
} // namespace medicalhorse::hardware::interface

#endif // MEDICALHORSE_PWMSIGNAL_H_