//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_ARG_PARSER_H
#define VNIIRA_ARG_PARSER_H

enum ParseStatus{
    fail = 0,
    successStop = 1,
    successContinue = 2
};

void printHelp(std::string name);

std::tuple<int, std::string, size_t> parseArgs (int argc, char** argv);

#endif // VNIIRA_ARG_PARSER_H
