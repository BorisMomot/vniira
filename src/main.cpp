#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <cstring>

#include "arg_parser/ArgParser.h"
#include "buffer_processor/BufferProcessors.h"
#include "result_accumulator/ResultAccumulator.h"
#include "thread_pool/ThreadPool.h"
#include "buffer_pool/buffer_pool.h"


// Задание:
// Есть многострочный текстовый файл с числами, записанными через пробел. Его размер
// превышает размер имеющейся памяти. Необходимо : - сложить все числа, - вычесть (из первого числа все остальные), - выполнить операцию XOR. Для работы с числами можно использовать не более трех потоков. Необходимо с максимальной скоростью обработать файл. Результатом обработки являются
// три числа. Для решения задачи необходимо использовать STL.
//------------------------------------------------------------------------------------------------


int main(int argc, char** argv) {
    // Считываем параметры запуска ввод
    auto pResult = parseArgs(argc, argv);
    auto const status = std::get<0>(pResult);
    if (status == ParseStatus::fail) { return EXIT_FAILURE;}
    else if (status == ParseStatus::successStop) {return EXIT_SUCCESS;}

    auto fileName = std::get<1>(pResult);
    auto bufferSize = std::get<2>(pResult);

    std::cout << "Process start with parameters: \n"
                 "\tfile name: " << fileName << "\n"
                 "\tbuffer size: " << bufferSize << std::endl;

    ResultAccumulator accumulator;

    // Читаем файл
    std::ifstream bigFile(fileName);
    std::shared_ptr<char[]> buffer(new char[bufferSize * 2]);

    // Вычисляем первое число в последовательности
    if (bigFile){
        bigFile.read(buffer.get(), bufferSize);
        accumulator.setFirstNumber(getFirstNumber(buffer, bigFile.gcount()) ) ;
        bigFile.clear();
        bigFile.seekg(0);
    } else {
        std::cerr << "Couldn't open file" << fileName << std::endl;
        return EXIT_FAILURE;
    }

    ThreadPool threadPool(2);
    BufferPool bufferPool(bufferSize * 2, 20, true);

    const auto prBuffer = [&accumulator, &bufferPool] (std::shared_ptr<char[]> buffer, size_t bufReadSize) {
        auto result = processBuffer( buffer, bufReadSize);
        accumulator.addNumber(result.first);
        accumulator.xorNumber(result.second);
        bufferPool.returnBuffer(buffer);
    };

    while (bigFile) {
        bigFile.read(buffer.get(), bufferSize);
        size_t firstRead = bigFile.gcount();
        bigFile.getline(buffer.get() + firstRead, bufferSize, ' ');
        size_t secondRead = bigFile.gcount();
        if (secondRead > bufferSize) { throw std::runtime_error("Buffer overflow");}

        auto buffer_copy = bufferPool.getBuffer();
        std::memmove(buffer_copy.get(), buffer.get(), firstRead + secondRead);
        threadPool.pushTask(prBuffer, buffer_copy, firstRead + secondRead);
    }

    threadPool.waitForTasks();
    std::cout << accumulator << std::endl;
    return EXIT_SUCCESS;
}


