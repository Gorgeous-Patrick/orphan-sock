#pragma once
#include <unistd.h>

#include <string>
#include <unordered_map>

struct ClientInfo {
  pid_t pid;
};

const std::string SOCK_PATH("/tmp/orphan_sock.sock");

class Server {
 private:
  class ClientInfo {
    pid_t pid;

   public:
    ClientInfo(pid_t pid) : pid(pid) {}
  };
  std::unordered_map<int, ClientInfo> clients;

 public:
  Server();
};
