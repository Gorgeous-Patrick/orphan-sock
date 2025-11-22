#include <iostream>
#include <grpcpp/grpcpp.h>
#include "orphan_sock.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::Status;
using grpc::ServerContext;

using orphan_sock::OrphanSockServer;
using orphan_sock::CloseRequest;
using orphan_sock::Empty;

class OrphanSockServerImpl final : public OrphanSockServer::Service {
    public:
        Status RegisterCloseProcess(ServerContext * ctx, const CloseRequest * req, Empty * reply) {
            int64_t pid = req->process_id();

            return Status::OK;
        }

};

int main() {
    OrphanSockServerImpl service;
    ServerBuilder builder;
    std::string uds_path = "/tmp/orphan_sock.sock";
    std::remove(uds_path.c_str());
    builder.AddListeningPort("unix:" + uds_path, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server Starting..." << std::endl;
    server->Wait();
}
