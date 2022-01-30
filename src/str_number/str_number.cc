//
// Created by boris on 21.12.2021.
//

#include "str_number/str_number.h"
#include <sstream>
#include <iostream>

StrNumber::StrNumber(std::string number) : numberString(number)
{
}

StrNumber::StrNumber(long long number) : numberString(std::to_string(number))
{}

std::string StrNumber::getNumberString() {
    return this->numberString;
}

StrNumber StrNumber::setNumberString(const std::string &str) {
    this->numberString = str;
    return *this;
}

StrNumber StrNumber::add(StrNumber other) {
    StrNumber n1 = other > *this ? other : *this;
    StrNumber n2 = other > *this ? *this : other;
    if (n1.isNegative() || n2.isNegative()) {
        if (n1.isNegative() && n2.isNegative()) {
            return n1.negate().add(n2.negate()).negate();
        }
        else if (n1.isNegative() && !n2.isNegative()) {
            return n1.negate().subtract(n2).negate();
        }
        else {
            return n2.negate().subtract(n1).negate();
        }
    }
    std::string results;
    int carry = 0;
    int diff = int(n1.numberString.size() - n2.numberString.size());
    for (int i = 0; i < diff; ++i) {
        n2.numberString.insert(n2.numberString.begin(), '0');
    }
    for (int i = int(n1.numberString.size() - 1); i >= 0; --i) {
        int sum = (n1.numberString[i] - '0') + (n2.numberString[i] - '0') + carry;
        carry = 0;
        if (sum <= 9 || i == 0) {
            results.insert(0, std::to_string(sum));
        }
        else {
            results.insert(0, std::to_string(sum % 10));
            carry = 1;
        }
    }
    return StrNumber(results);
}

StrNumber StrNumber::subtract(StrNumber other) {
    StrNumber n1 = *this, n2 = other;
    if (n1.isNegative() || n2.isNegative()) {
        if (n1.isNegative() && n2.isNegative()) {
            return n1.negate().add(n2.negate()).negate();
        }
        else if (n1.isNegative() && !n2.isNegative()) {
            return n1.negate().add(n2).negate();
        }
        else {
            return n2.negate().add(n1);
        }
    }
    std::string results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (n1 < n2) {
        //Negative answer
        std::string t = n2.subtract(*this).negate().getNumberString();
        for (unsigned int i = 1; i < t.length(); ++i) {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return StrNumber(t);
    }

    if (n1.numberString.size() - n2.getNumberString().size() > 1) {
        for (unsigned long i = 0; i < n1.numberString.size() - n2.getNumberString().size() - 1; ++i) {
            n2.numberString.insert(n2.numberString.begin(), '0');
        }
    }
    int i = int(n1.numberString.size() - 1);
    for (int j = int(n2.numberString.size() - 1); j >= 0; --j) {
        if (((n1.numberString[i] - '0') < (n2.numberString[j] - '0')) && i > 0) {
            n = char((n1.numberString[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || n1.numberString[i - 1] != '0') {
                p = char((n1.numberString[i - 1] - '0') - 1);
                if (p == -1) {
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if (shouldBeTen) {
                int index = i - 1;
                for (int a = i - 1; (n1.numberString[a] - '0') == 0; --a) {
                    n1.numberString[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (n1.numberString[index] - '0') - 1;
                n1.numberString[index] = static_cast<char>(t + '0');
            }
            n1.numberString[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if (((n1.numberString[i] - '0') == (n2.numberString[j] - '0'))) {
            ss << "0";
        }
        else {
            if (n <= 0) {
                ss << ((n1.numberString[i] - '0') - (n2.numberString[j] - '0'));
            }
            else {
                ss << (n - (n2.numberString[j] - '0'));
            }
        }

        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if (takeOffOne) {
        std::string number = "";
        for (int j = n1.numberString.length() - n2.numberString.length() - 1; j >= 0; --j) {
            if (n1.numberString[j] == '0') {
                number += "0";
                continue;
            }
            else {
                number.insert(number.begin(), n1.numberString[j]);
                int t = atoi(number.c_str());
                --t;
                n1.numberString.replace(0, number.size(), std::to_string(t));
                break;
            }
        }
    }
    while (i >= 0) {
        std::stringstream ss;
        if (i == 0) {
            if (n1.numberString[i] - '0' != 0) {
                ss << (n1.numberString[i] - '0');
                results.insert(0, ss.str());
            }
        }
        else {
            ss << (n1.numberString[i] - '0');
            results.insert(0, ss.str());
        }

        --i;
    }
    if (results.find_first_not_of('0') == std::string::npos) {
        results = "0";
    }
    else if (results[0] == '0') {
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return StrNumber(results);
}

bool StrNumber::equals(const StrNumber &other) {
    return this->numberString == other.numberString;
}

bool StrNumber::equals(const long long &other) {
    return this->getNumberString() == std::to_string(other);
}

bool StrNumber::equals(const std::string &other) {
    return this->getNumberString() == other;
}

bool StrNumber::isNegative() const {
    return this->numberString[0] == '-';
}

StrNumber StrNumber::negate() {
    if (this->numberString[0] == '-') {
        this->numberString.erase(0, 1);
    }
    else {
        this->numberString.insert(this->numberString.begin(), '-');
    }
    return *this;
}

StrNumber StrNumber::deleteZeros() {
    StrNumber b = *this;
    if (b.numberString.find_first_not_of('0') != std::string::npos) {
        b.setNumberString(b.numberString.erase(0, b.numberString.find_first_not_of('0')));
    }
    return b;
}

StrNumber StrNumber::addll(const long long &other) {
    return this->add(StrNumber(other));
}

StrNumber StrNumber::addstr(const std::string &other) {
    return this->add(StrNumber(other));
}

StrNumber StrNumber::subtractll(const long long &other) {
    return this->subtract(StrNumber(other));
}

StrNumber StrNumber::subtractstr(const std::string &other) {
    return this->subtract(StrNumber(other));
}
//-----------------------------------------------------------------------------------------
// Operators
//-----------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const StrNumber &num) {
    os << num.numberString;
    return os;
}

StrNumber operator+(StrNumber n1, const StrNumber &n2) {
    return n1.add(n2);
}

StrNumber operator+(StrNumber n1, const long long &n2) {
    return n1.addll(n2);
}

StrNumber operator+(StrNumber n1, const std::string &n2) {
    return n1.addstr(n2);
}

StrNumber operator-(StrNumber n1, const StrNumber &n2) {
    return n1.subtract(n2);
}

StrNumber operator-(StrNumber n1, const long long &n2) {
    return n1.subtractll(n2);
}

StrNumber operator-(StrNumber n1, const std::string &n2) {
    return n1.subtractstr(n2);
}

bool operator==(StrNumber n1, const StrNumber &n2) {
    return n1.equals(n2);
}

bool operator==(StrNumber n1, const long long &n2) {
    return n1.equals(n2);
}

bool operator==(StrNumber n1, const std::string &n2) {
    return n1.equals(n2);
}

bool operator>(StrNumber n1, const StrNumber &n2) {
    if (n1.isNegative() || n2.isNegative()) {
        if (n1.isNegative() && n2.isNegative()) {
            StrNumber bt = n2;
            n1.numberString.erase(0, 1);
            bt.numberString.erase(0, 1);
            return n1 < bt;
        }
        else {
            return !(n1.isNegative() && !n2.isNegative());
        }
    }
    n1 = n1.deleteZeros();
    auto c = StrNumber(n2);
    c = c.deleteZeros();
    if (n1 == c) {
        return false;
    }
    if (n1.numberString.size() > c.numberString.size()) {
        return true;
    }
    else if (c.numberString.size() > n1.numberString.size()) {
        return false;
    }
    else {
        for (unsigned int i = 0; i < n1.numberString.size(); ++i) {
            if (n1[i] == static_cast<unsigned int>(c.numberString[i] - '0')) {
                continue;
            }
            return n1[i] > static_cast<unsigned int>(c.numberString[i] - '0');
        }
    }
    return false;
}

bool operator<(StrNumber n1, const StrNumber &n2) {
    return !(n1 == n2) && !(n1 > n2);
}

bool operator>=(StrNumber n1, const StrNumber &n2) {
    return n1 > n2 || n1 == n2;
}

bool operator<=(StrNumber n1, const StrNumber &n2) {
    return n1 < n2 || n1 == n2;
}

unsigned int StrNumber::operator[](int index) {
    if (this->numberString[index] == '-') {
        std::cerr << "Negative sign from number" << std::endl;
    }
    return static_cast<unsigned int>(this->numberString[index] - '0');
}

StrNumber& StrNumber::operator=(const StrNumber &other) {
    this->numberString = other.numberString;
    return *this;
}

StrNumber& StrNumber::operator=(const long long &other) {
    this->numberString = std::to_string(other);
    return *this;
}

StrNumber& StrNumber::operator=(const std::string &other) {
    this->numberString = other;
    return *this;
}

StrNumber& StrNumber::operator+=(const StrNumber &other) {
    *this = *this + other;
    return *this;
}

StrNumber& StrNumber::operator+=(const long long &other) {
    *this = *this + other;
    return *this;
}

StrNumber& StrNumber::operator+=(const std::string &other) {
    *this = *this + other;
    return *this;
}

StrNumber& StrNumber::operator-=(const StrNumber &other) {
    *this = *this - other;
    return *this;
}

StrNumber& StrNumber::operator-=(const long long &other) {
    *this = *this - other;
    return *this;
}

StrNumber& StrNumber::operator-=(const std::string &other) {
    *this = *this - other;
    return *this;
}



