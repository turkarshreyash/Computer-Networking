#include<iostream>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 6969

int main(){
  int sockett,new_connect,valread;
  struct sockaddr_in server_addr;
  //struct sockaddr_in client_addr;
  int addrlen = sizeof(server_addr);
  char buffer[1024] = {0};

  if ((sockett = socket(AF_INET, SOCK_STREAM, 0)) == 0){
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  bind(sockett,(const sockaddr*)&server_addr,addrlen);

  listen(sockett,5);

  new_connect = accept(sockett,(struct sockaddr*)&server_addr,(socklen_t*)&addrlen);

  valread = read(new_connect,buffer,1024);
  printf("%s\n",buffer);
}
