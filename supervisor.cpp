#include "supervisor.h"
#include <iostream>
#include <unordered_set>
#include <unistd.h>
#include <memory>
#include <unordered_map>
#include <vector>
using namespace std;

typedef int linux_fd_t;

class exposed_fd_t {
  linux_fd_t linux_fd;
  public:
  exposed_fd_t(linux_fd_t fd) : linux_fd(fd) {}
  linux_fd_t get_linux_fd() const { return linux_fd; }
  ~exposed_fd_t() {
    // Close the underlying linux fd when this object is destroyed
    if (close(linux_fd) == -1) {
        perror("Close failed");
    }
  }
};
typedef shared_ptr<exposed_fd_t> exposed_fd_ptr;

// Each process has a set of file descriptors
// associated with it.
// And a parent process (or null if init).
class process_t;
typedef shared_ptr<process_t> process_ptr;
class process_t {
  process_ptr parent = nullptr;
  public:
  process_t(process_ptr parent_proc) : parent(parent_proc) {}
  unordered_set<exposed_fd_ptr> fds;
  process_ptr get_parent() {
      return parent;
  }
  ~process_t() {
    // Hand the fds to the parent process on destruction
    if (parent) {
      for (const auto& fd : fds) {
        parent->fds.insert(fd);
      }
      fds.clear();
    }
  }
};


typedef unordered_map<pid_t, process_ptr> process_lib_t;
process_lib_t process_lib;


void associate_linux_fd_with_process(process_ptr proc, linux_fd_t fd) {
  exposed_fd_ptr exposed_fd = make_shared<exposed_fd_t>(fd);
  proc->fds.insert(exposed_fd);
}

bool is_linux_fd_associated_with_process(process_ptr proc, linux_fd_t fd) {
  for (const auto& exposed_fd : proc->fds) {
    if (exposed_fd->get_linux_fd() == fd) {
      return true;
    }
  }
  return false;
}

bool is_linux_fd_associated_with_any_child_recursively(process_ptr proc, linux_fd_t fd) {
  for (const auto& entry : process_lib) {
    process_ptr child_proc = entry.second;
    if (child_proc->get_parent() == proc) {
      if (is_linux_fd_associated_with_process(child_proc, fd) ||
          is_linux_fd_associated_with_any_child_recursively(child_proc, fd)) {
        return true;
      }
    }
  }
  return false;
}


int register_fork_process(pid_t parent, pid_t child, vector<linux_fd_t> fds_to_associate) {
  process_ptr parent_proc = process_lib[parent];
  if (!parent_proc) {
    cerr << "Parent process not found!" << endl;
    return -1; // Error
  }
  // Make sure that all fds are accessible by parent.
  for (const auto & fd : fds_to_associate) {
    if (!is_linux_fd_associated_with_process(parent_proc, fd) &&
        !is_linux_fd_associated_with_any_child_recursively(parent_proc, fd)) {
      cerr << "FD " << fd << " not accessible by parent process!" << endl;
      return -1; // Error
    }
  }
  process_ptr child_proc = make_shared<process_t>(parent_proc);
  process_lib[child] = child_proc;

  for (const auto & fd : fds_to_associate) {
    associate_linux_fd_with_process(child_proc, fd);
  }

  return 0; // Success
}

int register_close_process(pid_t pid) {
  if (process_lib.find(pid) == process_lib.end()) {
    cerr << "Process not found!" << endl;
    return -1; // Error
  }
  process_lib.erase(pid);
  return 0; // Success
}

int register_hand_over_fd(pid_t pid, linux_fd_t fd) {
  process_ptr proc = process_lib[pid];
  if (!proc) {
    cerr << "Process not found!" << endl;
    return -1; // Error
  }
  // erase fd from pid
  proc->fds.erase_if([fd](const exposed_fd_ptr& exposed_fd) {
    return exposed_fd->get_linux_fd() == fd;
  });
  associate_linux_fd_with_process(proc, fd);
  return 0; // Success
}
