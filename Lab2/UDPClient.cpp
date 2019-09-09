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
  sockaddr_in serverAddress;
  char message[256] = "Message from client";
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  sockett = socket(AF_INET,SOCK_DGRAM,0);

  sendto(sockett,message,sizeof(message),MSG_CONFIRM,(sockaddr*)&serverAddress,sizeof(serverAddress));
  printf("Message sent\n");
  return 0;
}
