#ifndef MEDICALHORSE_COMMAND_LINE_H_
#define MEDICALHORSE_COMMAND_LINE_H_

#include <memory>

#include "CommandDefinition.h"
#include "ICommand.h"

namespace medicalhorse::command {
class CommandHandler {
 public:
  static std::unique_ptr<ICommand> GetCommand(
      const util::definition::program::name &commandName);

 private:
  CommandHandler() = default;
  ~CommandHandler() = default;
};

}  // namespace medicalhorse::command
#endif  //  MEDICALHORSE_COMMAND_LINE_H_
