#pragma once
#include <sys/socket.h>
class Selector
{
public:
    Selector();
    ~Selector();
    
    void ResetSelector(void)
    {
        FD_ZERO(&m_FdSet);
    }
    
    int Select(int nTimeOut = 10)
    {
        struct timeval tv = { 0, nTimeOut };
	    return select(FD_SETSIZE, &m_FdSet, 0, 0, &tv);
    }
    
    
    void AddSocket(int nSocketFd)
    {
        FD_SET(nSocketFd, &m_FdSet);
    }
    
    bool Check(int nSocketFd)
    {
        return FD_ISSET(nSocketFd, &m_FdSet);
    }
private:
    fd_set m_FdSet;
};

