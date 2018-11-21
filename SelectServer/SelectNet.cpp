#include "SelectNet.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>

SelectNet::SelectNet()
{
}


SelectNet::~SelectNet()
{
}

bool SelectNet::CreateServer(void)
{
    m_ServerListenSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(10004);
    my_addr.sin_addr.s_addr = INADDR_ANY;
	
    int nRet = bind(m_ServerListenSocketFd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    if (-1 == nRet)
    {
        close(m_ServerListenSocketFd);
        m_ServerListenSocketFd = 0;
        return false;
    }

    listen(m_ServerListenSocketFd, 5);
    return true;
}

int SelectNet::Update( void )
{
	FD_ZERO(&m_FdRSet);
    
    // 加入服务器监听socket,是为了处理accept，处理到来的新连接
    
    FD_SET(m_ServerListenSocketFd, &m_FdRSet);
    
    // 重新添加客户端连接,并判断有效
    ClientSessionList::iterator iter = m_ClientList.begin();
    for (; iter != m_ClientList.end(); ++iter)
    {
        ClientSession* pClientSession = (*iter);
        if (NULL == pClientSession)
        {
            continue;
        }
        FD_SET(pClientSession->GetSocket(), &m_FdRSet);
    }
    
    struct timeval tv = { 0, 10 };
    int nRet = select(FD_SETSIZE, &m_FdRSet, 0, 0, &tv);
    if (nRet > 0)
    {
		// 存在可读事件
		// 处理服务器监听socket 新到来连接
        HandleNewConnection();

                    // 处理客户端发来的数据
        HandleData();
    }
	
	RefreshClients();
   	 
}

int SelectNet::HandleNewConnection()
{
    if (FD_ISSET(m_ServerListenSocketFd, &m_FdRSet))
    {
    	// 服务器监听socket 在 selector 中，说明有事件
    	// 对于服务器socket,事件就是有新的连接到来
        std::cout << "new con " << std::endl;
        int clientSocket =:: accept(m_ServerListenSocketFd, NULL, NULL);
        if (0 == clientSocket)
        {
            return 0;
        }

        ClientSession* pClientSession = new ClientSession(clientSocket);
        m_ClientList.push_back(pClientSession);
        
        m_pNewConnection(pClientSession);

    }
}

int SelectNet::HandleData()
{
    ClientSessionList::iterator iter = m_ClientList.begin();
    for (; iter != m_ClientList.end(); ++iter)
    {
        ClientSession* pSession = (*iter);
        if (NULL == pSession)
        {
            continue;
        }


        if (FD_ISSET(pSession->GetSocket(), &m_FdRSet))
        {
        	// 判断客户端是否有可读事件到来
	        char buff[1024] = { 0 };
            int nLen = 0;
            int nRet = recv(pSession->GetSocket(), &nLen, 4, 0);
            if (0 == nRet)
            {
                pSession->SetDisConnect();
                std::cout << "client disconnected ! " << std::endl;
                return 0;
            }
            std::cout << "recive " <<  nLen << std::endl;
            int nRec = 0;
            while (nRec < nLen)
            {
                nRec += recv(pSession->GetSocket(), buff + nRec, nLen, 0) ;
            }
           
            //std::cout << "get data" << std::endl;
            //std::cout << buff << std::endl;
            //send(pSession->GetSocket(), buff, strlen(buff), 0);
            
          
            send(pSession->GetSocket(), &nLen, 4, 0);
            int nSend = 0;
            while (nSend < nLen)
            {
                nSend += send(pSession->GetSocket(), buff + nSend, nLen, 0);
            }
        
        }
    }
}


int SelectNet::RefreshClients()
{
     /// 清除无效客户端连接
    ClientSessionList::iterator iter = m_ClientList.begin();
    for (; iter != m_ClientList.end();)
    {
        ClientSession* pSession = (*iter);
        if (NULL == pSession)
        {
            iter = m_ClientList.erase(iter);
            continue;
        }
        if (pSession->IsDisconnected())
        {
            iter = m_ClientList.erase(iter);
            continue;
        }

        ++iter;
    }
}
