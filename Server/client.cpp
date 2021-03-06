#include "client.h"
#include "clientshandler.h"

using namespace std;

int Client::_current_id = 0;

Client::Client(int sock, sockaddr_in addr, ClientsHandler &clients_handler) : _client_id(_current_id++), _sock(sock), _addr(addr), _clients_handler(clients_handler), _job(&Client::process_requests, this), _job_active(true)
{

}

//Lance un thread qui va gérer toutes les demandes du client
void Client::manage()
{
    _job.detach();
}

void Client::process_requests()
{
    cout << "Thread of client " << _client_id << " is beginning" << endl;

    vector<Boat*> boats = _clients_handler.getBoats();

    while(_job_active)
    {
        Packet packet = _clients_handler.receive_packet_from(this);

        if(packet == GET_ALL_BOATS)
        {
            cout << "Client " << _client_id << " asks GET_ALL_BOATS !" << endl;
            _clients_handler.send_integer_to(this, boats.size()); //On envoit le nombre de bateaux à réceptionner

            cout << "sending the " << boats.size() << " boats" << endl;

            for(int i = 0; i < (int)boats.size(); i++)
                _clients_handler.send_string_to(this, boats.at(i)->toString());
        }

        else if(packet == ERROR)
        {
            _job_active = false;
        }
    }

    cout << "Thread of client " << _client_id << " is stopping" << endl;
}

int Client::getSocket()
{
    return _sock;
}

sockaddr_in Client::getAddr()
{
    return _addr;
}

int Client::getId()
{
    return _client_id;
}

Client::~Client()
{
    _job_active = false;
    close(_sock);
}
