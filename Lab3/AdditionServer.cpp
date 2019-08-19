#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

#define PORT 6969

void* ThreadAdd(void* data){
  int x,y,sockett;
  sockett = *(int*)data;
  recv(sockett,&x,sizeof(x),0);
  recv(sockett,&y,sizeof(y),0);
  x += y;
  send(sockett,&x,sizeof(x),0);
  pthread_exit(NULL);
}

int main(){
  int sockett,clientSocket;
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  sockett = socket(AF_INET,SOCK_STREAM,0);
  bind(sockett,(sockaddr*)&serverAddress,sizeof(serverAddress));
  listen(sockett,10);
  pthread_t tid[10];
  int i=0;
  while(1){
    clientSocket = accept(sockett,NULL,NULL);
    pthread_create(&tid[i++],NULL,ThreadAdd,&clientSocket);
    if(i>=10){
      i=0;
      while(i<10) pthread_join(tid[i],NULL);
      i=0;
    }
  }
}
