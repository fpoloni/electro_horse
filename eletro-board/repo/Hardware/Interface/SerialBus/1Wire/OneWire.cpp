
#include "OneWire.h"

#include <cstring>
#include <thread>
#include <vector>

#define ONEWIRE_GPIO "sudo modprobe w1-gpio"
#define ONEWIRE_THERM "sudo modprobe w1-therm"
#define DATA_LEN 5

namespace medicalhorse::hardware::interface {

inline void sensor_init() {
  system(ONEWIRE_GPIO);
  system(ONEWIRE_THERM);
}

inline std::string build_cmd(const std::string sensor_id) {
  std::string ret = "";
  const std::string const_temp_word = "/temperature";
  ret.append(sysclassdefinition::serialbus::onewire)
      .append(sensor_id)
      .append(const_temp_word);
  return ret;
}

inline bool check_sensor_id(char *sensor_id) {
  bool ret = false;
  if (nullptr != sensor_id) {
    ret = strstr(sensor_id,
                 sysclassdefinition::serialbus::sbtsensor::keyword.c_str());
  }
  return ret;
}

inline DIR *open_sensor_dir() {
  return opendir(sysclassdefinition::serialbus::onewire.c_str());
}

inline void close_sensor_dir(DIR *directory) { closedir(directory); }

inline int open_sensor_file(const char *path) { return open(path, O_RDONLY); }

inline void close_sensor_file(const int fd) { close(fd); }

bool OneWire::Open() {
  DIR *directory;
  struct dirent *direntp;

  sensor_init();

  if (nullptr != (directory = open_sensor_dir())) {
    while (nullptr != (direntp = readdir(directory))) {
      if (check_sensor_id(direntp->d_name)) {
        mListOfDevicesPath.push_back(build_cmd(direntp->d_name));
      }
    }

    close_sensor_dir(directory);
  }

  return !mListOfDevicesPath.empty();
}

bool OneWire::Read(const int reg, int *parameter) {
  std::vector<char> currentDeviceData(DATA_LEN);
  bool retVal = false;
  int fd = -1;

  if ((fd = open_sensor_file(mListOfDevicesPath[reg].c_str())) >= 0) {
    if (read(fd, &currentDeviceData[0], currentDeviceData.size()) >= 0) {
      *parameter = std::stoi(currentDeviceData.data());
      retVal = true;
    }
  }

  close_sensor_file(fd);

  return retVal;
}

bool OneWire::Write(const int reg, const int parameter) { return true; }

bool OneWire::Close() { return true; }

int OneWire::Size() { return mListOfDevicesPath.size(); }

void OneWire::Show() {
  printf("Sensor Path List\n");
  for (auto element : mListOfDevicesPath) {
    printf("%s\n", element.c_str());
  }
  printf("\n");
}

} // namespace medicalhorse::hardware::interface
