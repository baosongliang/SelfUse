#ifndef __TEST_LOG_HANDLER_EX_H
#define __TEST_LOG_HANDLER_EX_H

#include "ClientService.h"
#include "ace\Time_Value.h"


// ClientService_Ex 相较于 ClientService使用了定时队列，相当于心跳包机制
class ClientService_Ex : public ClientService
{
public:
	ClientService_Ex()
		:m_maxClientTimeout(60*5){ }

	typedef ClientService PARENT;

	int open();

	virtual int handle_input (ACE_HANDLE fd);

	virtual int handle_timeout(const ACE_Time_Value &current_time, const void *act /* = 0 */);

	virtual int handle_close (ACE_HANDLE handle ,ACE_Reactor_Mask close_mask );

protected:
	~ClientService_Ex(){}

private:
	// Time when a client last sent a msg.
	ACE_Time_Value m_lastRecordTime;
	
	// Maximum time to wait for a client msg.
	const ACE_Time_Value m_maxClientTimeout;
};


#endif