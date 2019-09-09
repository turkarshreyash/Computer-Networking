#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>

using namespace std;

#define PORT 6969

void* receive(void* data){
  int clientSocket = *(int*)data;
  char buffer[1024] = {};
  while(1){
    if(recv(clientSocket,buffer,sizeof(buffer),0)<=0) break;
    cout << '>';
    cout << "\033[1;32m" << buffer << "\033[0m" << endl;
  }
  pthread_exit(NULL);
}

void* sendd(void* data){
  int clientSocket = *(int*)data;
  char buffer[1024] = {};
  string input;
  while(1){
    getline(cin,input);
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

int main(int argc,char* argv[]){
  if(argc != 2){
    cout << "Incorrect number of arguments";
    exit(1);
  }
  int sockett;
  sockaddr_in serverAddress;
  sockett = socket(AF_INET,SOCK_STREAM,0);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  inet_pton(AF_INET,argv[1],&serverAddress.sin_addr);

  if(connect(sockett,(sockaddr*)&serverAddress,sizeof(serverAddress)) == -1){
    cout << "Error in establishing connection.";
    exit(1);
  }
  //All connections established. Ready to begin chat.
  pthread_t sender,receiver;
  pthread_create(&receiver,NULL,receive,&sockett);
  pthread_create(&sender,NULL,sendd,&sockett);
  //Chat has begun and is active.
  pthread_join(sender,NULL);
  pthread_cancel(receiver);
  cout << "\033[1;31mConversation ended\033[0m" << endl;
  close(sockett);
}
