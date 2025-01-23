#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "child_exe.h"
#include "Product.h"
#include "funky.h"
#include "Order.h"

#define PORT 8080

int main() {
    printf("Starting the main process\n");
    fflush(stdout);

    pid_t pid; 
    int i, k, m, customer;
    struct sockaddr_in address;
    int addr_length = sizeof(address);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    // Counters for the final report
    int orders = 0, completed = 0, income = 0;

    // Arrays for products and orders
    Product array1[10];
    Order array2[10];

    // Initialize products
    printf("Initializing products\n");
    fflush(stdout);

    const char *descriptions[10] = {
        "tv 4k 55inch", "gaming keyboard", "gaming mouse", 
        "mousepad", "gaming headphones", "f175 carlos sainz 1/43 car model", 
        "gaming computer", "gaming monitor", "ps5 pro", 
        "ps5 controller dualsense"
    };
    int prices[10] = {650, 120, 80, 12, 65, 49, 2350, 350, 750, 75};

    for (i = 0; i < 10; i++) {
        strcpy(array1[i].desc, descriptions[i]);
        array1[i].price = prices[i];
        array1[i].item_count = 2;
        array2[i].requests = 0;
        array2[i].sold = 0;
        memset(array2[i].canceled, 0, sizeof(array2[i].canceled));
    }

    // Create a listening socket in the parent
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Parent process listening on port %d\n", PORT);
    fflush(stdout);

    // Fork child processes after ensuring the socket is ready
    for (int child_id = 1; child_id <= 5; child_id++) {
        pid = fork();
        if (pid == 0) {
            printf("Starting child process %d\n", child_id);
            fflush(stdout);
            child_exe(&address, child_id);
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process accepts client connections
    for (m = 0; m < 5; m++) {
        int accept_fd = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&addr_length);
        if (accept_fd < 0) {
            perror("Accept failed");
            continue;
        }

        for (i = 0; i < 10; i++) {
            int product_index, total_price;
            customer = i / 10;
            product_index = i % 10;
            orders++;

            read(accept_fd, &i, sizeof(i));

            total_price = funky(array1, array2, product_index);
            if (total_price == 0) {
                total_price = array1[product_index].price;
                income += total_price;
                completed++;
                char response = 'Y';
                write(accept_fd, &response, 1);
                printf("Client %d: Purchase complete! Total: %d €\n", customer, total_price);
            } else {
                array2[product_index].canceled[customer - 1] = 1;
                char response = 'N';
                write(accept_fd, &response, 1);
                printf("Client %d: Request denied\n", customer);
            }
        }

        close(accept_fd);
    }

    close(socket_fd);

    // Wait for all child processes to terminate
    while (wait(NULL) > 0);

    // Generate final reports
    printf("\nFinal Reports:\n");
    printf("-----------------------\n");
    for (i = 0; i < 10; i++) {
        printf("Product %d: %s\n", i + 1, array1[i].desc);
        printf("  Requests: %d\n", array2[i].requests);
        printf("  Sales: %d\n", array2[i].sold);
        printf("  Unserved Clients: ");
        int served_flag = 0;
        for (k = 0; k < 5; k++) {
            if (array2[i].canceled[k]) {
                printf("Client %d ", k + 1);
                served_flag = 1;
            }
        }
        if (!served_flag) printf("None");
        printf("\n");
    }

    printf("\nTotal Orders: %d\n", orders);
    printf("Total Completed: %d\n", completed);
    printf("Total Income: %d €\n", income);

    return 0;
}

