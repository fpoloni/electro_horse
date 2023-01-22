#ifndef MEDICALHORSE_SIGNALCOMMAND_H_
#define MEDICALHORSE_SIGNALCOMMAND_H_

#include "Command.h"
#include "Signal.h"

namespace medicalhorse {
namespace util {

class SignalCommand: public Command
{
    public:
        SignalCommand(Signal *pSignal) : mpSignal(pSignal)
        {
        }

        void Execute() const override
        {
            mpSignal->SetHigh();
        }

    private:
        Signal *mpSignal;
};

}  // namespace util
}  // namespace medicalhorse

#endif // MEDICALHORSE_SIGNALCOMMAND_H_