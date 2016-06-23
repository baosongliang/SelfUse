#ifndef __TEST_ACCEPT_HANDLER_EX_H
#define __TEST_ACCEPT_HANDLER_EX_H

#include "AcceptHandler.h"

class AcceptHandler_Ex : public AcceptHandler
{
public:

	virtual int handle_input (ACE_HANDLE fd);

protected:
	virtual ~AcceptHandler_Ex() {}
};




#endif