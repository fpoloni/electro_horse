
#include "ThreadManager.h"

namespace medicalhorse {
namespace util {

ThreadManager::ThreadManager(
    const std::vector<std::shared_ptr<std::thread>> &pThreadList)
    : mpThreadList(pThreadList) {}

ThreadManager::~ThreadManager() {}

void ThreadManager::Start() {}

void ThreadManager::Stop() {
}

}  // namespace util
}  // namespace medicalhorse
