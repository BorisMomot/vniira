//
// Created by boris on 30.01.2022.
//
#include <iostream>
#include <tuple>
#include "arg_parser/arg_parser.h"

void printHelp(std::string name) {
  std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
            << "Options:\n"
            << "\t-h,--help \tShow this help message\n"
            << "\t-f,--file \tSpecify file for processing"
            << "\t-b,--buffer \tSpecify reading buffer size (default: 1024 x 1024)"
            << std::endl;
}

std::tuple<int, std::string, size_t> parseArgs (int argc, char** argv) {
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