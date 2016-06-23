#include "AcceptHandler.h"
#include "ace/Reactor.h"
#include "ace/OS.h"

int main(int argc, char *argv[]) 
{
	AcceptHandler acceptor;
	acceptor.reactor(ACE_Reactor::instance());

	ACE_INET_Addr addr(1234);

	if (acceptor.open(addr) == -1)
	{
		ACE_OS::printf("Server open failed!\n");
	}

	acceptor.reactor()->run_event_loop();

	return 0;
};