#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080

// Get current time in milliseconds
long long current_time_in_ms()
{
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec * 1000LL) + (time_now.tv_usec / 1000);
}

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Ping!";

    // Create TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Server address setup
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    // Record start time
    long long start_time = current_time_in_ms();

    // Send message to server
    send(sockfd, buffer, strlen(buffer), 0);
    printf("Message sent to server\n");

    // Receive server response
    int n = read(sockfd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';

    // Print the received message
    printf("Received from server: %s\n", buffer);

    // Record end time
    long long end_time = current_time_in_ms();

    // Calculate RTT
    long long rtt = end_time - start_time;
    printf("RTT: %lld ms\n", rtt);

    close(sockfd);
    return 0;
}