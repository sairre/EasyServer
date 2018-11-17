#include <iostream>
#include "NetManager.h"
using namespace std;

int main(int argc, char *argv[])
{
	char sz[] = "Hello, World!";	//Hover mouse over "sz" while debugging to see its contents
	cout << sz << endl;	//<================= Put a breakpoint here
    
    NetManager * pManager = new NetManager();
    if (NULL != pManager)
    {
        pManager->InitManager();
        pManager->Dispatch();
    }
	return 0;
}