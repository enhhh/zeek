#ifndef _ZEEK_REST_STATE_H
#define _ZEEK_REST_STATE_H
#include "object/Zeek.h"
#include "AI/stateMachine/state.h"

class ZeekRestState
	: public State<Zeek>
{


	virtual void enter(Zeek *)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void execute(Zeek *)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void exit(Zeek *)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};
#endif // !_ZEEK_REST_STATE_H
