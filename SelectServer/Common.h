#pragma once
#include <list>
class ClientSession;
typedef std::list<ClientSession*> ClientSessionList;
typedef int(*NEW_CONNECTION_HOOK)(ClientSession* pClient);
typedef int(*NEW_DATA_HOOK)(ClientSession* pClient);
typedef int(*LOST_CONNECTION_HOOK)(ClientSession* pClient);
