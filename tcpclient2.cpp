#include<iostream.h>
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")
//�������˿ں�5050
#define DEFAULT_PORT   5050

void main(int argc,char*argv[])
{
 WSADATA    wsaData;
 SOCKET     sockCli;
 int        iPort = DEFAULT_PORT;//�ӷ������˽��յ����ݳ���
 if (argc <2)
 {
    //��ʾ�������������������IP��ַ
  printf ("Usage:client [server IP address]\n");
   return;
 }

 if( WSAStartup ( MAKEWORD(2,2), & wsaData)!= 0)
 {
    printf("Failed to load Winsock.\n");
 return;
 }
 sockCli = socket(AF_INET,SOCK_STREAM,0);//�ͻ���ֻҪ����һ���׽��ֵ�ַ
 //��дҪ���ӵķ�������ַ��Ϣ
 SOCKADDR_IN addrSer;
addrSer.sin_family = AF_INET;
addrSer.sin_port = htons(iPort);
 //inet_addr���������������еĵ��IP��ַת��Ϊ�ö����Ʊ�ʾ�������ֽ�˳���IP��ַ
addrSer.sin_addr.S_un.S_addr = inet_addr(argv[1]);
int res = connect(sockCli,(SOCKADDR*)&addrSer,sizeof(SOCKADDR));
if(res)
{
printf("�ͻ������ӷ�����ʧ��");
return;
}
else
{
 printf("�ͻ������ӷ������ɹ�\n");
}
char sendbuf[256],recvbuf[256];
while(1)
{
printf("�ͻ���˵��>");
cin>>sendbuf;
if(strcmp(sendbuf,"bye")==0)
{
break;
}
send(sockCli,sendbuf,strlen(sendbuf)+1,0);
if(recv(sockCli,recvbuf,256,0)>0)
cout<<"������˵��>"<<recvbuf<<endl;
else
{
printf("�������ѹر�����");
break;
}
}
 closesocket(sockCli);
 WSACleanup();
 return;
}