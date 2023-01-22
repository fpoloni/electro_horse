#ifndef MEDICALHORSE_QUEUE_H_
#define MEDICALHORSE_QUEUE_H_

#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>

namespace medicalhorse::util {
template <class T>
class Queue {
 public:
  Queue() : mReady(false) {}

  void Set(const T data) {
    std::lock_guard<std::mutex> guard(mMutex);
    mQueueData.push_back(data);
    mConditionVariable.notify_one();
    mReady = true;
  }

  T Get() {
    std::unique_lock<std::mutex> guard(mMutex);
    T data;

    if (mQueueData.empty()) {
      mReady = false;
      mConditionVariable.wait(guard, [this] { return mReady; });
    }

    data = mQueueData.front();
    mQueueData.pop_front();

    guard.unlock();
    mConditionVariable.notify_one();

    return data;
  }

  size_t Size() const {
    std::lock_guard<std::mutex> guard(mMutex);
    return mQueueData.size();
  }

  size_t IsEmpty() const {
    std::lock_guard<std::mutex> guard(mMutex);
    return mQueueData.empty();
  }

 private:
  T mData;
  bool mReady;
  std::list<T> mQueueData;
  mutable std::mutex mMutex;
  std::condition_variable mConditionVariable;
};
}  // namespace medicalhorse::util

#endif  // MEDICALHORSE_QUEUE_H_
