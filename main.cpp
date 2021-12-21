#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <cmath>
#include <vector>


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


int main(int argc, char** argv) {
    // Парсим ввод
    auto pResult = parseArgs(argc, argv);
    auto const status = std::get<0>(pResult);
    if (status == ParseStatus::fail) { return EXIT_FAILURE;}
    else if (status == ParseStatus::successStop) {return EXIT_SUCCESS;}

    // Читаем файл
    auto fileName = std::get<1>(pResult);
    auto bufferSize = std::get<2>(pResult);

    std::ifstream bigFile(fileName);

    std::unique_ptr<char[]> buffer(new char[bufferSize]);
    if (bigFile){
        bigFile.read(buffer.get(), bufferSize);
        bigFile.clear();
        bigFile.seekg(0);

    }


    return EXIT_SUCCESS;
}
