#include "ClientSession.h"





 ClientSession::ClientSession( int nSocketFd )
{
	m_nSocketFd = nSocketFd;
    m_bDisConnected = false;
}

ClientSession::~ClientSession()
{
}
