#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(address);

    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Server address setup
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, SOMAXCONN) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        // Accept a connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len)) < 0)
        {
            perror("Accept failed");
            continue;
        }

        // Handle the connection in a separate process
        if (fork() == 0)
        {
            close(server_fd); // Child process doesn't need the listener

            // Receive and send data
            while (1)
            {
                int n = read(new_socket, buffer, BUFFER_SIZE - 1);
                if (n <= 0)
                {
                    break;
                }
                buffer[n] = '\0';
                printf("Received: %s\n", buffer);

                // Send "Pong!" back to the client
                const char *response = "Pong!";
                send(new_socket, response, strlen(response), 0);
            }

            // Close the connection
            close(new_socket);
            return 0;
        }
        else
        {
            close(new_socket); // Parent process doesn't need this socket
        }
    }

    close(server_fd);
    return 0;
}