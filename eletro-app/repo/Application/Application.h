#ifndef MEDICALHORSE_APPLICATION_H_
#define MEDICALHORSE_APPLICATION_H_

#include <functional>
#include <memory>
#include <thread>

#include "Display/Display.h"
#include "ICommand.h"
#include "eletro-util/repo/HandlePackage/HandlePackage.h"

namespace medicalhorse::app {

class Application {
 public:
  Application();
  virtual ~Application() = default;

  void Run(const medicalhorse::util::pdu_t &pdu);
  void Start();
  void Stop();
  bool Status();
  void PackageFromDisplay();
  void PackageToDisplay();
  void HandlePackageToProgram(const medicalhorse::util::pdu_t &pdu);

  medicalhorse::util::pdu_t GetPayloadStatus();

 private:
  util::Queue<std::vector<int8_t>> mDataToDisplay;
  util::Queue<std::vector<int8_t>> mDataFromDisplay;

  std::shared_ptr<command::ICommand> mpProgram;

  std::thread mThreadDataFromDisplay;
  std::thread mThreadDataToDisplay;
  std::thread mThreadRunProgram;

  display::Display mDisplay;

  bool IsStopped;
  bool IsStarted;
  bool IsRunning;
  bool WaitToFinish;
  int8_t mSetProgram;
};

}  // namespace medicalhorse::app

#endif  // MEDICALHORSE_APPLICATION_H_
