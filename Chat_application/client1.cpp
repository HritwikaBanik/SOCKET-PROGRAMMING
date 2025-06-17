#include<iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

using namespace std;

  //initialise winSock
  bool Initialise(){
        WSADATA data;
        return WSAStartup(MAKEWORD(2,2), &data) == 0 ;
    }

int main(){
    if(!Initialise()){
       cout<<"WinSock initialisation failed in client.";
       return 1;
    }
    
    cout<<"client program started....."<<endl;

    //create socket
    SOCKET s;
    s = socket(AF_INET , SOCK_STREAM , 0);
    if(s == INVALID_SOCKET){
        cout<<"Invalid socket created"<<endl;
        return 1 ;
    }

    //specify and get port & IP
    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    string serveraddress = "127.0.0.1";
    inet_pton(AF_INET, serveraddress.c_str(),&(serveraddr.sin_addr));

    //connect to server
    if(connect(s,reinterpret_cast<sockaddr*>&serveraddr , sizeof(serveraddr)) == SOCKET_ERROR){
        cout<<"not able to connect to server."<<endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //send/recv
    string message = "Hello , there ..";
    int bytesent = send(s, message.c_str(),message.length(),0);
    if(bytesent == SOCKET_ERROR){
        cout<<"send failed"<<endl;
    }

    closesocket(s);

    WSACleanup();
    return 0; 
}