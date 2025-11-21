#pragma once
#include <unistd.h>
#include <vector>
typedef int linux_fd_t;

int register_fork_process(pid_t parent, pid_t child, std::vector<linux_fd_t> fds_to_associate);

int register_close_process(pid_t pid);


int register_hand_over_fd(pid_t pid, linux_fd_t fd);
