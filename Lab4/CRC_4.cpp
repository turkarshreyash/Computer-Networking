#include<iostream>
#include"CRC_4.h"

int CRC::divisor[4] = {1,0,1,1};
int CRC::temp[4] = {0,0,0,0};  

bool CRC::copy(int* data, int start, int len){
    int i = start;
    for(; i < len && i < start + 4; i++){
        temp[i] = data[i];
        std::cout<<temp[i]<<"\t";
    }
    std::cout<<"\n"<<i<<"\n"<<start+3<<"\n";
    if(i != start + 4){
        return 1;
    }
    return 0;
}

void CRC::_xor(){
    for(int i = 0; i < 3 ; i++){
        temp[i] ^= CRC::divisor[i];
    }
}

void CRC::generate_CRC(int* data, int len){
    int current = 0;
    bool run;
    while(current < len){
        //std::cout<<"RUnning";
        while(data[current] == 0){
            current++;
        }
        run = CRC::copy(data, current, len);
        //std::cout<<run<<":RUN\n";
        if(run){
            return;
        }
        CRC::_xor();
        std::cout<<"running..\n";
    }
}

void CRC::get_reminder(){

    for(int i = 0 ; i < 3 ; i++){
        std::cout<<temp[i]<<"\n";
    }
}