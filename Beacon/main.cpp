#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */

#include "datasender.h"

#define BEACON //On se définit comme étant une balise afin de ne pas compiler ce qui ne nous concerne pas dans boat.h et boat.cpp
#include "../Common/boat.h"

using namespace std;

double random_range(double min, double max)
{
    return min + (double)rand() / RAND_MAX * (max - min);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
       cerr << "Usage : " << argv[0] << " [boat_name]" << endl;
       exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    Boat boat(argv[1]);
    boat.setCap(static_cast<Cap>(rand() % 4 + 1));

    //position aléatoire dans le golf du mexique
    //45.522321 59.427795
    //44.414753 59.878235
    double latitude = random_range(44.414753, 45.522321);
    double longitude = random_range(59.427795, 59.878235);
    boat.setLocation(latitude, longitude);


    DataSender sender;

    while(1)
    {
        sender.send_string(boat.toString());
        sleep(1);
    }

    return 0;
}

