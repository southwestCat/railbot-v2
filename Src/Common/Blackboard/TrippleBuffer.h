/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 19:45:17
 * @FilePath: /railbot-v2/Src/Common/Blackboard/TrippleBuffer.h
 * @Description:
 *
 */
#pragma once

#include <memory>
#include <ostream>

template <typename T>
class TrippleBuffer {
 public:
  TrippleBuffer() : writting(0), reading(0), newest(0) {
    for (int i = 0; i < NUM; i++) {
      data[i] = std::make_unique<T>();
    }
  }

  void write(const T& t) {
    writting = 0;
    if (newest != 0 && reading != 0) writting = 0;
    else if (newest != 1 && reading != 1) writting = 1;
    else if (newest != 2 && reading != 2) writting = 2;
    assert(writting < NUM);
    *data[writting] = t;
    newest = writting;
  }

  T read() {
    reading = newest;
    assert(data[reading] != nullptr);
    return *data[reading];
  }

  friend std::ostream& operator<<(std::ostream& o, const TrippleBuffer& t) {
    o << t.data[0].get() << std::endl;
    o << t.data[1].get() << std::endl;
    o << t.data[2].get();
    return o;
  }

 private:
  enum { NUM = 3 };
  std::unique_ptr<T> data[NUM];
  volatile int writting;
  volatile int reading;
  volatile int newest;
};