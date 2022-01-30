//
// Created by boris on 28.01.2022.
//

#ifndef VNIIRA_BUFFERPOOL_H
#define VNIIRA_BUFFERPOOL_H

#include <stack>
#include <memory>
#include <mutex>

class BufferPool {
  bool cleanData{false};
  size_t bufferSize;
  size_t amountOfBuffers;
  std::mutex buffersMutex;
  std::stack< std::shared_ptr<char[]> > freeBuffers;
  void initBuffers(size_t initialCapacity);
public:
  BufferPool(size_t bufferSize, size_t amountOfBuffers, bool cleanData = false);
  virtual ~BufferPool();

  size_t getAmountOfBuffers() const;
  size_t getSizeOfBuffers() const;

  std::shared_ptr<char[]> getBuffer();
  void returnBuffer(std::shared_ptr<char[]>& buffer);
};

#endif // VNIIRA_BUFFERPOOL_H
