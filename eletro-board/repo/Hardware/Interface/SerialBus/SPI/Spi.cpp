
#include "Spi.h"
#include <chrono>
#include <cstring>
#include <thread>

namespace medicalhorse::hardware::interface {

inline std::string select_channel(const iodefinition::SENSOR_SPI SpiChannel) {
  std::string Ret = "";
  switch (SpiChannel) {
  case iodefinition::SENSOR_SPI::CH0: {
    Ret = "0.0";
    break;
  }
  case iodefinition::SENSOR_SPI::CH1: {
    Ret = "0.1";
    break;
  }
  default:
    printf("ERROR: SPI Channel Unavailable.\n");
  }
  return Ret;
}

inline bool transfer(int file, std::vector<char> &pkg_rcv,
                     std::vector<char> &pkg_send, const uint8_t pkg_len) {
  bool retVal = true;
  int ret = -1;
  struct spi_ioc_transfer tr = {.tx_buf = (unsigned long)pkg_send.data(),
                                .rx_buf = (unsigned long)pkg_rcv.data(),
                                .len = pkg_len,
                                .delay_usecs = SPI_DELAY,
                                .bits_per_word = SPI_WORD,
                                .cs_change = 0};

  tr.speed_hz = SPI_FREQ;
  tr.rx_nbits = 8;
  tr.tx_nbits = 8;

  if ((ret = (ioctl(file, SPI_IOC_MESSAGE(1), &tr))) < 1) {
    printf("Can't send SPI message: %d\n", ret);
    retVal = false;
  }
  return retVal;
}

Spi::Spi(const iodefinition::SENSOR_SPI Channel)
    : m_state(CLOSE), m_channel(Channel) {}

bool Spi::Open() {
  bool retval = OPEN;
  uint8_t mode = SPI_WORD;
  printf("Opening SPI connection.\n");

  if (CLOSE == m_state) {
    std::string filename(sysclassdefinition::serialbus::spi);
    filename.append(select_channel(m_channel));
    if ((mFile = open(filename.c_str(), O_RDWR)) < 0) {
      retval = true;
      m_state = OPEN;
    }

    // Set SPI mode
    if (ioctl(mFile, SPI_IOC_RD_MODE, &mode) < 0) {
      printf("Failed to acquire bus access and/or talk to slave.\n");
      retval = false;
    } else {
      printf("Set SPI mode successfully. Path: %s Mode: %d\n", filename.c_str(),
             mode);
    }
  }
  return retval;
}

bool Spi::Close() {
  printf("Closing SPI connection.\n");
  bool retVal = false;

  if (OPEN == m_state) {
    close(mFile);
    m_state = CLOSE;
    retVal = true;
  }

  return retVal;
}

bool Spi::Read(const int reg, int *parameter) {
  std::vector<char> none(0);
  std::vector<char> read(reg);
  bool ret = transfer(mFile, read, none, reg);
  std::memcpy(parameter, read.data(), reg); // OK
  return ret;
}

bool Spi::Write(const int reg, const int parameter) {
  std::vector<char> none(0);
  std::vector<char> write(reg);
  bool ret = transfer(mFile, none, write, reg);
  return ret;
}

} // namespace medicalhorse::hardware::interface
