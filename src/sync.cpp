#include "sync.h"
#include <iostream>

using namespace std;

void Sync::updateState(const string& state) {
    cout << "[Sync]: " << state << endl;
}
