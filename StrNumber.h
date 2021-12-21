//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_STRNUMBER_H
#define VNIIRA_STRNUMBER_H

#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Класс для работы с большими числами
 */

class StrNumber {
public:

    StrNumber(std::string number);
    StrNumber(long long number);

    /**
     * Возвращает число в формате строки
     * @return число в формате строки
     */
    std::string getNumberString();

    /**
     * Установить значение числа из строки
     * @param str - новое значние в формате строки
     * @return новое значние
     */
    StrNumber setNumberString(const std::string &str);

    StrNumber add(StrNumber other);
    StrNumber subtract(StrNumber other);

    bool equals(const StrNumber &other);
    bool equals(const long long &other);
    bool equals(const std::string &other);

    bool isNegative() const;

    /**
     * Умножение на -1
     * @return возвращает число с инвертированным знаком
     */
    StrNumber negate();

    /**
     * Удаяем не значащие нули
     * @return число без обрезанных нулей
     */
    StrNumber deleteZeros();

    friend std::ostream &operator<<(std::ostream &os, const StrNumber &num);

    friend StrNumber operator+(StrNumber n1, const StrNumber &n2);
    friend StrNumber operator+(StrNumber n1, const long long &n2);
    friend StrNumber operator+(StrNumber n1, const std::string &n2);

    friend StrNumber operator-(StrNumber n1, const StrNumber &n2);
    friend StrNumber operator-(StrNumber n1, const long long &n2);
    friend StrNumber operator-(StrNumber n1, const std::string &n2);

    friend bool operator==(StrNumber n1, const StrNumber &n2);
    friend bool operator==(StrNumber n1, const long long &n2);
    friend bool operator==(StrNumber n1, const std::string &n2);

    friend bool operator>(StrNumber n1, const StrNumber &n2);
    friend bool operator<(StrNumber n1, const StrNumber &n2);
    friend bool operator>=(StrNumber n1, const StrNumber &n2);
    friend bool operator<=(StrNumber n1, const StrNumber &n2);

    StrNumber& operator=(const StrNumber &other);
    StrNumber& operator=(const long long &other);
    StrNumber& operator=(const std::string &other);

    StrNumber& operator+=(const StrNumber &other);
    StrNumber& operator+=(const long long &other);
    StrNumber& operator+=(const std::string &other);

    StrNumber& operator-=(const StrNumber &other);
    StrNumber& operator-=(const long long &other);
    StrNumber& operator-=(const std::string &other);

    unsigned int operator[](int index);

private:
    std::string numberString; // хранение числа

    //Основные методы       
    StrNumber addstr(const std::string &other);
    StrNumber addll(const long long &other);
    StrNumber subtractstr(const std::string  &other);
    StrNumber subtractll(const long long &other);
};




#endif//VNIIRA_STRNUMBER_H
