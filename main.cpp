#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

int main(int argc, char *argv[])
{
    WSADATA wsaData;
       if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
           cout << "WSAStartup failed.\n";
           system("pause");
           return 1;
       }
       SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
       struct hostent *host;
       host = gethostbyname("www.ispeech.org");
       SOCKADDR_IN SockAddr;
       SockAddr.sin_port=htons(80);
       SockAddr.sin_family=AF_INET;
       SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
       cout << "Connecting...\n";
       if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
           cout << "Could not connect";
           system("pause");
           return 1;
       }
       cout << "Connected.\n";
       send(Socket,"GET /p/generic/getaudio?text=demo%2C&voice=usspanishmale&speed=0&action=convert HTTP/1.1\r\nHost: www.ispeech.org\r\nConnection: keep-alive\r\n\r\n", strlen("GET /p/generic/getaudio?text=demo%2C&voice=usspanishmale&speed=0&action=convert HTTP/1.1\r\nHost: www.ispeech.org\r\nConnection: keep-alive\r\n\r\n"),0);
       char buffer[19440];
       int nDataLength;
       while ((nDataLength = recv(Socket,buffer,19440,0)) > 0){
           int i = 0;
            int count = sizeof(buffer)/sizeof(buffer[0]);
            cout << count;
            cout << '-';
           while (i <= count) {

               if(buffer[i] == '\r' & buffer[i+1] == '\n' & buffer[i+3] == '\n')
               {
                    cout << '+';
                    cout << buffer[i+10];
                    cout << '+';

               }
                i += 1;
           }
           //while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
                //cout << buffer;
               //printf(cout);

           //}
       }
       closesocket(Socket);
           WSACleanup();
       system("pause");

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    return 0;
    //return a.exec();
}
