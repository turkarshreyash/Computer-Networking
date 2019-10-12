#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include<iostream>
#include<cmath>
#include"Tranport_Layer.h"

/*
Flow Control Sliding window
window size -> variable
*/

struct packet{
    char IP_Addr[12]; //destination
    uint16_t port_number; //destination_port
    data_gram payload;
    uint16_t sequence_number;
};

class NetworkLayer{

    uint16_t window_size;
    uint16_t current_sequence_no;
    packet *window;
    bool *recv_ack;
        
    public:
        NetworkLayer(uint16_t);
        void rx_handler();
        void sendTo(data_gram playload, char* IP_Addr, uint16_t port_number); 
};

#endif //NETWORK_LAYER_H