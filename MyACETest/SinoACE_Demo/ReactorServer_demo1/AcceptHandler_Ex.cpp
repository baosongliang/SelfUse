#include "AcceptHandler_Ex.h"
#include "ClientService_Ex.h"
#include "ace\OS.h"

int AcceptHandler_Ex::handle_input(ACE_HANDLE fd)
{
	ClientService_Ex* pPeer_handler = NULL;
	ACE_NEW_RETURN(pPeer_handler,ClientService_Ex(),-1);

	if (m_acceptor.accept(pPeer_handler->peer()) == -1)
	{
		ACE_OS::printf("Server Accept Failed!\n");

		pPeer_handler->handle_close(ACE_INVALID_HANDLE,0);
		return -1;
	}

	pPeer_handler->reactor(this->reactor());

	if (pPeer_handler->open() == -1) // Register client service handler.
	{
		pPeer_handler->handle_close(ACE_INVALID_HANDLE,0);
	}

	return 0;
}
