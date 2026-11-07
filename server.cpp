#include<iostream>
#include<winsock2.h>
#include<fstream>
#pragma comment(lib,”ws2_32.lib”)
using namespace std;
int main(){WSADATA w;WSAStartup(MAKEWORD(2,2),&w);
SOCKET s=socket(AF_INET,SOCK_STREAM,0);
sockaddr_in a;a.sin_family=AF_INET;a.sin_addr.s_addr=INADDR_ANY;a.sin_port=htons(8080);
bind(s,(sockaddr*)&a,sizeof(a));listen(s,5);
cout<<“Waiting for client...\n”;
SOCKET c=accept(s,0,0);cout<<“Connected!\n”;
ofstream f(“data.txt”);char b[1024];
for(int i=0;i<100;i++){int n=recv(c,b,1023,0);if(n<=0)break;b[n]=0;f<<b;cout<<b;}
f.close();cout<<“Done! data.txt saved”;}
