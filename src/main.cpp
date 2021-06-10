#include <iostream>
#include <pwd.h>

using namespace std;

#include "core/commander.h"
#include "core/consoleColor.h"

int main() {
    bool isRight = true;
    char hostname[1024];
    gethostname(hostname, 1024);

    string username = getpwuid(getuid())->pw_name;

    string input;
    while (true) {
        // TODO print the current path and time after hostname
        cout
            << (isRight ? RESET : RED) << username << "@[" << hostname << "]" << endl
            << RESET;
        cout
            << (isRight ? RESET : RED) << ">> "
            << RESET;

        getline(cin, input);

        bool isBreak = false;
        auto commands = Commander::parser(input);
        for (auto c : *commands) {
            try {
                isRight = true;

                auto result = Commander::doCmd(*c);
                if (result == 1) {
                    isBreak = true; break;
                }
            } catch (std::string &msg) {
                isRight = false;
                cout << (isRight ? RESET : RED) << "Error: " << msg << endl;
            }
        }
        if (isBreak) break;
    }
    cout << "See you~" << endl;
    return 0;
}
