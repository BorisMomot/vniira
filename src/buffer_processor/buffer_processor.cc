//
// Created by boris on 30.01.2022.
//
#include <buffer_processor/buffer_processors.h>
#include <str_number/str_number.h>
#include <memory>

StrNumber getFirstNumber(std::shared_ptr<char[]> buffer, size_t bufReadSize) {
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