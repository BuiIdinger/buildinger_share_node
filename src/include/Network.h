#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>

namespace network::socket {
    /*
     * Number of events that can be
     * backlogged in the os socket queue
     */
    constexpr int backlog = 50;

    /*
     * Client & Server ports
     */
    constexpr int clientPort = 22773;
    constexpr int serverPort = 23363;

    /*
     * We need a socket for the client, and one for the
     * server to communicate between nodes
     */
    inline int32_t clientSocket = -1;
    inline int32_t serverSocket = -1;
    inline sockaddr_in clientSocketAddress;
    inline sockaddr_in serverSocketAddress;

    bool setNonBlocking(int socket) noexcept;
    void create() noexcept;
    void bind() noexcept;
    void listen() noexcept;

    // Closes client & server socket
    void shutdown() noexcept;
}