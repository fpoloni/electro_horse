

#include "Rele.h"

#include <iostream>

#include "Common.h"
#include "Interface/IO/GPIO.h"
#include "Interface/IO/IODefinition.h"

namespace medicalhorse::hardware::device {

Rele::Rele(const std::string &name)
    : mDeviceName(name), mCurrentProgramState(util::program::ALL) {}

void Rele::Reset() {
  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::FREEZE),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));

  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::HEATER),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));

  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::PUMP),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));
}

bool Rele::Start() {
  interface::GPIO::Add(
      static_cast<int>(hardware::iodefinition::rele::TYPE::FREEZE),
      static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

  interface::GPIO::Add(
      static_cast<int>(hardware::iodefinition::rele::TYPE::HEATER),
      static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

  interface::GPIO::Add(
      static_cast<int>(hardware::iodefinition::rele::TYPE::PUMP),
      static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));
  Reset();

  return true;
}

void Rele::Stop() {
  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::FREEZE),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));

  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::HEATER),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));

  interface::GPIO::Set(
      static_cast<int>(hardware::iodefinition::rele::TYPE::PUMP),
      static_cast<int>(hardware::iodefinition::VALUE::LOW));
}

std::string Rele::GetName() { return mDeviceName; }

bool Rele::SetParameter(const int parameter) {
  mCurrentProgramState = parameter;

  switch (parameter) {
    case util::program::PUMP_ON:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::PUMP),
          static_cast<int>(hardware::iodefinition::VALUE::HIGH));
      break;

    case util::program::PUMP_OFF:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::PUMP),
          static_cast<int>(hardware::iodefinition::VALUE::LOW));
      break;

    case util::program::TEMP_CRYO_ON:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::FREEZE),
          static_cast<int>(hardware::iodefinition::VALUE::HIGH));
      break;
    case util::program::TEMP_CRYO_OFF:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::FREEZE),
          static_cast<int>(hardware::iodefinition::VALUE::LOW));
      break;
    case util::program::TEMP_THERM_ON:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::HEATER),
          static_cast<int>(hardware::iodefinition::VALUE::HIGH));
      break;
    case util::program::TEMP_THERM_OFF:
      interface::GPIO::Set(
          static_cast<int>(hardware::iodefinition::rele::TYPE::HEATER),
          static_cast<int>(hardware::iodefinition::VALUE::LOW));
      break;

    default:
      printf("Invalid reles signal position.\n");
      Reset();
      break;
  }

  return false;
}

bool Rele::GetParameter(int *parameter) {
  if (nullptr != parameter) {
    *parameter = mCurrentProgramState;
    return true;
  }
  return false;
}

void Rele::Set(const int device) {
  interface::GPIO::Set(device,
                       static_cast<int>(hardware::iodefinition::VALUE::HIGH));
}

void Rele::Clear(const int device) {
  interface::GPIO::Set(device,
                       static_cast<int>(hardware::iodefinition::VALUE::LOW));
}

}  // namespace medicalhorse::hardware::device
