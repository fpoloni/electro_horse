
#include "ProgramProcess.h"

#include <iostream>

#include "CommandDefinition.h"
#include "Interface/PWM/PwmDefinition.h"

namespace medicalhorse::command {

ProgramProcess::ProgramProcess(
    const std::shared_ptr<hardware::Board> &pBoard,
    const util::definition::program::name &ProgramType)
    : mpBoard(pBoard), mProgramType(ProgramType), mIsStarted(false),
      mSetPackage(false), mIsTemperatureOk(false), mManagePumpTime(0),
      mManagePumpTimeState(0), mStatusProgram(util::definition::status::NONE),
      mStateProgram(util::definition::state::STOP) {}

void ProgramProcess::Init() {
  printf("ProgramProcess::Init\n");
  mpBoard->Init();
}

void ProgramProcess::Start() {
  printf("ProgramProcess::Start\n");
  printf("time: %d, TempMax: %d, TempMin: %d, PWM: %d\n", mpdu.payload.time,
         mpdu.payload.temp_max, mpdu.payload.temp_min, mpdu.payload.pwm_level);

  mIsStarted = mpBoard->Start();

  if (mIsStarted) {
    mpThreadRun = std::make_shared<std::thread>(&ProgramProcess::Run, this);
    mpThreadRun->detach();
  } else {
    Stop();
    printf("ERROR: Failed to trye to start the board component.\n");
  }
}

void ProgramProcess::Stop() {
  printf("ProgramProcess::Stop\n");

  mIsStarted = false;
  mSetPackage = false;
  mIsTemperatureOk = false;
  mManagePumpTime = 0;
  mManagePumpTimeState = 0;
  mStateProgram = util::definition::state::STOP;

  SetTemperatureCtrl(util::program::PUMP_OFF);
  SetTemperatureCtrl(util::program::TEMP_THERM_OFF);
  SetTemperatureCtrl(util::program::TEMP_CRYO_OFF);

  mpBoard->Stop();
}

bool ProgramProcess::Status(int *parameter) {
  if (nullptr != parameter) {
    *parameter = mStatusProgram;
  }

  return mIsStarted;
}

bool ProgramProcess::State(int *parameter) {
  if (nullptr != parameter) {
    *parameter = mStateProgram;
  }

  return mIsStarted;
}

void ProgramProcess::Set(const int8_t device, const int parameter) {
  switch (device) {
  case medicalhorse::util::definition::device::name::MOTOR:
    mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Motor,
                                  parameter);
    break;
  case medicalhorse::util::definition::device::name::SENSOR:
    mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Sensor,
                                  parameter);
    break;
  case medicalhorse::util::definition::device::name::TIME:
    mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Timer,
                                  parameter);
    break;
  case medicalhorse::util::definition::device::name::HBRIDGE:
    mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::HBridge,
                                  parameter);
    break;
  default:
    /**
     * @fixme: Have to implement the log class for info, debug or error messages
     */
    break;
  }
}

void ProgramProcess::Set(const medicalhorse::util::pdu_t &pdu) {
  if (!mSetPackage) {
    mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Sensor,
                                  mProgramType);
    mSetPackage = true;
  }

  mpdu = pdu;
}

void ProgramProcess::Get(const int8_t device, int *parameter) {
  if (nullptr == parameter) {
    /**
     * @fixme: Have to implement the log class for info, debug or error messages
     */
    return;
  }

  switch (device) {
  case medicalhorse::util::definition::device::name::MOTOR:
    mpBoard->GetParameterToDevice(hardware::BoardElement::first_type::Motor)
        ->GetParameter(parameter);
    break;
  case medicalhorse::util::definition::device::name::SENSOR:
    mpBoard->GetParameterToDevice(hardware::BoardElement::first_type::Sensor)
        ->GetParameter(parameter);
    break;
  case medicalhorse::util::definition::device::name::TIME:
    mpBoard->GetParameterToDevice(hardware::BoardElement::first_type::Timer)
        ->GetParameter(parameter);
    break;
  default:
    /**
     * @fixme: Have to implement the log class for info, debug or error messages
     */
    break;
  }
}

void ProgramProcess::SetTemperatureCtrl(const util::program::state control) {
  mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Rele,
                                control);
}

void ProgramProcess::PumpControl(const int time) {
  if (mManagePumpTime != time) {
    mManagePumpTime = time;
    mManagePumpTimeState++;

    if (mManagePumpTimeState <= 2) {
      SetTemperatureCtrl(util::program::PUMP_ON);
    } else {
      SetTemperatureCtrl(util::program::PUMP_OFF);
      if (mManagePumpTimeState == 6) {
        mManagePumpTimeState = 0;
      }
    }
  }
}

int ProgramProcess::GetCurrentTimeMinute() {
  int time_counter = 0;
  this->Get(medicalhorse::util::definition::device::name::TIME, &time_counter);

  return time_counter / 100;
}

int ProgramProcess::GetCurrentTimeSeconds() {
  int time_counter = 0;
  this->Get(medicalhorse::util::definition::device::name::TIME, &time_counter);

  return time_counter % 100;
}

void ProgramProcess::Run() {
  int temperature = 0;
  bool flag_run_start = false;

  while (mIsStarted) {
    Get(medicalhorse::util::definition::device::name::SENSOR, &temperature);

    printf("Temperature values: %d, %d, %d\n", mpdu.payload.temp_max,
           mpdu.payload.temp_min, temperature);

    if (mProgramType == util::definition::program::CRYOTHERAPY)
      this->CrioProcess(temperature);

    if (mProgramType == util::definition::program::THERMOTHERAPY)
      this->TermoProcess(temperature);

    switch (mpdu.payload.status) {
    case util::definition::status::PREPARE:
      mStatusProgram = util::definition::status::PREPARE;
      mStateProgram = mpdu.state;

      if (mIsTemperatureOk) {
        mStateProgram = util::definition::state::CANCEL;
      } else {
        mStateProgram = mpdu.state;
      }

      break;
    case util::definition::status::RUN:
      if (!flag_run_start) {
        flag_run_start = true;
        mpBoard->SetParameterToDevice(
            hardware::BoardElement::first_type::HBridge, mProgramType);

        // SetTemperatureCtrl(util::program::PUMP_ON);

        mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Timer,
                                      mpdu.payload.time);
        mpBoard->GetParameterToDevice(hardware::BoardElement::first_type::Timer)
            ->Start();
      }
      // the pwm level should be used only in the termoterapia
      mpBoard->SetParameterToDevice(hardware::BoardElement::first_type::Motor,
                                    mpdu.payload.pwm_level);

      this->PumpControl(this->GetCurrentTimeSeconds());

      mStatusProgram = util::definition::status::RUN;
      mStateProgram = mpdu.state;

      break;

    default:
      break;
    }
  } // while end

  Stop();
}

void ProgramProcess::CrioProcess(const int &temperature) {
  printf("Temperature control for CrioProcess.\n");
  if (temperature > mpdu.payload.temp_min && !mIsTemperatureOk) {
    SetTemperatureCtrl(util::program::TEMP_CRYO_ON);
  } else {
    SetTemperatureCtrl(util::program::TEMP_CRYO_OFF);
    mIsTemperatureOk = true;
  }

  if (temperature < mpdu.payload.temp_max && mIsTemperatureOk) {
    SetTemperatureCtrl(util::program::TEMP_CRYO_OFF);
  } else {
    SetTemperatureCtrl(util::program::TEMP_CRYO_ON);
    mIsTemperatureOk = false;
  }
}

void ProgramProcess::TermoProcess(const int &temperature) {
  printf("Temperature control for TermoProcess.\n");
  if (temperature < mpdu.payload.temp_max && !mIsTemperatureOk) {
    SetTemperatureCtrl(util::program::TEMP_THERM_ON);

  } else {
    SetTemperatureCtrl(util::program::TEMP_THERM_OFF);
    mIsTemperatureOk = true;
  }

  if (temperature > mpdu.payload.temp_min && mIsTemperatureOk) {
    SetTemperatureCtrl(util::program::TEMP_THERM_OFF);

  } else {
    SetTemperatureCtrl(util::program::TEMP_THERM_ON);
    mIsTemperatureOk = false;
  }
}

} // namespace medicalhorse::command
