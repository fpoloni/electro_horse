#ifndef MEDICALHORSE_HANDLECOMMAND_H_
#define MEDICALHORSE_HANDLECOMMAND_H_

#include "Command.h"

namespace medicalhorse {
namespace util {

class HandleCommand
{
    public:
        void CommandRegister(Command *pCommand)
        {
            if (nullptr != pCommand)
            {
                mpCommand = pCommand;
            }
        }

        void CommandSet()
        {
            mpCommand->Execute();
        }

    private:
        Command *mpCommand;
};

}  // namespace util
}  // namespace medicalhorse

#endif // MEDICALHORSE_HANDLECOMMAND_H_