#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h> // For InetPton
using namespace std;

#pragma comment(lib,"ws2_32.lib")

    // 1. Initialise winsock library for windows application
    bool Initialise(){
        WSADATA data;
        return WSAStartup(MAKEWORD(2,2), &data) == 0 ;
    }


int main(){
    if(!Initialise()){
       cout<<"WinSock initialisation failed.";
       return 1;
    }

    cout<<"-----Server Program-----"<<endl;

    // 2. Create a socket 
    SOCKET listenSocket = socket(AF_INET , SOCK_STREAM , 0);

    //Always check the return value of the APIs 
    if(listenSocket == INVALID_SOCKET){
        cout<<"socket creation failed"<<endl;
        return 1 ;
    }

    // 3. Get the IP(localhost) and port(12345):other clients will connect here
    // 3.1 create address structure
    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    //3.2 convert the ipaddress(0.0.0.0) put it inside
    //the sin_family in binary form
    if(InetPton(AF_INET , "0.0.0.0", &serveraddr.sin_addr) != 1){
        cout<<"setting address structure failed!"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    // 4. Bind the IP & port with the socket(created in step 2)
    if(bind(listenSocket, reinterpret_cast<sockaddr*>&serveraddr , sizeof(serveraddr)) == SOCKET_ERROR){
        cout<<"Bind failed"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // 5. Listen on the socket 
    if(listen(listenSocket, SOMAXCONN)==SOCKET_ERROR){
        cout<<"Listen failed"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "server is listening on port: " << port<<std::endl;

    // 6. Accept (this is a blocking call) : Here the code will wait untill there is any client connection request incoming
    SOCKET clientSocket = accept(listenSocket,nullptr,nullptr);
    if(clientSocket == INVALID_SOCKET){
        cout<<"INVALID CLIENT SOCKET."<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // 7. recv and send
    char buffer[4096];
    int byterecv = recv(clientSocket,buffer ,sizeof(buffer),0);
    
    if (byterecv > 0) {
        string message(buffer,byterecv);
        cout<<" message from client : "<<message <<endl;
    } else{
        cout << "recv() failed or client disconnected." << endl;
    }
    // 8. closesocket the socket
    closesocket(clientSocket);
    closesocket(listenSocket);

    // 9. Clean up the winsock
    WSACleanup();

    
    return 0; 
}