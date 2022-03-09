#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

#include <iostream>

#include "Server.h"

constexpr int kPort = 27015;

int main(int argc, char *argv[]) {
  try {
    chat::Server server;
    server.Listen("localhost", kPort);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
