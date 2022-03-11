#ifndef SOURCEFILES_SOCKETMANAGER_H_
#define SOURCEFILES_SOCKETMANAGER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>

namespace chat {

class SocketManager final {
 public:
  static void CloseSocket(SOCKET *socket);
};

}  // namespace chat

#endif  // SOURCEFILES_SOCKETMANAGER_H_
