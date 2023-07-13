#include <string>
using namespace std;

#ifndef _NETWORK_h
#define _NETWORK_h

/**
 * @file network.h
 * @brief Déclaration de la classe Network 
 *
 * @version 1.0
 *
 * @author Team Epitech (FPKGA)
 */

/**
 * @class Network
 * @brief Declaration of the class Network
 * @details This class is used to connect to the network and send data to the API
 */

class Network
{

private:
    char *ssid;
    char *password;

public:
    void connection(char *ssid, char *password);
    int postBMP(char *url, char *data);
    int postDust(char *url, char *data);
    int get(char *url);
};

extern Network network;
#endif