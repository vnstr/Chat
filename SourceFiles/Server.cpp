#include "Server.h"

#include <WS2tcpip.h>

chat::Server::Server() {
  const auto winsock_version = chat::kWinsockVersion;

  int result = WSAStartup(winsock_version, &wsaData_);
  if (result != 0) {
    Release();
    throw std::system_error(std::error_code(result, std::system_category()),
                            "winsock error: WSAStartup failed");
  }
}

void chat::Server::Listen(const std::string &node_name, int port) {
  addrinfo hints = {};

  int result = getaddrinfo(node_name.c_str(), std::to_string(port).c_str(),
                           &hints, &addr_info_);
  if (result != 0) {
    Release();
    throw std::system_error(std::error_code(result, std::system_category()),
                            "windows error: getaddrinfo failed");
  }
}

chat::Server::~Server() { Release(); }

void chat::Server::Release() {
  if (addr_info_) {
    freeaddrinfo(addr_info_);
    addr_info_ = nullptr;
  }

  WSACleanup();
}
