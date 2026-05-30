#pragma once
#include <vector>
#include <algorithm>

using namespace std;
class Lobby {
public:
    void addPlayer(int clientId);
    void removePlayer(int clientId);
private:
    vector<int> players;
};
