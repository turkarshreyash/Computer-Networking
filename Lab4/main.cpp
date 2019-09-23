#include<iostream>
#include<stdlib.h>
#include"CRC_4.h"

int main(int argc, char *argv[]){
    //11110001011
    //11
    int temp;
    int *data = new int[argc-1];
    for(int i = 1 ; i < argc ;i++){
        data[i-1] = atoi(argv[i]);
        //std::cout<<data[i]<<"\n";
    }
    CRC::generate_CRC(data,argc-1);
    CRC::get_reminder();

}

