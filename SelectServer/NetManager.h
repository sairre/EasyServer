#pragma once
#include "SelectNet.h"


class NetManager
{
public:
    NetManager();
    ~NetManager();
    
    bool InitManager(void);
    
    int Dispatch();
    
    static int HandleNewConnection(ClientSession* pClient);
    
    static int HandleNewData(ClientSession* pClient);
    
    static int HandleLostConnection(ClientSession* pClient);
    
    
private:
    SelectNet * m_pSelectNet; 
};

