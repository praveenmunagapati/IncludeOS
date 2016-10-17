// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sys/socket.h>
#include <errno.h>
#include <tcp_fd.hpp>
#include <fd_map.hpp>

int socket(int domain, int type, int protocol)
{
  // disallow strange domains, like ALG
  if (domain < 0 || domain > AF_INET6) { errno = EAFNOSUPPORT; return -1; }
  // disallow RAW etc
  if (type < 0 || type > SOCK_DGRAM) { errno = EINVAL; return -1; }
  // we are purposefully ignoring the protocol argument
  if (protocol < 0) { errno = EPROTONOSUPPORT; return -1; }

  int sock = -1;
  // let's assume IPv4 for now
  if (type == SOCK_STREAM) {
    sock = FD_map::_open<TCP_FD>().get_id();
  }
  else {
    /// implement UDP_FD
  }
  return sock;
}

int connect(int socket, const struct sockaddr *address, socklen_t len)
{
  try {
    auto& fd = FD_map::_get(socket);
    return fd.connect(address, len);
  } catch (...) {
    errno = EBADF;
    return -1;
  }
}

ssize_t send(int socket, const void *message, size_t len, int fmt)
{
  try {
    auto& fd = FD_map::_get(socket);
    return fd.send(message, len, fmt);
  } catch (...) {
    errno = EBADF;
    return -1;
  }
}

int listen(int socket, int backlog)
{
  try {
    auto& fd = FD_map::_get(socket);
    return fd.listen(backlog);
  } catch (...) {
    errno = EBADF;
    return -1;
  }
}