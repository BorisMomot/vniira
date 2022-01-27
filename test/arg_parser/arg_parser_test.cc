//
// Created by boris on 26.01.2022.
//
#include <gtest/gtest.h>
#include "arg_parser/ArgParser.h"

TEST(arg_parser, help_no_param){
    char* args[]={
            "progname",""
    };
    auto argc_test = sizeof(args)/sizeof(char*);
    auto argv_test = args;
    auto res = parseArgs(argc_test, argv_test);
    ASSERT_EQ(std::get<0>(res), ParseStatus::fail);
    ASSERT_EQ(std::get<1>(res), "");
    ASSERT_EQ(std::get<2>(res), 0);
}

TEST(arg_parser, help){
    char* args[]={
            "progname","--buffer", "1024", "--file", "my_file.txt", "--help"
    };
    auto argc_test = sizeof(args)/sizeof(char*);
    auto argv_test = args;
    auto res = parseArgs(argc_test, argv_test);
    ASSERT_EQ(std::get<0>(res), ParseStatus::successStop);
    ASSERT_EQ(std::get<1>(res), "");
    ASSERT_EQ(std::get<2>(res), 0);
}

TEST(arg_parser, normal_param){
    char* args[]={
            "progname","--buffer", "1024", "--file", "my_file.txt"
    };
    auto argc_test = sizeof(args)/sizeof(char*);
    auto argv_test = args;
    auto res = parseArgs(argc_test, argv_test);
    ASSERT_EQ(std::get<0>(res), ParseStatus::successContinue);
    ASSERT_EQ(std::get<1>(res), "my_file.txt");
    ASSERT_EQ(std::get<2>(res), 1024);
}

TEST(arg_parser, short_param){
    char* args[]={
            "progname","-b", "1024", "-f", "my_file.txt"
    };
    auto argc_test = sizeof(args)/sizeof(char*);
    auto argv_test = args;
    auto res = parseArgs(argc_test, argv_test);
    ASSERT_EQ(std::get<0>(res), ParseStatus::successContinue);
    ASSERT_EQ(std::get<1>(res), "my_file.txt");
    ASSERT_EQ(std::get<2>(res), 1024);
}
