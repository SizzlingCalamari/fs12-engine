#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <XAudio2.h>
#include <fstream>
#include <string>

#include <vector>
#include <map>

using namespace std;

#define AUDIO_LIB_SIZE 64 //amount of memory allocated for loading sounds ( in Megabytes )

struct Sound
{
	XAUDIO2_BUFFER *buffer;
	WAVEFORMATEXTENSIBLE wfx;

	// will probably require other information for this specific sound
	// like volume, pan, priority

	Sound()
	{
		ZeroMemory(&buffer, sizeof(XAUDIO2_BUFFER));
		ZeroMemory((void*)&wfx, sizeof(WAVEFORMATEXTENSIBLE));
	}
};

class AudioManager
{
public:
	static AudioManager *GetInstance();

	bool LoadSound(const char *_filename);
	bool LoadWav(const char *_filename);

	void PlaySound(unsigned int i);

	void Init();
	void Shutdown();
protected:
	AudioManager();
	~AudioManager();
	AudioManager(AudioManager &ref);
	AudioManager &operator=(AudioManager &ref);

private:
	vector<Sound> sounds;

	BYTE* dataBuffer;
	unsigned int allocOffset;

	unsigned int maxAllocSize;
	unsigned int currAllocSize;

	IXAudio2* m_pXAudioDevice;
	IXAudio2MasteringVoice* m_pXAudioMasterVoice;
	IXAudio2SourceVoice* m_pXAudioSourceVoice;
};

#endif