#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
 
#define MAXLINE 1024
int main(int argc, char *argv[])
{
	char *servInetAddr = "127.0.0.1";
	int socketfd;
	struct sockaddr_in sockaddr;
	char recvline[MAXLINE], sendline[MAXLINE];
	int n;
 
//	if (argc != 2)
//	{
//		printf("client <ipaddress> \n");
//		exit(0);
//	}
	fd_set fdSet;
	fd_set fdWSet;
    FD_ZERO(&fdSet);
    FD_ZERO(&fdWSet);
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
   
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(10004);
	inet_pton(AF_INET, servInetAddr, &sockaddr.sin_addr);
	if ((connect(socketfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) < 0)
	{
		printf("connect error %s errno: %d\n", strerror(errno), errno);
		exit(0);
	}

    
    while (true)
    {
       
        FD_ZERO(&fdSet);
        FD_ZERO(&fdWSet);
        //FD_SET(0, &fdSet);
        FD_SET(socketfd, &fdSet);
        FD_SET(socketfd, &fdWSet);
        struct timeval tv = { 0, 10 };
        int nRet = select(FD_SETSIZE, &fdSet, &fdWSet, 0, &tv);
        if (nRet > 0)
        {
            if (FD_ISSET(socketfd, &fdSet))
            {
                int nLen = 0;
                char buff[1024] = { 0 };
                recv(socketfd, &nLen, 4, 0);
                
                int nRec = 0;
                while (nRec < nLen)
                {
                    nRec += recv(socketfd, buff + nRec, nLen, 0);
                }
                
                std::cout << "recive " << std::endl;
                std::cout << strlen(buff) << " " << buff << " " << std::endl;
            }
            
            if (FD_ISSET(socketfd, &fdWSet))
            {
                std::cout << "sendddddd " << std::endl;
                char buff[1024] = "But detailed analysis of the expression in use turns up a rather more interesting phenomenon. In the expression, 'gold' is of course used as a metaphor for something exceptionally good. Correspondingly, speaker creativity has led to a fascinating extension of the gold metaphor into surrounding language, so we see examples of verb collocations like mine, strike, hit, unearth, spin/turn into comedy gold, noun phrases such as comedy goldmines, nuggets/pieces of comedy gold, a treasure trove of comedy gold, modifying adjectives like pure or 24-carat comedy gold, or, inspired by the legend of king Midas, someone's capacity to generate amusing things characterised as everything he/she touches turns to comedy gold. There's some evidence that the precious metal idea is played around with too ¨C so just as bronze is less valuable than gold, so comedy bronze has correspondingly popped up as a tongue-in-cheek reference to something inferior on the funniness scale.";
                int nLen = strlen(buff);
                send(socketfd, &nLen, 4, 0);
                int nSend = 0;
                while (nSend < nLen)
                {
                    nSend += send(socketfd, buff + nSend, nLen, 0);
                }
             
            }
            
            
        
//            if (FD_ISSET(0, &fdSet))
//            {
//                char buff[1024] = { 0 };
//                scanf("%s", buff);
//           
//                send(socketfd, buff, strlen(buff), 0);
//                std::cout << "send " << std::endl;
//            
//            }
        }

 
 
    }
	
	close(socketfd);
	printf("exit\n");
	exit(0);
}