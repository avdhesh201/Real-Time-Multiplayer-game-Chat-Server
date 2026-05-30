#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

constexpr int TCP_PORT= 5000;
constexpr int UDP_PORT = 5001;
constexpr int BUFFER_SIZE= 1024;

void tcpListener(int sock) {
    char buffer[BUFFER_SIZE];
    while (true) {
        ssize_t bytes= recv(sock, buffer, BUFFER_SIZE-1, 0);
        if (bytes<=0) {
            cout << "Disconnected from server." << endl;
            break;
        }
        buffer[bytes]='\0';
        cout << "[Server]: " << buffer << endl;
    }
}

int main() {
    int tcpSock= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSock < 0) {
        cerr << "Error creating TCP socket" << endl;
        return 1;
    }
    sockaddr_in serverAddr{};
    serverAddr.sin_family= AF_INET;
    serverAddr.sin_port= htons(TCP_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    if (connect(tcpSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Failed to connect to server" << endl;
        return 1;
    }
    cout << "Connected to server on TCP port " << TCP_PORT << endl;
    thread listener(tcpListener, tcpSock);
    int udpSock= socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in udpAddr{};
    udpAddr.sin_family =AF_INET;
    udpAddr.sin_port =htons(UDP_PORT);
    inet_pton(AF_INET, "127.0.0.1", &udpAddr.sin_addr);
    string input;
    while (true) {
        getline(cin, input);
        if (input =="/quit") break;
        send(tcpSock, input.c_str(), input.size(), 0);
        if (input.rfind("/state ", 0)== 0)sendto(udpSock, input.c_str(), input.size(), 0,(sockaddr*)&udpAddr, sizeof(udpAddr));
        
    }
    close(tcpSock);
    close(udpSock);
    listener.join();
    return 0;
}
