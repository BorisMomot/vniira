//
// Created by boris on 28.01.2022.
//

#include "buffer_pool/buffer_pool.h"

BufferPool::BufferPool(size_t bufferSize,
                       size_t amountOfBuffers, bool cleanData)
    : cleanData(cleanData), bufferSize(bufferSize), amountOfBuffers(amountOfBuffers)
      {
  initBuffers(amountOfBuffers);
}

void BufferPool::initBuffers(size_t initialCapacity) {
  for (int i = 0; i < initialCapacity; ++i){
    freeBuffers.emplace(std::shared_ptr<char[]> (new char[bufferSize]));
  }
}

BufferPool::~BufferPool() {}

std::shared_ptr<char[]> BufferPool::getBuffer() {
  std::lock_guard<std::mutex> lockGuard(buffersMutex);
  if (freeBuffers.size() > 0){
    auto buf = freeBuffers.top();
    freeBuffers.pop();
    return buf;
  } else {
    initBuffers(amountOfBuffers);
    auto buf = freeBuffers.top();
    freeBuffers.pop();
    return buf;
  }
}

void BufferPool::returnBuffer(std::shared_ptr<char[]> &buffer) {
  std::lock_guard<std::mutex> lockGuard(buffersMutex);
  if (cleanData){
    for (int i = 0; i < bufferSize; ++i){
      buffer[i] = ' ';
    }
  }
  freeBuffers.emplace(buffer);
}

size_t BufferPool::getAmountOfBuffers() const { return freeBuffers.size(); }

size_t BufferPool::getSizeOfBuffers() const { return bufferSize; }
