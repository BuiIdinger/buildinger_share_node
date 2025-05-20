#include "Network.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Logging.h"
#include <fcntl.h>
#include <unistd.h>

bool network::socket::setNonBlocking(const int socket) noexcept {
  const int flags = fcntl(socket, F_GETFL, 0);
  if (flags == -1) {
    log::error(std::strerror(errno));
    return false;
  }

  if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1) {
    log::error(std::strerror(errno));
    return false;
  }

  return true;
}

void network::socket::create() noexcept {
  clientSocket = ::socket(PF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    log::critical(std::strerror(errno));
  }

  serverSocket = ::socket(PF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    log::critical(std::strerror(errno));
  }

  // Reuse the same address
  constexpr int reuse = 1;
  if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    log::critical(std::strerror(errno));
  }

  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    log::error(std::strerror(errno));
    log::critical(std::strerror(errno));
  }

  if (!setNonBlocking(clientSocket)) {
    log::critical(std::strerror(errno));
  }

  if (!setNonBlocking(serverSocket)) {
    log::critical(std::strerror(errno));
  }
}

void network::socket::bind() noexcept {
  clientSocketAddress.sin_family = AF_INET;
  clientSocketAddress.sin_addr.s_addr = INADDR_ANY;
  clientSocketAddress.sin_port = htons(clientPort);

  serverSocketAddress.sin_family = AF_INET;
  serverSocketAddress.sin_addr.s_addr = INADDR_ANY;
  serverSocketAddress.sin_port = htons(serverPort);

  // Bind
  if (bind(clientSocket, reinterpret_cast<struct sockaddr *>(&clientSocketAddress), sizeof(clientSocketAddress)) == -1) {
    log::critical(std::strerror(errno));
  }

  if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverSocketAddress), sizeof(serverSocketAddress)) == -1) {
    log::critical(std::strerror(errno));
  }
}

void network::socket::listen() noexcept {
  if (::listen(clientSocket, backlog) == -1) {
    log::critical(std::strerror(errno));
  }

  if (::listen(serverSocket, backlog) == -1) {
    log::critical(std::strerror(errno));
  }
}

void network::socket::shutdown() noexcept {
  if (close(clientSocket) == -1) {
    log::error(std::strerror(errno));
  }

  if (close(serverSocket) == -1) {
    log::error(std::strerror(errno));
  }
}