#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <vector>

#include "client.h"

class BeaconsHandler : public Server
{

private:

public:
    BeaconsHandler();
    std::string receive_string();
    Boat *create_boat(const std::string &beacon_string) const;
    void start() override;

};

#endif // DATARECEIVER_H
