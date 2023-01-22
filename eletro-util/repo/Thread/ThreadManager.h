
#ifndef MEDICALHORSE_THREADMANAGER_H_
#define MEDICALHORSE_THREADMANAGER_H_

#include <algorithm>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace medicalhorse {
namespace util {

class ThreadManager {
 public:
  /**
   * @brief Constructor
   * @param A thread pointer pointer
   */
  ThreadManager(const std::vector<std::shared_ptr<std::thread>> &pThreadList);

  /**
   * @brief Destructor
   */
  virtual ~ThreadManager();

  /**
   * @brief Method to start the created threads
   *
   */
  void Start();

  /**
   * @brief Method to stop the created threads
   */
  void Stop();

 private:
  std::vector<std::shared_ptr<std::thread>> mpThreadList;
};

}  // namespace util
}  // namespace medicalhorse

#endif  // MEDICALHORSE_THREADMANAGER_H_
