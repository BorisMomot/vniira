//
// Created by boris on 27.01.2022.
//
#include "result_accumulator/ResultAccumulator.h"
#include "str_number/StrNumber.h"
#include <future>
#include <gtest/gtest.h>
#include <limits>
#include <thread>
#include <vector>


TEST(result_accumulator, sum){
    ResultAccumulator resultAccumulator;
    StrNumber firstNumber(std::numeric_limits<long long>::max());
    resultAccumulator.setFirstNumber(firstNumber);

    for (int i = 0; i < 100; ++i) {
        resultAccumulator.addNumber(std::numeric_limits<long long>::max());
    }
    auto res(resultAccumulator.getTotalSum());
    ASSERT_EQ(res.getNumberString() , std::to_string(std::numeric_limits<long long>::max()) + "00");
}

TEST(result_accumulator, xoring){
    ResultAccumulator resultAccumulator;
    StrNumber firstNumber(std::numeric_limits<long long>::max());

    for (int i = 0; i < 100; ++i) {
        resultAccumulator.xorNumber(111);
    }
    ASSERT_EQ(resultAccumulator.getTotalXor(), 0);
    resultAccumulator.xorNumber(1);
    ASSERT_EQ(resultAccumulator.getTotalXor(), 1);
}

TEST(result_accumulator, mthr_sum){
    ResultAccumulator resultAccumulator;
    StrNumber firstNumber(std::numeric_limits<long long>::max());
    resultAccumulator.setFirstNumber(firstNumber);

    std::vector<std::future<void>> workers{};

    for (int i = 0; i < 10000; ++i) {
        auto work = [&resultAccumulator]() {resultAccumulator.addNumber(std::numeric_limits<long long>::max());};
        workers.emplace_back(std::async(std::launch::async, work));
    }
    for (auto& w:workers){
        w.wait();
    }
    auto res(resultAccumulator.getTotalSum());
    ASSERT_EQ(res.getNumberString() , std::to_string(std::numeric_limits<long long>::max()) + "0000");
}