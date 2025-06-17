#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

using namespace std;

// Initialise WinSock
bool Initialise() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main() {
    if (!Initialise()) {
        cout << "WinSock initialisation failed in client." << endl;
        return 1;
    }

    cout << "Client program started..." << endl;

    // Create socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Invalid socket created." << endl;
        return 1;
    }

    // Specify IP and port
    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    string serveraddress = "127.0.0.1";
    inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

    // Connect to server
    if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Not able to connect to server." << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Send message
    string message = "Hello, there ..";
    int bytesent = send(s, message.c_str(), static_cast<int>(message.length()), 0);
    if (bytesent == SOCKET_ERROR) {
        cout << "Send failed." << endl;
    }

    // Cleanup
    closesocket(s);
    WSACleanup();
    return 0;
}
