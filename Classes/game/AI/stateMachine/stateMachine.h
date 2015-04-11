#ifndef ZEEK_STATE_MACHINE_H
#define ZEEK_STATE_MACHINE_H

#include "state.h"

template <class entity_type>

class StateMachine
{
public:
		StateMachine(entity_type* owner) :m_pOwner(owner),
			m_pCurrentState(NULL),
			m_pPreviousState(NULL),
			m_pGlobalState(NULL)
		{}

		virtual ~StateMachine(){}

		void setCurrentState(State<entity_type>* s){ m_pCurrentState = s; }
		void setGlobalState(State<entity_type>* s) { m_pGlobalState = s; }
		void setPreviousState(State<entity_type>* s){ m_pPreviousState = s; }

		void  update(float delta)const
		{
			if (m_pGlobalState)   m_pGlobalState->execute(delta,m_pOwner);

			if (m_pCurrentState) m_pCurrentState->execute(delta,m_pOwner);
		}

		void  changeState(State<entity_type>* pNewState)
		{
			assert(pNewState &&
				"<StateMachine::ChangeState>: trying to change to NULL state");

			m_pPreviousState = m_pCurrentState;
			if (m_pCurrentState)
				m_pCurrentState->exit(m_pOwner);

			m_pCurrentState = pNewState;

			m_pCurrentState->enter(m_pOwner);
		}

		void  revertToPreviousState()
		{
			changeState(m_pPreviousState);
		}

		bool  isInState(const State<entity_type>& st)const
		{
			return typeid(*m_pCurrentState) == typeid(st);
		}

		State<entity_type>*  currentState()  const{ return m_pCurrentState; }
		State<entity_type>*  globalState()   const{ return m_pGlobalState; }
		State<entity_type>*  previousState() const{ return m_pPreviousState; }

protected:
	entity_type* m_pOwner;

	State<entity_type>*	m_pCurrentState;

	State<entity_type>* m_pPreviousState;

	State<entity_type>* m_pGlobalState;
};
#endif // !ZEEK_STATE_MACHINE_H
