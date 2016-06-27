#include "AcceptHandler_Ex.h"
#include "ace/Reactor.h"
#include "ace/TP_Reactor.h"
#include "ace/OS.h"
#include "ace/Auto_Ptr.h"
#include "ace/Event_Handler.h"
#include "ace/Thread_Manager.h"

static ACE_THR_FUNC_RETURN event_loop(void *arg)
{
	ACE_Reactor *reactor = static_cast<ACE_Reactor*>(arg);

	reactor->owner(ACE_OS::thr_self());
	reactor->run_reactor_event_loop();

	return 0;
}


int main(int argc, char *argv[]) 
{
	const size_t N_THREADS = 2;
	ACE_TP_Reactor tp_reactor;
	ACE_Reactor reactor(&tp_reactor);
	auto_ptr<ACE_Reactor> delete_instance(ACE_Reactor::instance(&reactor));

	AcceptHandler_Ex* pAcceptor;
	ACE_NEW_RETURN(pAcceptor,AcceptHandler_Ex(),-1);
	pAcceptor->reactor(ACE_Reactor::instance());

	ACE_INET_Addr addr(1234);

	if (pAcceptor->open(addr) == -1)
	{
		ACE_OS::printf("Server open failed!\n");
	}

	ACE_Thread_Manager::instance()->spawn_n(N_THREADS,event_loop,ACE_Reactor::instance());


	ACE_Thread_Manager::instance()->wait();

	pAcceptor->handle_close(ACE_INVALID_HANDLE,0);

	return 0;
};