#ifndef MEDICALHORSE_HANDLETHREAD_COMMAND_H_
#define MEDICALHORSE_HANDLETHREAD_COMMAND_H_

namespace medicalhorse {
namespace util {

class Command
{
    public:
        virtual ~Command() {}

        virtual void Execute() const = 0;
};

}  // namespace util
}  // namespace medicalhorse



#endif  // #define MEDICALHORSE_HANDLETHREAD_COMMAND_H_