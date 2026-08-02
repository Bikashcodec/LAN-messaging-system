#pragma once
#include <string>

// Command prefixes
const std::string CMD_JOIN = "JOIN:";
const std::string CMD_MSG = "MSG:";
const std::string CMD_LIST = "LIST:";
const std::string CMD_LIST_RESPONSE = "LIST_RESPONSE:";
const std::string CMD_LEAVE = "LEAVE:";

// Config
const int SERVER_PORT = 54000;
const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

inline std::string buildJoinMsg(const std::string& username) {
    return CMD_JOIN + username + "\n";
}

inline std::string buildChatMsg(const std::string& username, const std::string& text) {
    return CMD_MSG + username + ":" + text + "\n";
}

inline std::string buildLeaveMsg(const std::string& username) {
    return CMD_LEAVE + username + "\n";
}

inline bool startsWith(const std::string& line, const std::string& prefix) {
    return line.compare(0, prefix.size(), prefix) == 0;
}

