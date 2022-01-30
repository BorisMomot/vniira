//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_BUFFER_PROCESSORS_H
#define VNIIRA_BUFFER_PROCESSORS_H

#include "str_number/str_number.h"
#include <memory>
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
StrNumber getFirstNumber(std::shared_ptr<char[]> buffer, size_t bufReadSize);

/**
 * Вычисляет сумму и xor для последовательности чисел
 * @param buffer - считанные символы
 * @param bufReadSize - количество считанных символов
 * @return сумма чисел и результат xor
 */
std::pair<StrNumber, long long> processBuffer(std::shared_ptr<char[]> &buffer, const size_t bufReadSize );
#endif // VNIIRA_BUFFER_PROCESSORS_H
