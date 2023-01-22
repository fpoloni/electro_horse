
#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "Device/HBridge/HBridgeDefinitions.h"
#include "Device/HBridge/I2C/HBridge.h"
#include "Device/Sensor/DS1803.h"
#include "Device/Sensor/MAX6675.h"
#include "Interface/SerialBus/1Wire/OneWire.h"
#include "Interface/SerialBus/SPI/Spi.h"

int max6675_test() {
  auto max_sensor = std::make_unique<medicalhorse::hardware::device::MAX6675>(
      "SPI temperature sensor",
      medicalhorse::hardware::iodefinition::SENSOR_SPI::CH0,
      medicalhorse::hardware::device::definition::temperature::UNIT::CELSIUS);

  max_sensor->Start();
  std::string name = max_sensor->GetName();
  int temperature = 0;
  max_sensor->GetParameter(&temperature);
  max_sensor->Stop();
  return 0;
}

int ds1803_test() {
  auto sensor = std::make_unique<medicalhorse::hardware::device::DS1803>(
      "1-wire temperature sensor",
      medicalhorse::hardware::device::definition::temperature::UNIT::CELSIUS);
  sensor->Start();
  std::string name = sensor->GetName();
  int temperature = 0;
  sensor->GetParameter(&temperature);
  sensor->Stop();
  return 0;
}

int onewire_test() {
  auto onewire = std::make_unique<medicalhorse::hardware::interface::OneWire>();
  onewire->Open();
  onewire->Show();
  onewire->Close();
  return 0;
}

int spi_test() {
  auto spitest = std::make_unique<medicalhorse::hardware::interface::Spi>(
      medicalhorse::hardware::iodefinition::SENSOR_SPI::CH0);
  std::vector<char> message(2);
  assert(spitest != NULL);
  spitest->Open();

  spitest->Read(message.size(), (int *)message.data());
  printf("Data from SPI Rx buffer: ");

  for (int idx = 0; idx < message.size(); idx++)
    printf("%.2X ", message[idx]);
  printf("\n");

  spitest->Close();
  return 0;
}

int main(int argc, char *argv[]) {
  printf("###### TEST - SPI #####\n");
  spi_test();
  printf("###### TEST - ONEWIRE #####\n");
  onewire_test();
  printf("###### TEST - SENSOR MAX6675 #####\n");
  max6675_test();
  printf("###### TEST - SENSOR DS1803 #####\n");
  ds1803_test();
  return 0;
}
