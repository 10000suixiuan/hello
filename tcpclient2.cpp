#include<iostream.h>
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")
//服务器端口号5050
#define DEFAULT_PORT   5050

void main(int argc,char*argv[])
{
 WSADATA    wsaData;
 SOCKET     sockCli;
 int        iPort = DEFAULT_PORT;//从服务器端接收的数据长度
 if (argc <2)
 {
    //提示在命令行中输入服务器IP地址
  printf ("Usage:client [server IP address]\n");
   return;
 }

 if( WSAStartup ( MAKEWORD(2,2), & wsaData)!= 0)
 {
    printf("Failed to load Winsock.\n");
 return;
 }
 sockCli = socket(AF_INET,SOCK_STREAM,0);//客户端只要创建一个套接字地址
 //填写要链接的服务器地址信息
 SOCKADDR_IN addrSer;
addrSer.sin_family = AF_INET;
addrSer.sin_port = htons(iPort);
 //inet_addr（）函数将命令行的点分IP地址转化为用二进制表示的网络字节顺序的IP地址
addrSer.sin_addr.S_un.S_addr = inet_addr(argv[1]);
int res = connect(sockCli,(SOCKADDR*)&addrSer,sizeof(SOCKADDR));
if(res)
{
printf("客户端连接服务器失败");
return;
}
else
{
 printf("客户端连接服务器成功\n");
}
char sendbuf[256],recvbuf[256];
while(1)
{
printf("客户端说：>");
cin>>sendbuf;
if(strcmp(sendbuf,"bye")==0)
{
break;
}
send(sockCli,sendbuf,strlen(sendbuf)+1,0);
if(recv(sockCli,recvbuf,256,0)>0)
cout<<"服务器说：>"<<recvbuf<<endl;
else
{
printf("服务器已关闭连接");
break;
}
}
 closesocket(sockCli);
 WSACleanup();
 return;
}