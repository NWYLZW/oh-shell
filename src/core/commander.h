#pragma once
#include <iostream>
#include <sstream>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

typedef struct COMMAND {
    char * filename;
    std::vector<char *> argv;
} Command;

class Commander {
public:
    static std::vector<Command*>* parser(const std::string& commandStr);
    static int doCmd(Command c);
};
