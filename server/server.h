#pragma once
#include <unistd.h>

#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

struct ClientInfo {
  pid_t pid;
};

const std::string SOCK_PATH("/tmp/orphan_sock.sock");

typedef std::shared_ptr<std::shared_mutex> shared_mutex_ptr;

class Server {
 private:
  class ClientInfo {
    pid_t pid;

   public:
    ClientInfo(pid_t pid) : pid(pid) {}
  };

  typedef std::tuple<shared_mutex_ptr, ClientInfo> ClientInfoLocked;

  std::shared_mutex clients_lock;

  std::unordered_map<int, ClientInfoLocked> clients;

 public:
  Server();
};
