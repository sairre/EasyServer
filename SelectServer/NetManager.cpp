#include "NetManager.h"

#include <stddef.h>
#include <iostream>
NetManager::NetManager()
{
}


NetManager::~NetManager()
{
}


bool NetManager::InitManager(void)
{
    m_pSelectNet = new SelectNet();
    if (NULL == m_pSelectNet)
    {
        return false;
    }
   
    m_pSelectNet->CreateServer();
    m_pSelectNet->AttachNewConnection(HandleNewConnection);
    m_pSelectNet->AttachNewData(HandleNewData);
    m_pSelectNet->AttachLostConnection(HandleLostConnection);
    
    return true;
}

int NetManager::Dispatch()
{
    while (true)
    {
        m_pSelectNet->Update();
        
    }
}


int NetManager::HandleNewConnection(ClientSession* pClient)
{
    std::cout << "new connection comes " << std::endl;
    return 0;
}


int NetManager::HandleNewData(ClientSession* pClient)
{
    std::cout << "new data comes " << std::endl;
    return 0;
}


int NetManager::HandleLostConnection(ClientSession* pClient)
{
    std::cout << "lost connection " << std::endl;
    return 0;
}
