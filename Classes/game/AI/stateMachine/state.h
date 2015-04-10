#ifndef __ZEEK_STATE__H
#define __ZEEK_STATE__H

template <class entity_type>

class State
{
public:
	~State(){}

	virtual void enter(entity_type *) = 0;

	virtual void execute(entity_type *) = 0;

	virtual void exit(entity_type *) = 0;

};
#endif // !__ZEEK_STATE__H
