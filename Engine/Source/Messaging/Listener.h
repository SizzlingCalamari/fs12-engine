#pragma once

class Event;

class Listener
{
public:
	Listener(void) {}
	virtual ~Listener(void) {}
	virtual void HandleEvent(Event* pEvent) = 0;
};