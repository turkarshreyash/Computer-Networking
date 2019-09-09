#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 6969

int main(){
  int sockett;
  socklen_t clientLength;
  char message[256];
  sockaddr_in Address,clientAddress;

  Address.sin_family = AF_INET;
  Address.sin_port = htons(PORT);
  Address.sin_addr.s_addr = INADDR_ANY;

  sockett = socket(AF_INET,SOCK_DGRAM,0);
  bind(sockett,(sockaddr*)&Address,sizeof(Address));
  int n = recvfrom(sockett,message,sizeof(message),MSG_WAITALL,(sockaddr*)&clientAddress,&clientLength);
  message[n] = '\0';
  printf("%s\n",message);
  return 0;
}
