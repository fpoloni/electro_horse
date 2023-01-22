
#include "TcpIpComm.h"
#include "TcpIpDefinitions.h"

namespace medicalhorse::display::connection {
TcpIpComm::TcpIpComm() : m_new_socket(-1) {}

void TcpIpComm::Open() {
  // Creating socket file descriptor
  if ((m_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    exit(EXIT_FAILURE);
  }

  m_address.sin_family = AF_INET;
  m_address.sin_addr.s_addr = INADDR_ANY;
  m_address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080
  if (bind(m_server_fd, (struct sockaddr *)&m_address, sizeof(m_address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(m_server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  printf("Waiting for display app.\n");
  this->WaitForStableConnection();
}

void TcpIpComm::Close() { close(m_new_socket); }

void TcpIpComm::WaitForStableConnection() {
  while (m_new_socket < 0) {
    if ((m_new_socket = accept(m_server_fd, (struct sockaddr *)&m_address,
                               &m_clilen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    printf("Data package from client.\n");
  }
}

int TcpIpComm::Read(std::vector<int8_t> *pBuffer) {
  int retVal = -1;
  if (nullptr != pBuffer) {
    retVal = recvfrom(m_new_socket, pBuffer->data(), pBuffer->size(), 0,
                      (struct sockaddr *)&m_address, &m_clilen);
  }

  return retVal;
}

int TcpIpComm::Write(const std::vector<int8_t> &buffer) {
  int retVal = sendto(m_new_socket, buffer.data(), buffer.size(), 0,
                      (struct sockaddr *)&m_address, m_clilen);
  printf("Total sent bytes: %d\n", retVal);

  return retVal;
}
} // namespace medicalhorse::display::connection
