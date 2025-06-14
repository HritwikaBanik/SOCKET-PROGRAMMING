#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

constexpr int DEFAULT_PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

void handle_client(int client_sock) {
    
    std::unique_ptr<char[]> buffer(new char[BUFFER_SIZE]);

    ssize_t read_bytes = read(client_sock, buffer.get(), BUFFER_SIZE - 1);
    if (read_bytes > 0) {
        buffer[read_bytes] = '\0';
        std::cout << "Received: " << buffer.get() << std::endl;

        const char* ack = "Message received";
        send(client_sock, ack, strlen(ack), 0);
    } else {
        std::cerr << "Read error or client disconnected\n";
    }
    close(client_sock);
}


int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    if (argc == 2) {
        port = std::stoi(argv[1]);
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on port " << port << std::endl;

    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        // Handling client in a new thread
        threads.emplace_back(std::thread(handle_client, client_sock));
        // Detaching thread so it runs independently
        threads.back().detach();
    }

    close(server_fd);
    return 0;
}
