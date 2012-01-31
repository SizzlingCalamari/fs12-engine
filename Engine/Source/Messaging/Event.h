#pragma once

#include <string>
using std::string;

enum EVENTID
{

};

class Event
{
private:
	EVENTID			eventID;
	string			eventName;
	void*			param;
public:
	Event(string _eventName, EVENTID _eventID, void* _param = NULL)
	{
		eventName = _eventName;
		eventID = _eventID;
		param  = _param;
	}

	~Event() {}

	inline EVENTID  GetEventID(void)	{	return eventID; }
	inline void*	GetParam(void)		{	return param; }
};