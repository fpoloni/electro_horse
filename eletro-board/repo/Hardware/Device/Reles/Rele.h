

#ifndef MEDICALHORSE_RELE_CONTROL_H_
#define MEDICALHORSE_RELE_CONTROL_H_

#include <string>
#include "../IDevices.h"

namespace medicalhorse::hardware::device
{

    class Rele : public IDevices
    {
    public:
        Rele(const std::string &name);
        virtual ~Rele() = default;

        bool Start() override;
        void Stop() override;
        bool GetParameter(int *parameter) override;
        bool SetParameter(const int parameter) override;
        std::string GetName() override;

        void Set(const int device);
        void Clear(const int device);

    private:
        void Reset();
        std::string mDeviceName;
        int mCurrentProgramState;
    };

} // namespace medicalhorse::hardware::device

#endif // MEDICALHORSE_RELE_CONTROL_H_
