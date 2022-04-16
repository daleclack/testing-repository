#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

typedef std::string string;

class Game24
{
public:
    bool startgame(string user_result);
    void getnumbers();
    char numbers_char[20];

private:
    const int n = 4;                           // Flag of third calculate
    double number[4] = {0};              // Numbers
    char oper[4] = {'+', '-', '*', '/'}; // operators
    string result[4];
    int count = 0;

    std::vector<std::string> result_strings;

    // Handlers
    void F(int n);
};
