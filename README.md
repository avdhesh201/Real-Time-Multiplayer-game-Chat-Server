# Real-Time-Multiplayer-Game-Chat-Server



## Problem Statement
Build a  **Real-Time-Multiplayer-Game-Chat-Server** in C++ that allows multiple clients to connect, exchange messages, and demonstrate real-time communication.  
The goal is to establish a clean project structure, configure builds with CMake, and implement a server that can handle multiple clients concurrently.  
Initially, the server only echoed messages back to the sender. We upgraded it to **broadcast messages** to all connected clients — the foundation of a multiplayer chat or game system.

---

## Build Instructions
From the project root:

- **Remove any old build folder**  : rm -rf build
- **Create a new build directory** : mkdir build && cd build
- **Run CMake to configure** : cmake ..
- **Compile the project** : make 


This produces two executables in build/: server and client
- Start the server : ./server
- Run  multiple clients : ./client
---


## Features Implemented
- TCP server listening on port 5000
- Thread pool for handling multiple clients concurrently
- Broadcast messaging so all clients see each other’s messages
- Clean CMake build system for easy compilation
