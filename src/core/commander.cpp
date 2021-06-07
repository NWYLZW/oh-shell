#include "commander.h"

std::vector<Command*>* Commander::parser(
    const std::string& commandStr
    ) {
    auto commands = new std::vector<Command*>;
    commands->push_back(new Command);

    const char * commandChars = commandStr.c_str();
    for (int i = 0; i < commandStr.length(); i++) {
        if (commandStr[i] != ' ') {
            int start = i;
            while (
                i < commandStr.length()
                && commandStr[++i] != ' '
            ) continue;
            auto cmd = (*commands)[commands->size() - 1];

            char *subBuff = new char[i - start + 1];
            memcpy(subBuff, &commandChars[start], i -start);
            subBuff[i - start] = '\0';
            cmd->argv.push_back(subBuff);

            if (cmd->argv.size() == 1) {
                cmd->filename = cmd->argv[0];
            }
        }
    }
    return commands;
}

int doDefaultCmd(Command c) {
    if (strcmp(c.filename, "exit") == 0) {
        return 1;
    } else if (strcmp(c.filename, "help") == 0) {
        // TODO print help message.
        std::cout << "This is help usage." << std::endl;
        return 0;
    }
    return -1;
}

int Commander::doCmd(Command c) {
    auto result = doDefaultCmd(c);
    if (result != -1) {
        return result;
    }
    pid_t pid;
    std::ostringstream os;
    if ((pid = fork()) == 0) {
        if (execvp(c.filename, &c.argv[0]) < 0) {
            os << "'" << c.filename << "' command not found.";
            throw os.str();
        }
    }
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        os << "Wait pid '" << pid << "' error.";
        throw os.str();
    }
    return 0;
}
