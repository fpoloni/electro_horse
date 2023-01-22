
#include "Display.h"

#include <vector>

#include "CommandDefinition.h"

namespace medicalhorse::display {
Display::Display() : mIsStarted(true) {}

void Display::Start() {
  printf("DEBUG: Display Start\n");
  mIsStarted = true;
  mEthConnection.Open();
}

void Display::Stop() {
  printf("DEBUG: Display Stop\n");
  mIsStarted = false;
  mEthConnection.Close();
}

int Display::Get(util::pdu_t *output) {
  printf("DEBUG: Display Get\n");
  std::vector<int8_t> data((sizeof(util::pdu_t) / sizeof(int8_t)));

  int retVal = -1;

  if (mIsStarted) {
    if ((retVal = mEthConnection.Read(&data)) > 0) {
      printf("Data from TCP: %d size\n", retVal);
      for (auto element : data) {
        printf("%x, ", element);
      }
      printf("\n");

      // copying the header content data package
      output->head = data[medicalhorse::util::DATAFIELD::HEAD];
      output->tail = data[medicalhorse::util::DATAFIELD::TAIL];
      output->crc = data[medicalhorse::util::DATAFIELD::CRC];

      // getting header content
      std::copy_n(data.begin() + 1, medicalhorse::util::header_size,
                  &output->operation);
      // gettingg payload content
      std::copy_n(data.begin() + medicalhorse::util::payload_start,
                  medicalhorse::util::payload_size, &output->payload.pwm_level);
    }
  }

  return retVal;
}

void Display::Set(const std::vector<int8_t> &package) {
  printf("Data to display: %ld size\n", package.size());
  for (auto element : package) {
    printf("%d, ", element);
  }
  printf("\n");
  mEthConnection.Write(package);
}

} // namespace medicalhorse::display
