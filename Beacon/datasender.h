#ifndef DATASENDER_H
#define DATASENDER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */

#define PORT 1338
#define SERV_ADDR "127.0.0.1"

using namespace std;

class DataSender {
private:
    struct sockaddr_in _serv_addr;
    int _serv_sock;
    string _message;

public:
    DataSender();
    ~DataSender();
    void send_string(string coordinates);
};

#endif // DATASENDER_H
