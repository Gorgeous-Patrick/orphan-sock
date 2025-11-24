#include "server.h"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>

Server::Server() {
    ::unlink(SOCK_PATH.c_str());

    int server_fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un addr {};
    addr.sun_family = AF_UNIX;
    std::strcpy(addr.sun_path, SOCK_PATH.c_str());

    if (::bind(server_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        std::cout << "error binding" << std::endl;
    }
    ::listen(server_fd, 16);
    std::cout << "Server listening on " << SOCK_PATH << "\n";
    while (true) {
        int client_fd = ::accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            continue;
        }
        // Get PID via SO_PEERCRED
        struct ucred cred;
        socklen_t len = sizeof(cred);
        if (::getsockopt(client_fd, SOL_SOCKET, SO_PEERCRED, &cred, &len) == 0) {
            std::cout << "New client: pid=" << cred.pid
                      << " uid=" << cred.uid
                      << " gid=" << cred.gid << "\n";
            // clients[client_fd] = Server::ClientInfo(cred.pid);
            clients.insert({client_fd, Server::ClientInfo(cred.pid)});
        }
    }
}
