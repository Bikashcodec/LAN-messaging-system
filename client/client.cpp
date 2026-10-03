#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../common/protocol.h"

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Step 1: Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Step 2: Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Step 3: Specify the server's address and port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // for now, connect to localhost

    // Step 4: Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!" << std::endl;

    // Step 5: Send a test message
    std::string msgToSend = buildChatMsg("bikram", "hello server!");
    send(clientSocket, msgToSend.c_str(), (int)msgToSend.length(), 0);

    // Step 6: Clean up
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}