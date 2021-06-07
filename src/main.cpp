#include <iostream>
#include <sstream>
#include <vector>

#include <pwd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

#include "core/consoleColor.h"

vector<char *>* parserCommand(const string& command) {
    auto argv = new vector<char *>;
    for (int i = 0; i < command.length(); i++) {
        auto c = command[i];
        if (c != ' ') {
            int start = i;
            while (
                i < command.length()
                && command[++i] != ' '
            ) continue;
            argv->push_back((char *) command.substr(start, i).c_str());
        }
    }
    argv->push_back(nullptr);
    return argv;
}

int doCommand(vector<char *> argv) {
    if (strcmp(argv[0], "exit") == 0) {
        return 1;
    }
    pid_t pid;
    ostringstream os;
    if ((pid = fork()) == 0) {
        if (execvp(argv[0], &argv[0]) < 0) {
            os << "'" << argv[0] << "' command not found.";
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

int main() {
    bool isRight = true;
    char hostname[1024];
    gethostname(hostname, 1024);

    string username = getpwuid(getuid())->pw_name;

    string input;
    while (true) {
        cout
            << (isRight ? RESET : RED) << username << "@[" << hostname << "]" << endl
            << RESET;
        cout
            << (isRight ? RESET : RED) << ">> "
            << RESET;

        getline(cin, input);

        auto p_argv = parserCommand(input);
        try {
            isRight = true;

            auto result = doCommand(*p_argv);
            if (result == 1) {
                break;
            }
        } catch (std::string &msg) {
            isRight = false;
            cout << (isRight ? RESET : RED) << "Error: " << msg << endl;
        }
    }
    cout << "See you~" << endl;
    return 0;
}
