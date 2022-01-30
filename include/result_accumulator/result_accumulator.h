//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_RESULT_ACCUMULATOR_H
#define VNIIRA_RESULT_ACCUMULATOR_H
#include "str_number/str_number.h"
#include <memory>
#include <mutex>

class ResultAccumulator {
public:
    ResultAccumulator() {}

    void addNumber(const StrNumber& number){
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        totalSum += number;
    }

    void xorNumber(const long long number){
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        totalXor ^= number;
    }

    const StrNumber &getFirstNumber1() const {
        std::lock_guard<std::mutex> lockGuard(firstMutex);
        return firstNumber;
    }
    void setFirstNumber(const StrNumber &firstNumber) {
        std::lock_guard<std::mutex> lockGuard(firstMutex);
        ResultAccumulator::firstNumber = firstNumber;
    }
    const StrNumber &getTotalSum() const {
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        return totalSum;
    }
    void setTotalSum(const StrNumber &totalSum) {
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        ResultAccumulator::totalSum = totalSum;
    }
    long long int getTotalXor() const {
        std::lock_guard<std::mutex> lockGuard(xorMutex);
        return totalXor;
    }
    void setTotalXor(long long int totalXor) {
        std::lock_guard<std::mutex> lockGuard(xorMutex);
        ResultAccumulator::totalXor = totalXor;
    }
    StrNumber getSubtract() const {
        std::scoped_lock scopedLock{firstMutex, totalMutex};
        return firstNumber + firstNumber - totalSum;
    }

    friend std::ostream &operator<<(std::ostream &os, const ResultAccumulator &accumulator) {
        os << "totalSum: " << accumulator.getTotalSum() << " totalSubtract: " << accumulator.getSubtract()  << " totalXor: " << accumulator.getTotalXor();
        return os;
    }

private:
    mutable std::mutex firstMutex;
    StrNumber firstNumber{0};
    mutable std::mutex totalMutex;
    StrNumber totalSum{0};
    mutable std::mutex xorMutex;
    long long totalXor{0};
};

#endif // VNIIRA_RESULT_ACCUMULATOR_H
