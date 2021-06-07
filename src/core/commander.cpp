#include "commander.h"

std::vector<Command*>* Commander::parser(
    const std::string& commandStr
    ) {
    auto commands = new std::vector<Command*>;
    commands->push_back(new Command);

    for (int i = 0; i < commandStr.length(); i++) {
        if (commandStr[i] != ' ') {
            int start = i;
            while (
                i < commandStr.length()
                && commandStr[++i] != ' '
            ) continue;
            auto cmd = (*commands)[commands->size() - 1];
            cmd->argv.push_back(
                (char *) commandStr.substr(start, i).c_str()
            );
            cmd->filename = cmd->argv[0];
        }
    }
    return commands;
}

int Commander::doCmd(Command c) {
    if (strcmp(c.filename, "exit") == 0) {
        return 1;
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
