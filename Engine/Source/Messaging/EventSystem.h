#pragma once

#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

#include "Event.h"
#include "Listener.h"

class EventSystem
{
private:
	multimap<string, Listener*>	m_ClientDatabase;

	list<Event>	currentEvents;

	void DispatchEvent(Event* _event);

	EventSystem() {}
	EventSystem(const EventSystem&);
	EventSystem& operator=(const EventSystem&);

	~EventSystem() {}

public:

	static EventSystem* GetInstance(void)
	{
		static EventSystem instance;
		return &instance;
	}

	void Register(EVENTID eventID, Listener* pClient);
	void Unregister(EVENTID eventID, Listener* pClient);
	void SendEvent(EVENTID eventID, void* data);
	void ProcessEvents();
	void ClearEvents();
	void Shutdown();
};