#include "ClientService.h"
#include "ace\Event_Handler.h"
#include "ace\Reactor.h"
#include "ace\OS.h"
#include <iostream>

ClientService::ClientService()
{

}

ClientService::~ClientService()
{

}

int ClientService::open()
{
	m_mask = ACE_Event_Handler::READ_MASK;
	return reactor()->register_handler(this,ACE_Event_Handler::READ_MASK);
}

int ClientService::handle_input(ACE_HANDLE fd /*= ACE_INVALID_HANDLE*/)
{
	char testBuf[512] = {0};
	int recvLen = 0;

	if( recvLen = m_peer.recv(testBuf,sizeof(testBuf)) < 0)
	{
		ACE_OS::printf("Recv Failed!\n");
		return -1; // 返回-1 ACE Reactor 将会自动调用 handle_close();
	}

	ACE_INET_Addr log_peerAddr;
	m_peer.get_remote_addr(log_peerAddr);

	ACE_OS::printf("Log_Peer Host name:%s port:%u, data:%s\n"
		,log_peerAddr.get_host_name()
		,log_peerAddr.get_port_number()
		,testBuf);

	m_peer.send(testBuf,recvLen); // Echo

	return 0;
}

int ClientService::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)
{
	if (close_mask == ACE_Event_Handler::WRITE_MASK)
		return 0;
	close_mask = ACE_Event_Handler::ALL_EVENTS_MASK |
		ACE_Event_Handler::DONT_CALL;

	this->reactor()->remove_handler (this, close_mask);
	this->m_peer.close ();
	delete this;    //socket出错时，将自动删除该客户端，释放相应资源
	return 0;
}
