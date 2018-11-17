#pragma once
class ClientSession
{
public:
    
    ~ClientSession();
    explicit ClientSession(int nSocketFd);
    int GetSocket()
    {
        return m_nSocketFd;
    }
    
    bool IsDisconnected()
    {
        return m_bDisConnected;
    }
    
    bool SetDisConnect()
    {
        m_bDisConnected = true;
    }
    
private:
    int m_nSocketFd;
    bool m_bDisConnected;
};

