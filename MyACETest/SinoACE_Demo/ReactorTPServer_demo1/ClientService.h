#ifndef __TEST_LOG_HANDLER_H
#define __TEST_LOG_HANDLER_H

#include "ace/Event_Handler.h"
#include "ace\SOCK_Stream.h"


class ClientService : public ACE_Event_Handler
{
public:
	ACE_SOCK_Stream& peer(){return m_peer;}

	int open();

	virtual int handle_input (ACE_HANDLE fd);

	/// Get the I/O handle.
	virtual ACE_HANDLE get_handle (void) const
	{
		return m_peer.get_handle();
	}

	virtual int handle_close (ACE_HANDLE handle ,ACE_Reactor_Mask close_mask );

protected:
	~ClientService(){}

	ACE_Reactor_Mask m_mask;
	ACE_SOCK_Stream m_peer;
};


#endif