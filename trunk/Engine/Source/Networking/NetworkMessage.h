#pragma once

enum IO_TYPE
{
	SIMPLE_MESSAGE
};

class NetworkMessage
{
public:
	NetworkMessage();
	~NetworkMessage();
private:
	IO_TYPE msgType;
	int dataBegin;
	int dataEnd;
	char *buffer;
	void Write(const char* data, int offset, int length);
	int Read(const char* data, int offset, int length);
};