#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

constexpr int BUFFER_SIZE = 1024;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port> <message>\n";
        return 1;
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);
    std::string message = argv[3];

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        close(sock);
        return 1;
    }

    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    // unique_ptr for send buffer
    auto send_buf = std::make_unique<char[]>(message.size() + 1);
    std::strcpy(send_buf.get(), message.c_str());

    send(sock, send_buf.get(), strlen(send_buf.get()), 0);

    auto recv_buf = std::make_unique<char[]>(BUFFER_SIZE);
    ssize_t read_bytes = read(sock, recv_buf.get(), BUFFER_SIZE - 1);
    if (read_bytes > 0) {
        recv_buf[read_bytes] = '\0';
        std::cout << "Server response: " << recv_buf.get() << std::endl;
    } else {
        std::cerr << "No response or read error\n";
    }

    close(sock);
    return 0;
}
