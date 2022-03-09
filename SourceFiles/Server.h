#ifndef SOURCEFILES_SERVER_H_
#define SOURCEFILES_SERVER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>

#include <string>
#include <system_error>

namespace chat {

constexpr WORD kWinsockVersion = MAKEWORD(2, 2);

class Server final {
 public:
  explicit Server();
  ~Server();

  void Listen(const std::string &node_name, int port);

 private:
  void Release();

  WSAData wsaData_{};

  SOCKET listen_{INVALID_SOCKET};
  SOCKET client_{INVALID_SOCKET};

  addrinfo *addr_info_{nullptr};
};

}  // namespace chat

#endif  // SOURCEFILES_SERVER_H_
