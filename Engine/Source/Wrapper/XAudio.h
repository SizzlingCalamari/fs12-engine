#ifndef XAUDIO_H
#define XAUDIO_H


class XAudio
{
	static XAudio *GetInstance();

	IXAudio2 *GetDevice() { return XAudioDevice; }
	HRESULT InitXAudioDevice(XAudio* AudioDevice);


private:
	IXAudio2* XAudioDevice;
};

#endif XAUDIO_H