#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

void child_exe(struct sockaddr_in* address,int d);
