# Ping Pong in C
This is a simple program that demonstrates the client-server model in C. The client sends a "ping" message to the server, and the server responds with a "pong" message.
# Compilation
```bash
gcc -o server server.c -O3
gcc -o client client.c -O3
```

# Execution
Open two terminals and run the following commands in each terminal:   
Terminal 1:
```bash
./server
```
Terminal 2:
```bash
./client
```