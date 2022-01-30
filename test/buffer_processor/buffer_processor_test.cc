//
// Created by boris on 26.01.2022.
//
#include <gtest/gtest.h>
#include "buffer_processor/buffer_processors.h"
#include "str_number/str_number.h"
#include <limits>

std::shared_ptr<char[]> getStrBuffer(const std::string& str){
    auto num = std::shared_ptr<char[]>(new char[str.length()]);
    int counter = 0;
    for (const auto& l: str){
        num[counter] = l;
        counter++;
    }
    return num;
}

TEST(buffer_processor, first_number){
    std::string testString = "152 2 3 4 5 6 7 9";
    auto num = getStrBuffer(testString);
    auto firstNumber = getFirstNumber(num, testString.size());
    ASSERT_EQ(firstNumber, 152);
}

TEST(buffer_processor, sum){
    std::string testString = "100 100 100 100 100 100 100";
    auto num = getStrBuffer(testString);
    auto result = processBuffer(num, testString.size());
    ASSERT_EQ(result.first, "700");
}

TEST(buffer_processor, xoring){
    std::string testString = "1 1 1 1 1 1 1";
    auto num = getStrBuffer(testString);
    auto result = processBuffer(num, testString.size());
    ASSERT_EQ(result.second, 1);
    testString = "1 1 1 1 1 1";
    num = getStrBuffer(testString);
    result = processBuffer(num, testString.size());
    ASSERT_EQ(result.second, 0);
}

TEST(buffer_processor, big_sum){
    StrNumber base(std::numeric_limits<long long>::max());
    std::string testString = base.getNumberString();
    for (int i = 0; i < 999; ++i){
        testString += " " + base.getNumberString();
    }
    auto num = getStrBuffer(testString);
    auto result = processBuffer(num, testString.size());
    ASSERT_EQ(result.first.getNumberString(), base.getNumberString() + "000");
}