#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void child_exe(struct sockaddr_in *address, int id) {
    srand(time(NULL) ^ getpid());  // Seed for unique random numbers
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("Child socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (connect(socket_fd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("Connection failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < 10; k++) {
        int i = rand() % 10 + id * 10;  // Unique product ID per child
        char response;

        write(socket_fd, &i, sizeof(i));
        sleep(1);  // Simulate processing delay

        if (read(socket_fd, &response, 1) > 0) {
            if (response == 'Y') {
                printf("Child %d: Purchase successful\n", id);
            } else {
                printf("Child %d: Purchase denied\n", id);
            }
        } else {
            perror("Read failed");
        }
    }

    close(socket_fd);
    exit(0);
}

