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


static void printHelp(std::string name){
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help \tShow this help message\n"
              << "\t-f,--file \tSpecify file for processing"
              << std::endl;
}


int main(int argc, char** argv) {
    if (argc < 3) {
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }
    std::vector <std::string> sources;
    std::string fileName;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            printHelp(argv[0]);
            return EXIT_SUCCESS;
        } else if ((arg == "-f") || (arg == "--file")) {
            if (i + 1 < argc) {
                fileName = argv[i++];
            } else {
                std::cerr << "--file option requires one argument." << std::endl;
                return EXIT_FAILURE;
            }
        } else {
            sources.push_back(argv[i]);
        }
    }
    std::ifstream bigFile("../numbers_light.txt");

    return EXIT_SUCCESS;
}
