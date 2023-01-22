#include "Application.h"

#include <signal.h>

#include <chrono>
#include <iostream>

#include "CommandDefinition.h"
#include "CommandHandler.h"
#include "eletro-util/repo/Log/Log.h"

#define __PREPARATION_TEST__

namespace medicalhorse::app {
Application::Application()
    : IsStopped(true), IsRunning(false), IsStarted(false), WaitToFinish(false),
      mpProgram(nullptr) {}

void Application::PackageFromDisplay() {
  bool printStatus = false;
  medicalhorse::util::pdu_t pdu;

  while (!IsStopped) {
    if (mDisplay.Get(&pdu) > 0) {
      if (medicalhorse::util::handlepackage::HandlePackage::Validate(pdu,
                                                                     true)) {
        HandlePackageToProgram(pdu);
      } else {
        Log::Error("Invalid package to receive.");
      }
      printStatus = false;
    }

    if (!printStatus) {
      Log::Info("Waiting for packages from display.");
      printStatus = true;
    }
  }
}

void Application::PackageToDisplay() {
  while (!IsStopped) {
    mDisplay.Set(mDataToDisplay.Get());
  }
}

void Application::HandlePackageToProgram(const medicalhorse::util::pdu_t &pdu) {
  if (pdu.state == medicalhorse::util::definition::state::START) {
    Log::Info("Start command request.");
    if (!IsStarted) {
      mpProgram = command::CommandHandler::GetCommand(
          static_cast<medicalhorse::util::definition::program::name>(
              pdu.program));

      mpProgram->Init();
      mpProgram->Set(pdu);
      mpProgram->Start();

      // thread to provide status data
      mThreadRunProgram = std::thread(&Application::Run, this, pdu);
      mThreadRunProgram.detach();

      IsStarted = true;
    } else {
      Log::Info("Update PDU to current program.");
      mpProgram->Set(pdu);
    }
  }

  if (pdu.state == medicalhorse::util::definition::state::STOP) {
    Log::Info("Stop command request.");
    this->Stop();
  }
}

void Application::Run(const medicalhorse::util::pdu_t &pdu) {
  int parameter = 0;
  int temperature = 0;
  int currenttime = 0;

  int status = 0;
  int state = 0;

  IsRunning = true;
  WaitToFinish = false;

  // Status signal to check if the program is running as well.
  while (IsRunning && nullptr != mpProgram) {
    Log::Info("Send message to screen application.");

    mpProgram->Get(medicalhorse::util::definition::device::name::SENSOR,
                   &temperature);
    mpProgram->Get(medicalhorse::util::definition::device::name::TIME,
                   &currenttime);

    mpProgram->State(&state);
    mpProgram->Status(&status);

    const std::vector<int8_t> parameter = {pdu.head,
                                           pdu.operation,
                                           pdu.len,
                                           pdu.program,
                                           (int8_t)state,
                                           pdu.device,
                                           pdu.payload.pwm_level,
                                           pdu.payload.temp_min,
                                           pdu.payload.temp_max,
                                           (int8_t)temperature,
                                           (int8_t)(currenttime / 100),
                                           (int8_t)status,
                                           pdu.crc,
                                           pdu.tail};

    mDataToDisplay.Set(parameter);
  }

  WaitToFinish = true;
  IsRunning = false;
  IsStarted = false;
}

void Application::Start() {
  Log::Info("START the application and Display's threads");

  IsStopped = false;
  mDisplay.Start();

  mThreadDataFromDisplay = std::thread(&Application::PackageFromDisplay, this);
  mThreadDataFromDisplay.detach();

  mThreadDataToDisplay = std::thread(&Application::PackageToDisplay, this);
  mThreadDataToDisplay.detach();
}

bool Application::Status() {
  bool retVal = false;
  int parameter = medicalhorse::util::definition::status::NONE;

  if (nullptr != mpProgram) {
    mpProgram->Status(&parameter);

    switch (parameter) {
    case medicalhorse::util::definition::status::RUN:
    case medicalhorse::util::definition::status::PREPARE:
      retVal = true;
      break;

    default:
      break;
    }
  }
  return retVal;
}

void Application::Stop() {
  if (IsStarted) {
    IsRunning = false;
    IsStarted = false;

    while (!WaitToFinish) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    mpProgram->Stop();
  }
}

} // namespace medicalhorse::app

static volatile bool keepRunning = true;

void test_spi_connection() {}

void intHandler(int info) { keepRunning = false; }

int main(int argc, char **argv) {
  medicalhorse::app::Application application;
  application.Start();

  signal(SIGINT, intHandler);

  // FIXME
  printf("Start of program.LATEST BUILD: %s - %s", __DATE__, __TIME__);

  while (keepRunning) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  application.Stop();

  Log::Info("End of program.");
  exit(0);
}
