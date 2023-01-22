
#include <iostream>
#include "Signal.h"

namespace medicalhorse {
namespace util {

Signal::Signal() {}

Signal::~Signal() {}

void Signal::SetHigh()
{
    std::cout << "Setting the signal to on\n";
}

void Signal::SetLow()
{
    std::cout << "Setting the signal to off\n";
}

}  // namespace util
}  // namespace medicalhorse