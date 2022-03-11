#include "SocketManager.h"

void chat::SocketManager::CloseSocket(SOCKET *socket) {
  if (!socket || *socket == INVALID_SOCKET) {
    return;
  }

  closesocket(*socket);
  *socket = INVALID_SOCKET;
}
