#include "lobby.h"

using namespace std;

void Lobby::addPlayer(int clientId) {
    players.push_back(clientId);
}

void Lobby::removePlayer(int clientId) {
    players.erase(remove(players.begin(), players.end(), clientId), players.end());
}
