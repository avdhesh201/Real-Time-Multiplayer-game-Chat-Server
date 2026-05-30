#pragma once
#include <queue>

using namespace std;

class Matchmaking {
public:
    void enqueuePlayer(int clientId) { q.push(clientId); }
    int findMatch();
private:
    queue<int> q;
};
