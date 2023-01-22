
#ifndef MEDICALHORSE_SIGNAL_H_
#define MEDICALHORSE_SIGNAL_H_

namespace medicalhorse {
namespace util {

class Signal
{
    public:
        /**
         * @brief Constructor
         */
        Signal();
        /**
         * @brief Destructor
         */
        virtual ~Signal();
        void SetHigh();
        void SetLow();
};

}  // namespace util
}  // namespace medicalhorse




#endif  // MEDICALHORSE_SIGNAL_H_
