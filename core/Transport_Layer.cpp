#include<iostream>
#include<cmath>
#include"Transport_Layer.h"


void TransportLayer::to_transport_layer(char* data, uint32_t length, char* IPAdrr, uint16_t port){
    uint16_t no_of_segments = length/MAX_USER_DATA_LEN;
    if(length%MAX_USER_DATA_LEN != 0){
        no_of_segments++;
    }

    
    




}
