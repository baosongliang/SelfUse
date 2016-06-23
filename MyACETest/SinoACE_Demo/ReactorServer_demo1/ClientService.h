#ifndef __TEST_LOG_HANDLER_H
#define __TEST_LOG_HANDLER_H

#include "ace/Event_Handler.h"
#include "ace\SOCK_Stream.h"


class ClientService : public ACE_Event_Handler
{
public:
	ClientService();

	~ClientService();

	ACE_SOCK_Stream& peer(){return m_peer;}

	int open();

	virtual int handle_input (ACE_HANDLE fd);

	virtual int handle_close (ACE_HANDLE handle ,ACE_Reactor_Mask close_mask );

private:
	ACE_Reactor_Mask m_mask;
	ACE_SOCK_Stream m_peer;
};


#endif