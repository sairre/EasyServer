#pragma once
#include "Common.h"
#include "Selector.h"
#include "ClientSession.h"
#include <list>

class SelectNet
{
public:
    SelectNet();
    ~SelectNet();
    
    bool CreateServer(void);
    
    int Update(void);
    
    int HandleNewConnection();
    
    int HandleData();
    
    int RefreshClients();
    
    int AttachNewConnection(NEW_CONNECTION_HOOK pFunc)
    {
        m_pNewConnection = pFunc;
    }
    
    int AttachNewData(NEW_DATA_HOOK pFunc)
    {
        m_pNewData = pFunc;
    }
    
    int AttachLostConnection(LOST_CONNECTION_HOOK pFunc)
    {
        m_pLostConnection = pFunc;
    }
    
private:
    
    int m_ServerListenSocketFd;
    

    fd_set m_FdRSet;
    
    ClientSessionList m_ClientList;
    
    NEW_CONNECTION_HOOK m_pNewConnection;
    NEW_DATA_HOOK m_pNewData;
    LOST_CONNECTION_HOOK m_pLostConnection;
    
};

