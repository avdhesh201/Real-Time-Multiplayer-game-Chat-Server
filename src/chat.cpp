#include "chat.h"
#include <iostream>

using namespace std;

void Chat::broadcast(const string& message) {
    cout << "[Chat]: " << message << endl;
}
