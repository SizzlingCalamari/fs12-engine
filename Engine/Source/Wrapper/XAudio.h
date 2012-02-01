#ifndef XAUDIO_H
#define XAUDIO_H

#include <XAudio2.h>
#include <windows.h>
#include <iostream>
using namespace std;

class XAudio
{
public:
	static XAudio* GetInstance();
	void Shutdown();

	IXAudio2* GetDevice() { return m_pXAudioDevice; }
	IXAudio2MasteringVoice* GetMasteringVoice() { return m_pXAudioMasterVoice; }
	IXAudio2SourceVoice* GetSourceVoice() { return m_pXAudioSourceVoice; }

	HRESULT InitXAudioDevice(XAudio* AudioDevice);

	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);

	HRESULT OpenFile(XAUDIO2_BUFFER* buffer, TCHAR* FilePath);

	HRESULT PlaySoundA();
	HRESULT StopSound();

protected:
	XAudio();
	~XAudio();
	XAudio(XAudio &ref);
	XAudio &operator=(XAudio &ref);

private:
	IXAudio2* m_pXAudioDevice;
	IXAudio2MasteringVoice* m_pXAudioMasterVoice;
	IXAudio2SourceVoice* m_pXAudioSourceVoice;
};

#endif