#ifndef MEDICALHORSE_COMMAND_LINE_INTERFACE_H_
#define MEDICALHORSE_COMMAND_LINE_INTERFACE_H_

#include "eletro-util/repo/Package/Package.h"

namespace medicalhorse::command {
class ICommand {
 public:
  virtual void Init() = 0;
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual bool Status(int *parameter) = 0;
  virtual bool State(int *parameter) = 0;
  virtual void Set(const int8_t device, const int parameter) = 0;
  virtual void Set(const medicalhorse::util::pdu_t &pdu) = 0;
  virtual void Get(const int8_t device, int *parameter) = 0;
};
}  // namespace medicalhorse::command

#endif  //  MEDICALHORSE_COMMAND_LINE_INTERFACE_H_
