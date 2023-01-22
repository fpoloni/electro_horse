/**
 * @author Fabricio Poloni
 * Class for GPIO control of the Raspberry. Thus
 * export, direction and level control.
 *
 */

#ifndef MEDICALHORSE_GPIO_H_
#define MEDICALHORSE_GPIO_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

#include "Error.h"

namespace medicalhorse::hardware::interface {

class GPIO {
 private:
  static const int bufferPinId_ = 3;
  static const int bufferDirectionPin_ = 35;

 public:
  static int Add(int pin, int mode) {
    if (NO_ERROR != Export(pin)) {
      return OP_ERROR;
    }

    if (NO_ERROR != Direction(pin, mode)) {
      return OP_ERROR;
    }

    return NO_ERROR;
  }

  static int Remove(int pin) {
    if (NO_ERROR != Unexport(pin)) {
      return OP_ERROR;
    }

    return NO_ERROR;
  }

  static int Get(int pin, int *value) {
    if (nullptr != value) {
      *value = Read(pin);
    }
    return NO_ERROR;
  }

  static int Set(int pin, int value) {
    Write(pin, value);
    return NO_ERROR;
  }

 private:
  static int Export(int pin) {
    char buffer[GPIO::bufferPinId_];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
      fprintf(stderr, "Failed to open export for writing!\n");
      return (-1);
    }

    bytes_written = snprintf(buffer, GPIO::bufferPinId_, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return (0);
  }

  static int Unexport(int pin) {
    char buffer[GPIO::bufferPinId_];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
      fprintf(stderr, "Failed to open unexport for writing!\n");
      return (-1);
    }

    bytes_written = snprintf(buffer, GPIO::bufferPinId_, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return (0);
  }

  static int Direction(int pin, int dir) {
    static const char s_directions_str[] = "in\0out";

    char path[GPIO::bufferDirectionPin_];
    int fd;

    snprintf(path, GPIO::bufferDirectionPin_,
             "/sys/class/gpio/gpio%d/direction", pin);
    // printf("debug - BufferDirectionPin: %s%d\n", path,
    // GPIO::bufferDirectionPin_);

    fd = open(path, O_WRONLY);
    if (-1 == fd) {
      fprintf(stderr, "Failed to open gpio direction for writing!\n");
      return (-1);
    }

    if (-1 ==
        write(fd, &s_directions_str[0 == dir ? 0 : 3], 0 == dir ? 2 : 3)) {
      fprintf(stderr, "Failed to set direction!\n");
      return (-1);
    }

    close(fd);
    return (0);
  }

  static int Read(int pin) {
    char path[GPIO::bufferDirectionPin_];
    char value_str[3];
    int fd;

    snprintf(path, GPIO::bufferDirectionPin_, "/sys/class/gpio/gpio%d/value",
             pin);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
      fprintf(stderr, "Failed to open gpio value for reading!\n");
      return (-1);
    }

    if (-1 == read(fd, value_str, 3)) {
      fprintf(stderr, "Failed to read value!\n");
      return (-1);
    }

    close(fd);
    return atoi(value_str);
  }

  static int Write(int pin, int value) {
    static const char s_values_str[] = "01";

    char path[GPIO::bufferDirectionPin_];
    int fd;

    snprintf(path, GPIO::bufferDirectionPin_, "/sys/class/gpio/gpio%d/value",
             pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
      fprintf(stderr, "Failed to open gpio value for writing!\n");
      return (-1);
    }

    if (1 != write(fd, &s_values_str[0 == value ? 0 : 1], 1)) {
      fprintf(stderr, "Failed to write value!\n");
      return (-1);
    }

    close(fd);
    return 0;
  }
};

}  // namespace medicalhorse::hardware::interface

#endif  // MEDICALHORSE_IOCONTROL_H_
