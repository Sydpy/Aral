#include "socketmanager.h"

SocketManager::SocketManager()
{
    if((_sock = socket(AF_INET , SOCK_STREAM, 0)) == -1) {
        cerr << "Could not create socket";
        exit(EXIT_FAILURE);
    }

    //Définition de la connexions : adresse du serveur, port, ipv4 ...
    _server.sin_addr.s_addr = inet_addr("127.0.0.1");
    _server.sin_port = htons(PORT);
    _server.sin_family = AF_INET;
}

void SocketManager::tryConnect()
{
    //Connexion
    while(connect(_sock, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
        cerr << "connect failed on PORT : " << PORT << endl;
        sleep(1);
    }

    cout << "Connected to the server !" << endl;
}

void SocketManager::send_packet(Packet packet)
{
    if(send(_sock, &packet, sizeof(packet), 0) < 0)
    {
        cerr << "send failed, errno : " << errno << endl;
        exit(EXIT_FAILURE);
    }
}

void SocketManager::send_string(string msg)
{
    size_t len = msg.length();

    //On envoie la taille de la chaine de carac
    if(send(_sock, &len, sizeof(len), 0) < 0)
    {
        cerr << "send failed";
        exit(EXIT_FAILURE);
    }

    //Envoie la chaine de carac
    if(send(_sock, msg.c_str(), msg.length(), 0) < 0)
    {
        cerr << "send failed";
        exit(EXIT_FAILURE);
    }
}

Packet SocketManager::receive_packet()
{
    Packet packet;
    size_t bytes_received = 0;

    while(bytes_received < sizeof(Packet))
    {
        int received = recv(_sock, &packet+bytes_received, sizeof(Packet)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "receiving packet error !" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    return packet;
}

int SocketManager::receive_integer()
{
    int value;
    size_t bytes_received = 0;

    while(bytes_received < sizeof(int))
    {
        int received = recv(_sock, &value+bytes_received, sizeof(int)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "Error while receiving size of string" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }


    return value;
}

string SocketManager::receive_string()
{
    size_t str_len = 0;
    size_t bytes_received = 0;

    //On recoit la taille de la chaine que l'on va devoir récupérer
    while(bytes_received < sizeof(str_len))
    {
        int received = recv(_sock, &str_len+bytes_received, sizeof(str_len)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "Error while receiving size of string" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    bytes_received = 0;

    char *buffer = new char[str_len+1];
    memset(buffer, 0, str_len+1);

    //On récupère la chaine
    while(bytes_received < str_len)
    {
        int received = recv(_sock, buffer+bytes_received, str_len-bytes_received, 0);

        if(received == 0)
        {
            cerr << "Error while receiving string" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    return string(buffer);
}

SocketManager::~SocketManager()
{
    close(_sock);
}


