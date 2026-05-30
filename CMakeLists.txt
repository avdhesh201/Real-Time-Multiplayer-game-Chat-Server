cmake_minimum_required(VERSION 3.10)
project(MultiplayerServer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SERVER_SRC
    src/server.cpp
    src/threadpool.cpp
    src/lobby.cpp
    src/matchmaking.cpp
    src/chat.cpp
    src/sync.cpp
)

set(CLIENT_SRC
    src/client.cpp
)

add_executable(server ${SERVER_SRC})
add_executable(client ${CLIENT_SRC})

target_link_libraries(server pthread)
target_link_libraries(client pthread)
