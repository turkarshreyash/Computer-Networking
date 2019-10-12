#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h> 
#include <netdb.h> 

#define N 1024
#define PORT 7478

struct basic_frame{
    char m[N];
    int k;
};

int main(){
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd != -1){
        std::cout<<"Socket Created !  :-) \n";
    }else{
        std::cout<<"An Error Occured !  :-( \n";
        exit(0);
    }
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = PORT;

    
    if(connect(socketfd, (sockaddr*)&servaddr, sizeof(servaddr))){
        std::cout<<"Connection Est !\n";
    }else{
        std::cout<<"Connection Failed !\n";
        exit(0);
    }
} 
