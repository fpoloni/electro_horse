
#include "HandlePackage.h"

#include <iostream>

namespace medicalhorse {
namespace util {
namespace handlepackage {

int8_t HandlePackage::mFixedElementLen = 6;

inline void Verbose(const pdu_t pdu) {
  std::vector<std::string> pdu_label = {
      "head, operation, len, program, state, device, payload, tail"};

  printf("head:%x operation:%x len:%x program:%x state:%x device:%x \n",
         pdu.head, pdu.operation, pdu.len, pdu.program, pdu.state, pdu.device);
}

std::shared_ptr<Package> HandlePackage::Build(pdu_t pdu) {
  pdu.len = sizeof(pdu_t);
  std::shared_ptr<Package> pPackage = std::make_shared<Package>();

  pPackage->Set(&pdu.head, 1, medicalhorse::util::DATAFIELD::HEAD);
  pPackage->Set(&pdu.operation, 1, medicalhorse::util::DATAFIELD::OPERATION);
  pPackage->Set(&pdu.len, 1, medicalhorse::util::DATAFIELD::LEN);
  pPackage->Set(&pdu.device, 1, medicalhorse::util::DATAFIELD::DEVICE);
  pPackage->Set(&pdu.program, 1, medicalhorse::util::DATAFIELD::PROGRAM);
  pPackage->Set(&pdu.state, 1, medicalhorse::util::DATAFIELD::STATE);

  pPackage->Set(reinterpret_cast<int8_t *>(&pdu.payload), sizeof(pdu.payload),
                medicalhorse::util::DATAFIELD::PAYLOAD);
  pPackage->Set(&pdu.crc, 1, medicalhorse::util::DATAFIELD::CRC);
  pPackage->Set(&pdu.tail, 1, medicalhorse::util::DATAFIELD::TAIL);

  return pPackage;
}

bool HandlePackage::GetPayload(const std::shared_ptr<Package> &pPackage,
                               pdu_t *pdu) {
  std::vector<int8_t> value;

  if (nullptr == pdu) {
    return false;
  }

  if (pPackage->Get(value, (sizeof(pdu_t) + sizeof(pdu->payload) - 1))) {
    std::copy_n(value.begin(), value.size(), reinterpret_cast<int8_t *>(pdu));
  }

  if (pdu->head != 0x7E || pdu->tail != 0x7E) {
    return false;
  }

  return true;
}

bool HandlePackage::Validate(pdu_t pdu, bool isVerbose) {
  bool retVal = true;
  printf("head and tail: %x %x\n", pdu.head, pdu.tail);
  if (pdu.head != 0x7E || pdu.tail != 0x7E) {
    retVal = false;
  }

  (void)isVerbose;
  return retVal;
}

}  // namespace handlepackage
}  // namespace util
}  // namespace medicalhorse
