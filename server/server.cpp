#include <iostream>
#include <winsock2.h>
#include "../common/protocol.h"

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return 1;
    }

    // Create a TCP socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind to all interfaces on our chosen port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Start listening
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << SERVER_PORT << "..." << std::endl;

    // Accept one client connection
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected!" << std::endl;

    // Receive a message from the client
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received from client: " << buffer;
    }

    // Clean up
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}