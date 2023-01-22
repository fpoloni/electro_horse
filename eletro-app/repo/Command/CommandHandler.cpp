
#include "CommandHandler.h"

#include "../Application/ProgramProcess.h"
#include "Board.h"

namespace medicalhorse::command {
std::unique_ptr<ICommand> CommandHandler::GetCommand(
    const util::definition::program::name &commandName) {
  std::unique_ptr<ICommand> pCommand = nullptr;

  printf("Switch value %d.\n", commandName);
  switch (commandName) {
    case util::definition::program::CRYOTHERAPY:
    case util::definition::program::THERMOTHERAPY:
      pCommand = std::make_unique<ProgramProcess>(
          hardware::Board::GetInstance(), commandName);
      break;

    case util::definition::program::NONE:
      printf("NONE.\n");
      pCommand = nullptr;
      break;
    default:
      printf("Program type is not defined.\n");
      break;
  }

  return pCommand;
}

}  // namespace medicalhorse::command
