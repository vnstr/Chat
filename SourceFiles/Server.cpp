#include "Server.h"

#include <WS2tcpip.h>

#include "SocketManager.h"

chat::Server::Server() {
  const auto winsock_version = chat::kWinsockVersion;

  int result = WSAStartup(winsock_version, &wsaData_);
  if (result != 0) {
    Release();
    throw std::system_error(std::error_code(result, std::system_category()),
                            "winsock error: WSAStartup failed");
  }
}

chat::Server::~Server() {
  StopListen();
  Release();
}

void chat::Server::Listen(const std::string &node_name, int port) {
  StopListen();

  addrinfo hints = {};

  hints.ai_family = AF_INET;  // Ipv4
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  int result = getaddrinfo(node_name.c_str(), std::to_string(port).c_str(),
                           &hints, &addrInfo_);
  if (result != 0) {
    StopListen();
    throw std::system_error(std::error_code(result, std::system_category()),
                            "windows error: getaddrinfo failed");
  }

  listen_ = socket(addrInfo_->ai_family, addrInfo_->ai_socktype,
                   addrInfo_->ai_protocol);

  if (listen_ == INVALID_SOCKET) {
    StopListen();
    throw std::system_error(
        std::error_code(WSAGetLastError(), std::system_category()),
        "windows error: socket failed");
  }

  result = connect(listen_, addrInfo_->ai_addr,
                   static_cast<int>(addrInfo_->ai_addrlen));
  if (result == SOCKET_ERROR) {
    StopListen();
    throw std::system_error(
        std::error_code(WSAGetLastError(), std::system_category()),
        "windows error: connect failed");
  }
}

void chat::Server::StopListen() {
  SocketManager::CloseSocket(&client_);
  SocketManager::CloseSocket(&listen_);

  if (addrInfo_) {
    freeaddrinfo(addrInfo_);
    addrInfo_ = nullptr;
  }
}

void chat::Server::Release() { WSACleanup(); }
