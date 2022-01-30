//
// Created by boris on 28.01.2022.
//
#include <gtest/gtest.h>
#include <future>
#include "buffer_pool/buffer_pool.h"

TEST(buffer_pool, create){
  BufferPool bufferPool1(1024, 10);
  ASSERT_EQ(bufferPool1.getAmountOfBuffers(), 10);

  BufferPool bufferPool2(10, 1024);
  ASSERT_EQ(bufferPool2.getAmountOfBuffers(), 1024);

  BufferPool bufferPool3(1024, 10, true);
  ASSERT_EQ(bufferPool3.getAmountOfBuffers(), 10);
}

TEST(buffer_pool, get_and_return_buffer){
  BufferPool bufferPool(100, 10);
  {
    auto buf = bufferPool.getBuffer();
    ASSERT_EQ(bufferPool.getAmountOfBuffers(), 9);
    bufferPool.returnBuffer(buf);
  }
  ASSERT_EQ(bufferPool.getAmountOfBuffers(), 10);
}

TEST(buffer_pool, check_cleaning){
  BufferPool bufferPool(100, 10, true);
  {
    auto buf = bufferPool.getBuffer();
    ASSERT_EQ(bufferPool.getAmountOfBuffers(), 9);
    size_t counter = 0;
    for (const auto c : "some string") {
      buf[counter] = c;
      counter++;
    }
    bufferPool.returnBuffer(buf);
  }
  ASSERT_EQ(bufferPool.getAmountOfBuffers(), 10);
  auto buf = bufferPool.getBuffer();
  for (int i = 0; i < bufferPool.getSizeOfBuffers(); ++i){
    ASSERT_EQ(buf[i], ' ');
  }
}

TEST(buffer_pool, check_not_cleaning){
  BufferPool bufferPool(100, 10);
  {
    auto buf = bufferPool.getBuffer();
    ASSERT_EQ(bufferPool.getAmountOfBuffers(), 9);
    size_t counter = 0;
    for (const auto c : "some string") {
      buf[counter] = c;
      counter++;
    }
    bufferPool.returnBuffer(buf);
  }
  ASSERT_EQ(bufferPool.getAmountOfBuffers(), 10);
  auto buf = bufferPool.getBuffer();
  int counter = 0;
  for (const auto c: "some string"){
    ASSERT_EQ(buf[counter], c);
    counter++;
  }
}

TEST(buffer_pool, check_elestic){
  BufferPool bufferPool(100, 10);
  std::vector<std::shared_ptr<char[]>> temp_storage(20);
  for (auto& slot:temp_storage){
    slot = bufferPool.getBuffer();
  }
  ASSERT_EQ(bufferPool.getAmountOfBuffers(), 0);
  for (auto& slot:temp_storage){
    bufferPool.returnBuffer(slot);
  }
  ASSERT_EQ(bufferPool.getAmountOfBuffers(), 20);
}

TEST(buffer_pool, multithread){
  BufferPool bufferPool(100, 10);
  std::vector<std::future<void>> results;

  auto filler = [&bufferPool](){
    auto buf = bufferPool.getBuffer();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    buf[0] = 'a';
    bufferPool.returnBuffer(buf);
    };

  for (int i = 0; i < 100; i++){
    auto task = std::async(std::launch::async, filler);
    results.emplace_back(std::move(task));
  }
  for (auto& r:results){
    r.wait();
  }
  ASSERT_EQ(bufferPool.getBuffer()[0], 'a');
}
// Проверить работу в нескольких потоках