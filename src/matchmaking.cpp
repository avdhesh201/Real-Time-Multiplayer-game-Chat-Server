#include "matchmaking.h"

int Matchmaking::findMatch() {
    if (q.size() >= 2) {
        int p1 = q.front(); q.pop();
        int p2 = q.front(); q.pop();
        return p1;
    }
    return -1;
}
