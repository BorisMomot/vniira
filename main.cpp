#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <cmath>
#include <vector>

#include "StrNumber.h"
#include "ThreadPool.h"


// Задание:
// Есть многострочный текстовый файл с числами, записанными через пробел. Его размер
// превышает размер имеющейся памяти. Необходимо : - сложить все числа, - вычесть (из первого числа все остальные), - выполнить операцию XOR. Для работы с числами можно использовать не более трех потоков. Необходимо с максимальной скоростью обработать файл. Результатом обработки являются
// три числа. Для решения задачи необходимо использовать STL.
//------------------------------------------------------------------------------------------------
// Уточнения:

enum ParseStatus{
    fail = 0,
    successStop = 1,
    successContinue = 2
};
static void printHelp(std::string name){
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help \tShow this help message\n"
              << "\t-f,--file \tSpecify file for processing"
              << "\t-b,--buffer \tSpecify reading buffer size (default: 1024 x 1024)"
              << std::endl;
}
static std::tuple<int, std::string, size_t> parseArgs (int argc, char** argv){
    std::string fileName;
    size_t bufferSize = 1024 * 1024;

    if (argc < 3) {
        printHelp(argv[0]);
        return std::make_tuple(ParseStatus::fail, "", 0);
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            printHelp(argv[0]);
            return std::make_tuple(ParseStatus::successStop, "", 0);
        } else {
            if ((arg == "-f") || (arg == "--file")) {
                if (i + 1 < argc) {
                    fileName = argv[++i];
                } else {
                    std::cerr << "--file option requires one argument." << std::endl;
                    return std::make_tuple(ParseStatus::fail, "", 0);
                }
            }
            if ((arg == "-b") || (arg == "--buffer")) {
                if (i + 1 < argc) {
                    std::string str(argv[++i]);
                    try {
                        bufferSize = std::stoll(str);
                    } catch (...) {
                        std::cerr << "couldn't convert to number buffer size parameter: " << str << std::endl;
                        return std::make_tuple(ParseStatus::fail, "", 0);
                    }
                }
            }
        }
    }
    return std::make_tuple(ParseStatus::successContinue, fileName, bufferSize);
}

StrNumber getFirstNumber(std::shared_ptr<char[]> buffer, size_t bufReadSize){
    StrNumber readPartSum{0};
    std::string currentNumber;

    for (int i = 0; i < bufReadSize; ++i) {
        if (buffer[i] == EOF) {break;}
        // Проверяем что не число
        if ( !isdigit(buffer[i]) ){
            // если первый знак и он минус
            if (buffer[i] == '-' && currentNumber.empty()){
                currentNumber += buffer[i];
                continue;
            }
            // Проверяем что нужно заканчивать число
            if ((buffer[i] == ' ' || buffer[i] == '\n' ) && !currentNumber.empty()){
                readPartSum = StrNumber(currentNumber);

                return readPartSum;
            } else{
                continue;
            }
        } else {
            currentNumber += buffer[i];
        }
    }

    // Если число первое, оно же единственное
    if(!currentNumber.empty()){
        std::cout << "Result number: " << currentNumber << std::endl;
        readPartSum = StrNumber(currentNumber);
        return readPartSum;
    }
    return readPartSum;
}

//std::pair<StrNumber, long long> processBuffer(std::unique_ptr<char[]> &buffer, const size_t bufReadSize ) {
//    StrNumber readPartSum{0};
//    long long partXor{0};
//
//    std::string currentNumber;
//
//    for (int i = 0; i < bufReadSize; ++i) {
//        if (buffer[i] == EOF) {break;}
//
//        // Проверяем что не число
//        if ( !isdigit(buffer[i]) ){
//            // если первый знак и он минус
//            if (buffer[i] == '-' && currentNumber.empty()){
//                currentNumber += buffer[i];
//                continue;
//            }
//
//            // Проверяем что нужно заканчивать число
//            if ((buffer[i] == ' ' || buffer[i] == '\n' ) && !currentNumber.empty()){
//                std::cout << "Result number: " << currentNumber << std::endl;
//
//                try {
//                    readPartSum += stoll(currentNumber);
//
//                    partXor = ( partXor ^ stoll(currentNumber));
//
//                }catch (const std::exception exception){
//                    std::cerr << exception.what() << " problem: " << currentNumber << std::endl;
//                }
//                currentNumber.clear();
//                continue;
//            } else{
//                continue;
//            }
//        } else {
//            currentNumber += buffer[i];
//        }
//    }
//
//    // clear buffer
//    if(!currentNumber.empty()){
//        std::cout << "Result number: " << currentNumber << std::endl;
//        try {
//            readPartSum += stoll(currentNumber);
//            partXor = ( partXor ^ stoll(currentNumber));
//
//        }catch (const std::exception exception){
//            std::cerr << exception.what() << " problem: " << currentNumber << std::endl;
//        }
//        currentNumber.clear();
//    }
//
//    return std::make_pair(readPartSum, partXor);
//}

std::pair<StrNumber, long long> processBuffer(std::shared_ptr<char[]> &buffer, const size_t bufReadSize ) {
    StrNumber readPartSum{0};
    long long partXor{0};

    std::string currentNumber;

    for (int i = 0; i < bufReadSize; ++i) {
        if (buffer[i] == EOF) {break;}

        // Проверяем что не число
        if ( !isdigit(buffer[i]) ){
            // если первый знак и он минус
            if (buffer[i] == '-' && currentNumber.empty()){
                currentNumber += buffer[i];
                continue;
            }

            // Проверяем что нужно заканчивать число
            if ((buffer[i] == ' ' || buffer[i] == '\n' ) && !currentNumber.empty()){
                std::cout << "Result number: " << currentNumber << std::endl;

                try {
                    readPartSum += stoll(currentNumber);

                    partXor = ( partXor ^ stoll(currentNumber));

                }catch (const std::exception exception){
                    std::cerr << exception.what() << " problem: " << currentNumber << std::endl;
                }
                currentNumber.clear();
                continue;
            } else{
                continue;
            }
        } else {
            currentNumber += buffer[i];
        }
    }

    // clear buffer
    if(!currentNumber.empty()){
        std::cout << "Result number: " << currentNumber << std::endl;
        try {
            readPartSum += stoll(currentNumber);
            partXor = ( partXor ^ stoll(currentNumber));

        }catch (const std::exception exception){
            std::cerr << exception.what() << " problem: " << currentNumber << std::endl;
        }
        currentNumber.clear();
    }

    return std::make_pair(readPartSum, partXor);
}

class Accumulator{
public:
    Accumulator() {}

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
        Accumulator::firstNumber = firstNumber;
    }
    const StrNumber &getTotalSum() const {
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        return totalSum;
    }
    void setTotalSum(const StrNumber &totalSum) {
        std::lock_guard<std::mutex> lockGuard(totalMutex);
        Accumulator::totalSum = totalSum;
    }
    long long int getTotalXor() const {
        std::lock_guard<std::mutex> lockGuard(xorMutex);
        return totalXor;
    }
    void setTotalXor(long long int totalXor) {
        std::lock_guard<std::mutex> lockGuard(xorMutex);
        Accumulator::totalXor = totalXor;
    }
    StrNumber getSubract() const {
        std::scoped_lock scopedLock{firstMutex, totalMutex};
        return firstNumber + firstNumber - totalSum;
    }

    friend std::ostream &operator<<(std::ostream &os, const Accumulator &accumulator) {
        os << "totalSum: " << accumulator.getTotalSum() << " totalSubract: " << accumulator.getSubract()  << " totalXor: " << accumulator.getTotalXor();
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


int main(int argc, char** argv) {
    // Парсим ввод
    auto pResult = parseArgs(argc, argv);
    auto const status = std::get<0>(pResult);
    if (status == ParseStatus::fail) { return EXIT_FAILURE;}
    else if (status == ParseStatus::successStop) {return EXIT_SUCCESS;}

    // Читаем файл
    auto fileName = std::get<1>(pResult);
    auto bufferSize = std::get<2>(pResult);

    Accumulator accumulator;

    std::ifstream bigFile(fileName);
    std::shared_ptr<char[]> buffer(new char[bufferSize]);

    if (bigFile){
        bigFile.read(buffer.get(), bufferSize);
        accumulator.setFirstNumber(getFirstNumber(buffer, bigFile.gcount()) ) ;
        bigFile.clear();
        bigFile.seekg(0);
    }

    ThreadPool threadPool(2);

    const auto prBuffer = [&accumulator] (std::shared_ptr<char[]> buffer, size_t bufReadSize) {
        auto result = processBuffer( buffer, bufReadSize);
        accumulator.addNumber(result.first);
        accumulator.xorNumber(result.second);
    };

    while (bigFile) {
        bigFile.read(buffer.get(), bufferSize);
        threadPool.pushTask(prBuffer, buffer, bigFile.gcount());
    }

    threadPool.waitForTasks();
    std::cout << accumulator << std::endl;
    return EXIT_SUCCESS;
}


