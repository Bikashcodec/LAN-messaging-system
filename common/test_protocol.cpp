#include <iostream>
#include "protocol.h"

int main() {
    std::string msg = buildChatMsg("bikram", "hello!");
    std::cout << "Built message: " << msg;

    bool result = startsWith(msg, CMD_MSG);
    std::cout << "Starts with CMD_MSG? " << result << std::endl;

    return 0;
}