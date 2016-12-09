#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SEND_PORT 9476
#define RECV_PORT 9477
#define BUFFER_SIZE 1024

using namespace std;

class ServerHandler {
private:
    // partie envoie de requêtes
    int _send_sock;
    struct sockaddr_in _server;
    char _send_buffer[BUFFER_SIZE];

    // partie réception de données
    int _recv_sock, _serv_sock;
    struct sockaddr_in _recv_addr, _serv_addr;
    char _recv_buffer[BUFFER_SIZE];

public:
    ServerHandler();

    void init_receive_socket();
    void init_send_socket();

    void send_request(string msg);
    void receive_data();

    void close_sockets();
};

#endif // SERVERHANDLER_H