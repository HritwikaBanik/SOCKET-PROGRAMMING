
---
```markdown
# 🧩 Socket Programming

This project implements a basic **TCP client-server** communication system in C++ using POSIX sockets. It demonstrates how a server can accept multiple client connections, receive messages, and respond with an acknowledgment. It also emphasizes **good memory management practices** including the use of smart pointers and validation with tools like Valgrind.

---

## 📦 Features

### ✅ TCP Server
- Listens on a configurable port (e.g., 8080)
- Accepts one or more client connections
- Receives messages from clients
- Sends an acknowledgment message (e.g., `"Message received"`)

### ✅ TCP Client
- Connects to the server using IP and port
- Sends a custom message to the server
- Receives and displays the acknowledgment

### ✅ Memory Management
- Uses **dynamic memory** (`new/delete` or `malloc/free`) for message buffers
- Uses **smart pointers** (`std::unique_ptr`, `std::shared_ptr`) where applicable
- Validated using **Valgrind** to ensure **no memory leaks**

---

## 🛠️ Requirements

- C++11 or later
- Linux or Unix-based OS (for POSIX sockets)
- Valgrind (optional, for memory testing)

---

## 📁 Project Structure

```

socket-programming/
├── client.cpp        # TCP client implementation
├── server.cpp        # TCP server implementation
├── Makefile          # (Optional) to build both programs
└── README.md         # Project documentation

````

---

## 🚀 How to Compile & Run

### 🧱 Compile Server & Client

```bash
g++ server.cpp -o server
g++ client.cpp -o client
````

### 🔌 Run Server

```bash
./server
```

(Default port is 8080 unless changed in code)

### 🖥️ Run Client

```bash
./client
```

When prompted, enter a message to send to the server.

---

## 🧪 Memory Leak Check (Optional)

Use [Valgrind](https://valgrind.org/) to check for memory leaks:

```bash
valgrind ./server
valgrind ./client
```

---

## 🧠 Concepts Used

* POSIX socket APIs (`socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`)
* Dynamic memory allocation
* Smart pointers (`std::unique_ptr`)
* Error handling and basic I/O
* Valgrind for memory safety validation

---

## 👨‍💻 Author

* **Hritwika**
  Developed as part of an assignment involving systems programming and memory management best practices.

---

## 📃 License

This project is open-source and free to use for educational purposes.

