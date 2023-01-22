#ifndef MEDICALHORSE_TCPIP_COMM_H_
#define MEDICALHORSE_TCPIP_COMM_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>

#define PORT 8080

namespace medicalhorse::display::connection {
class TcpIpComm {

public:
  /**
   * @brief Constructor
   */
  TcpIpComm();

  /**
   * @brief Destructor
   */
  virtual ~TcpIpComm() = default;

  /**
   * @brief Method to open connection
   */
  void Open();

  void Close();

  /**
   * @brief Method to wait for connection
   */
  void WaitForStableConnection();

  /**
   * @brief Method to read UDP packages
   * @param Data package to read
   * @return Number of bytes received
   */
  int Read(std::vector<int8_t> *pBuffer);

  /**
   * @brief Method to write UDP packages
   * @param Data package to send
   * @return Number of bytes to write
   */
  int Write(const std::vector<int8_t> &buffer);

private:
  int m_opt;
  int m_server_fd;
  int m_new_socket;
  int m_valread;
  struct sockaddr_in m_address;
  socklen_t m_clilen;
  std::thread m_thread;
};
} // namespace medicalhorse::display::connection

#endif // MEDICALHORSE_TCPIP_COMM_H_