#include "AcceptHandler.h"
#include "ace\Reactor.h"
#include "ClientService.h"
#include "ace\OS.h"


int AcceptHandler::open(const ACE_INET_Addr &local_addr)
{
	if ( this->m_acceptor.open(local_addr,1) == -1 )
	{
		ACE_OS::printf("OPEN Server Failed!\n");
		return -1;
	}
	
	m_mask = ACE_Event_Handler::ACCEPT_MASK;

	return this->reactor()->register_handler(this,ACE_Event_Handler::ACCEPT_MASK);
}

int AcceptHandler::handle_input(ACE_HANDLE fd )
{
	ClientService* pPeer_handler = NULL;
	ACE_NEW_RETURN(pPeer_handler,ClientService(),-1);

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

int AcceptHandler::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)
{
	if (this->m_acceptor.get_handle () != ACE_INVALID_HANDLE)
	{
		ACE_Reactor_Mask m = ACE_Event_Handler::ACCEPT_MASK |
			ACE_Event_Handler::DONT_CALL;
		this->reactor ()->remove_handler (this, m);
		this->m_acceptor.close ();

		delete this;
	}

	return 0;
}
