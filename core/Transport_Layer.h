#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

#include<iostream>
#include<stdint.h>

#define MAX_USER_DATA_LEN 255

struct data_gram{
    uint16_t segment_number;
    uint16_t lenght;
    char user_data[255];
};

class TransportLayer{
    public:
        void to_transport_layer(char*, uint32_t, char*, uint16_t);

};


#endif //TRANSPORT_LAYER_H
