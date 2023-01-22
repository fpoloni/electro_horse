

#ifndef MEDICALHORSE_UTIL_STRUCTDATA_H_
#define MEDICALHORSE_UTIL_STRUCTDATA_H_

#include <algorithm>
#include <vector>

namespace medicalhorse {
namespace util {
template <class T>
class StructData {
 public:
  static int GetIndexElement(const std::vector<T> &data, const T &element) {
    auto it = std::find(data.begin(), data.end(), element);
    int retVal = -1;

    if (it != data.end()) {
      retVal = std::distance(data.begin(), it);
    }
    return retVal;
  }

  static std::vector<T> GetSubDataFromElement(const std::vector<T> &data,
                                              const T &element) {
    auto it = std::find(data.begin(), data.end(), element);
    std::vector<T> retVal;

    if (it != data.end()) {
      std::copy(it, data.end(), std::back_inserter(retVal));
    }

    return retVal;
  }
};

template <class T>
class Package {
 public:
  static std::vector<T> data;
};
}  // namespace util
}  // namespace medicalhorse
#endif  // MEDICALHORSE_UTIL_STRUCTDATA_H_
