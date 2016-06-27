#ifndef __TEST_ACCEPT_HANDLER_H
#define __TEST_ACCEPT_HANDLER_H

#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"

class AcceptHandler : public ACE_Event_Handler
{
public:
	virtual ACE_HANDLE get_handle (void) const
	{ return this->m_acceptor.get_handle (); }

	virtual int open(const ACE_INET_Addr &local_addr);

	virtual int handle_input (ACE_HANDLE fd);

	virtual int handle_close (ACE_HANDLE handle,ACE_Reactor_Mask close_mask);

protected:
	virtual ~AcceptHandler(){}

	// Keep track of the events the handler's registered for.
	ACE_Reactor_Mask m_mask;
	ACE_SOCK_Acceptor m_acceptor;
};




#endif