#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>        
#include <arpa/inet.h>
#include <unistd.h>
#include "threadpool.h"
#include "lobby.h"
#include "chat.h"

using namespace std;

constexpr int TCP_PORT= 5000;
constexpr int BUFFER_SIZE= 1024;

vector<int> clients;
mutex clientsMutex;

void broadcastMessage(const string& msg, int senderSock) {
    lock_guard<mutex> lock(clientsMutex);
    for (int sock : clients) {
        if (sock!= senderSock)send(sock, msg.c_str(), msg.size(), 0);
    }
}

void handleClient(int clientSock) {
    {
        lock_guard<mutex> lock(clientsMutex);
        clients.push_back(clientSock);
    }
    char buffer[BUFFER_SIZE];
    while (true) {
        ssize_t bytes= recv(clientSock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes<= 0) break;
        buffer[bytes]= '\0';
        string msg= "[Client] " + string(buffer);
        cout << msg << endl;
        broadcastMessage(msg, clientSock);
    }

    {
        lock_guard<mutex> lock(clientsMutex);
        clients.erase(remove(clients.begin(), clients.end(), clientSock), clients.end());
    }
    close(clientSock);
}

int main() {
    int serverSock=socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        cerr << "Error creating server socket" << endl;
        return 1;
    }
    sockaddr_in serverAddr{};
    serverAddr.sin_family =AF_INET;
    serverAddr.sin_port= htons(TCP_PORT);
    serverAddr.sin_addr.s_addr= INADDR_ANY;
    if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed" << endl;
        return 1;
    }
    if (listen(serverSock, 5) < 0) {
        cerr << "Listen failed" << endl;
        return 1;
    }
    ThreadPool pool(4);
    cout << "Server running on port " << TCP_PORT << endl;
    while (true) {
        int clientSock = accept(serverSock, nullptr, nullptr);
        if (clientSock < 0) {
            cerr << "Accept failed" << endl;
            continue;
        }
        pool.enqueue([clientSock] { handleClient(clientSock); });
    }
}