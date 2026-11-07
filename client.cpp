#include<iostream>
#include<winsock2.h>
#pragma comment(lib,”ws2_32.lib”)
using namespace std;
int main(){WSADATA w;WSAStartup(MAKEWORD(2,2),&w);
SOCKET s=socket(AF_INET,SOCK_STREAM,0);
sockaddr_in a;a.sin_family=AF_INET;a.sin_port=htons(8080);
string ip;cout<<“Enter Server IP: “;cin>>ip;
a.sin_addr.s_addr=inet_addr(ip.c_str());
if(connect(s,(sockaddr*)&a,sizeof(a))<0){cout<<“Failed!”;return 1;}
for(int i=1;i<=100;i++){char b[100];
sprintf(b,”Record %d time=%.2fs temp=%dC\n”,i,7.21+(i-1)*0.01,20+rand()%15);
send(s,b,strlen(b),0);cout<<“Sent: “<<b;}
cout<<“All 100 Sent!”;}
