
#ifndef MEDICALHORSE_PACKAGE_H_
#define MEDICALHORSE_PACKAGE_H_

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

namespace medicalhorse {
namespace util {

// number of bytes
const uint8_t header_start = 1;
const uint8_t header_size = 5;
const uint8_t payload_start = 6;
const uint8_t payload_size = 6;

/**
 * @brief Index field to build the package data
 * to set/get.
 */
enum DATAFIELD : uint8_t {
  HEAD = 0,       // idx start 00 - len 1
  OPERATION = 1,  // idx start 01 - len 1
  LEN = 2,        // idx start 02 - len 1
  PROGRAM = 3,    // idx start 01 - len 1
  STATE = 4,      // idx start 01 - len 1
  DEVICE = 5,     // idx start 01 - len 1
  PAYLOAD = 6,    // idx start 03 - len 6
  CRC = 12,       // idx start 10 - len 2
  TAIL = 13       // idx start 12 - len 1
};

/**
 * @brief Structure to get/set the package unit data from
 * the selected program.
 */
typedef struct {
  int8_t pwm_level;     // adjut the motor intensit according to pwm value
  int8_t temp_min;      // temperature range of the cryo/therm
  int8_t temp_max;      // temperature range of the cryo/therm
  int8_t temp_current;  // current temperature value cryo/therm
  int8_t time;          // period of time to program run
  int8_t status;        // indicates the program status

} payload_t;

/**
 * @brief Complete package used to communication
 */
typedef struct {
  int8_t head;        // begin of package
  int8_t operation;   // read or write operation
  int8_t len;         // total package size
  int8_t program;     // program name to start
  int8_t state;       // start, stop or cancel state
  int8_t device;      // select specific device to set/get
  payload_t payload;  // program field content
  int8_t crc;         // CRC check
  int8_t tail;        // end of package

} pdu_t;

typedef struct {
  int8_t minimum_package_size;
  int8_t maximum_package_size;

} limitPackage_t;

class Package {
 public:
  Package() { mDataPackage = std::vector<int8_t>(TAIL + 1); }

  bool Set(const std::vector<int8_t> &input) {
    mDataPackage = input;
    return true;
  }

  bool Set(int8_t *data, const int8_t len, const DATAFIELD field) {
    uint8_t idx_data = 0;
    if (nullptr == data && (field < HEAD || field > TAIL)) {
      return false;
    }

    for (int idx = field; idx < (len + field); idx++) {
      mDataPackage[idx] = data[idx_data++];
    }

    return true;
  }

  bool Get(std::vector<int8_t> &data, const DATAFIELD field) {
    if (field < HEAD || field > TAIL) {
      return false;
    }
    std::copy_n(mDataPackage.begin() + field, GetFieldLen(field),
                std::back_inserter(data));
    return true;
  }

  bool Get(std::vector<int8_t> &data, const int8_t len) {
    std::copy_n(mDataPackage.begin(), len, std::back_inserter(data));
    return true;
  }

  void Show() {
    std::vector<std::string> pdu_label = {
        "head, operation, len, program, state, device, payload, tail"};

    for (auto element : pdu_label) printf("| %s ", element.c_str());

    printf("\r\n");

    for (auto element : mDataPackage) printf("| 0x%x ", element);

    printf("\r\n");
  }

 private:
  int8_t GetFieldLen(const DATAFIELD field) {
    int8_t retVal = 0;
    switch (field) {
      case PAYLOAD:
        retVal = 6;
        break;
      case CRC:
        retVal = 2;
        break;

      case TAIL:
      case HEAD:
      case LEN:
      case STATE:
      case OPERATION:
        retVal = 1;
        break;

      default:
        printf("Invalid field: %d\n", field);
        break;
    }

    return retVal;
  }

 private:
  std::vector<int8_t> mDataPackage;
};
}  // namespace util
}  // namespace medicalhorse

#endif  // MEDICALHORSE_PACKAGE_H_
