#include "Network.h"

int main() {
  // Start up sockets
  network::socket::create();
  network::socket::bind();
  network::socket::listen();

  return 0;
}