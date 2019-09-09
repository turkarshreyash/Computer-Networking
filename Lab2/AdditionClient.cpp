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

int main(int argc,char* argv[]){
  if(argc != 2){
    cout << "Please provide argumets";
    exit(1);
  }
  int x,y,sockett;
  sockaddr_in serverAddress;
  sockett = socket(AF_INET,SOCK_STREAM,0);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  inet_pton(AF_INET,argv[1],&serverAddress.sin_addr);

  if(connect(sockett,(sockaddr*)&serverAddress,sizeof(serverAddress)) == -1){
    cout << "Error in establishing connection.";
    exit(1);
  }

  cin >> x >> y;
  send(sockett,&x,sizeof(x),0);
  send(sockett,&y,sizeof(y),0);
  recv(sockett,&x,sizeof(x),0);
  cout << x;
  close(sockett);
  return 0;
}
