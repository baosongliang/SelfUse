#include "ClientService_Ex.h"
#include "ace\Reactor.h"
#include "ace\Abstract_Timer_Queue.h"

int ClientService_Ex::open()
{
	int result = PARENT::open();

	if (result != -1)
	{
		ACE_Time_Value rescheduleTime( m_maxClientTimeout.sec() / 2 );
		result = reactor()->schedule_timer(this,0
			,m_maxClientTimeout // Initial timeout
			,rescheduleTime);// Subsequent timeout
	}

	return result;
}

int ClientService_Ex::handle_input(ACE_HANDLE fd)
{
	m_lastRecordTime = reactor()->timer_queue()->gettimeofday();

	return PARENT::handle_input(fd);
}

int ClientService_Ex::handle_timeout(const ACE_Time_Value &current_time, const void *act /* = 0 */)
{
	if (current_time - m_lastRecordTime >= m_maxClientTimeout)
	{
		std::string byeStr("Time out!");
		m_peer.send(byeStr.c_str(),byeStr.size());
		reactor()->remove_handler(this,ACE_Event_Handler::READ_MASK); // handle_close() will be automatically called then.
	}

	return 0;
}

int ClientService_Ex::handle_close(ACE_HANDLE handle ,ACE_Reactor_Mask close_mask)
{
	reactor()->cancel_timer(this);
	return PARENT::handle_close(ACE_INVALID_HANDLE,0);
}

