//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_BUFFERPROCESSORS_H
#define VNIIRA_BUFFERPROCESSORS_H

#include "StrNumber.h"

/**
 * Исключение на случай недопустимых чисел в последовательности
 */
struct UnAcceptableNumber: public std::exception{
    std::string message;
    UnAcceptableNumber(const std::string &message) : message(message) {}
    ~UnAcceptableNumber() throw() {}
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        return message.c_str();
    }
};

/**
 * Возвращает первое число в последовательности
 * @param buffer - считанные символы
 * @param bufReadSize - количество считанных символов
 * @return - первое число
 */
StrNumber getFirstNumber(std::shared_ptr<char[]> buffer, size_t bufReadSize){
    StrNumber readPartSum{0};
    std::string currentNumber;

    for (int i = 0; i < bufReadSize; ++i) {
        if (buffer[i] == EOF) {break;}
        if (buffer[i] == '.' || buffer[i] == ',' ) {throw UnAcceptableNumber("XOR operation not acceptable for double");}

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
        readPartSum = StrNumber(currentNumber);
        return readPartSum;
    }
    return readPartSum;
}
/**
 * Вычисляет сумму и xor для последовательности чисел
 * @param buffer - считанные символы
 * @param bufReadSize - количество считанных символов
 * @return сумма чисел и результат xor
 */
std::pair<StrNumber, long long> processBuffer(std::shared_ptr<char[]> &buffer, const size_t bufReadSize ) {
    StrNumber readPartSum{0};
    long long partXor{0};

    std::string currentNumber;

    for (int i = 0; i < bufReadSize; ++i) {
        if (buffer[i] == EOF) {break;}
        if (buffer[i] == '.' || buffer[i] == ',' ) {throw UnAcceptableNumber("XOR operation not acceptable for double");}

        // Проверяем что не число
        if ( !isdigit(buffer[i]) ){
            // если первый знак и он минус
            if (buffer[i] == '-' && currentNumber.empty()){
                currentNumber += buffer[i];
                continue;
            }

            // Проверяем что нужно заканчивать число
            if ((buffer[i] == ' ' || buffer[i] == '\n' ) && !currentNumber.empty()){
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
#endif//VNIIRA_BUFFERPROCESSORS_H
