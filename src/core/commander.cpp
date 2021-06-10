#include "commander.h"

std::vector<Command*>* Commander::parser(
    const std::string& commandStr
    ) {
    auto commands = new std::vector<Command*>;
    if (commandStr.empty()) return commands;
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

            // TODO refactor the following logic to a substr method
            char *subBuff = new char[i - start + 1];
            memcpy(subBuff, &commandChars[start], i -start);
            subBuff[i - start] = '\0';
            cmd->argv.push_back(subBuff);

            if (cmd->argv.size() == 1) {
                cmd->filename = cmd->argv[0];
            }
        }
    }
    for (const auto &command : *commands) {
        command->argv.push_back(nullptr);
    }
    return commands;
}

int doDefaultCmd(Command c) {
    if (strcmp(c.filename, "exit") == 0) {
        return 1;
    } else if (strcmp(c.filename, "help") == 0) {
        std::cout
            << "Usage: oh-shell [version-0.0.1]" << std::endl
            << "Very simple shell." << std::endl;
        return 0;
    } else if (strcmp(c.filename, "cd") == 0) {
        if (c.argv.size() > 1) {
            chdir(c.argv[1]);
        }
        return 0;
    }
    return -1;
}

int Commander::doCmd(Command c) {
    if (strcmp(c.filename, "") == 0) return 0;
    auto result = doDefaultCmd(c);
    if (result != -1) {
        return result;
    }
    pid_t pid;
    std::ostringstream os;
    if ((pid = fork()) == 0) {
        auto doResult = execvp(c.filename, &c.argv[0]);
        if (doResult < 0) {
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
