#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>

using namespace std;

#define PORT 6969

sem_t print;

void* receive(void* data){
  int clientSocket = *(int*)data;
  char buffer[1024] = {};
  while(1){
    if(recv(clientSocket,buffer,sizeof(buffer),0)<=0) break;
    sem_wait(&print);
    cout << '>';
    cout << "\033[1;32m" << buffer << "\033[0m" << endl;
    sem_post(&print);
  }
  pthread_exit(NULL);
}

void* sendd(void* data){
  int clientSocket = *(int*)data;
  char buffer[1024] = {};
  string input;
  while(1){
    sem_wait(&print);
    getline(cin,input);
    sem_post(&print);
    strcpy(buffer,input.c_str());
    if(!strcmp(buffer,"EXIT")){
      strcpy(buffer,"Person has left the chat");
      send(clientSocket,buffer,sizeof(buffer),0);
      break;
    }
    send(clientSocket,buffer,sizeof(buffer),0);
  }
  pthread_exit(NULL);
}

int main(){
  int sockett,clientSocket;
  sockaddr_in serverAddress;
  sockett = socket(AF_INET,SOCK_STREAM,0);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  bind(sockett,(sockaddr*)&serverAddress,sizeof(serverAddress));
  cout << "\033[1;33mWaiting for client to connect\033[0m" << endl;
  listen(sockett,0);
  clientSocket = accept(sockett,NULL,NULL);
  //All connections established. Ready to begin chat.

  sem_init(&print,0,1);
  pthread_t sender,receiver;
  pthread_create(&receiver,NULL,receive,&clientSocket);
  pthread_create(&sender,NULL,sendd,&clientSocket);
  //Chat has begun and is active.
  pthread_join(sender,NULL);
  pthread_cancel(receiver);
  cout << "\033[1;31mConversation ended\033[0m" << endl;
  close(sockett);
  close(clientSocket);
}
