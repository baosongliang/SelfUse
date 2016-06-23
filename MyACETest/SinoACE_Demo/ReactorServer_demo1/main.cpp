#include "AcceptHandler.h"
#include "AcceptHandler_Ex.h"
#include "ace/Reactor.h"
#include "ace/OS.h"

int main(int argc, char *argv[]) 
{
	/*AcceptHandler* pAcceptor;
	ACE_NEW_RETURN(pAcceptor,AcceptHandler(),-1);*/

	AcceptHandler_Ex* pAcceptor;
	ACE_NEW_RETURN(pAcceptor,AcceptHandler_Ex(),-1);


	pAcceptor->reactor(ACE_Reactor::instance());

	ACE_INET_Addr addr(1234);

	if (pAcceptor->open(addr) == -1)
	{
		ACE_OS::printf("Server open failed!\n");
	}

	pAcceptor->reactor()->run_event_loop();

	pAcceptor->handle_close(ACE_INVALID_HANDLE,0);

	return 0;
};