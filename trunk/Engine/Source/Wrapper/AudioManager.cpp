#include "AudioManager.h"

AudioManager::AudioManager()
{
	dataBuffer				= NULL;
	m_pXAudioDevice			= NULL;
	m_pXAudioMasterVoice	= NULL;
	m_pXAudioSourceVoice	= NULL;

	maxAllocSize			= AUDIO_LIB_SIZE*1024*1024; // amount of memory to allocate for audio
	allocOffset				= 0;
}

AudioManager::~AudioManager()
{
}

AudioManager* AudioManager::GetInstance()
{
	static AudioManager instance;
	return &instance;
}

void AudioManager::Init()
{
	if(!m_pXAudioDevice)
	{
		if(XAudio2Create(&m_pXAudioDevice, XAUDIO2_DEBUG_ENGINE, XAUDIO2_DEFAULT_PROCESSOR)) // create the audio device ??DEBUG?? will look into that
			MessageBox(0,"FAILED TO CREATE AUDIO DEVICE",0,0);
	}
	if(!m_pXAudioMasterVoice)
	{
		if(m_pXAudioDevice->CreateMasteringVoice(&m_pXAudioMasterVoice)) // Master Voice serves as a mixing master for all subvoices
			MessageBox(0,"FAILED TO CREATE AUDIO MASTER VOICE",0,0);
	}
	if(!dataBuffer)
		dataBuffer = (BYTE*)malloc(maxAllocSize); // allocate enough memory to allocate our audio library
}

bool AudioManager::LoadSound(const char *_filename)
{
	unsigned int count = 0;
	while(true)
	{
		if(_filename[count] == '.')
		{
			count++;
			break;
		}
		count++;
	}

	if(!strcmp(_filename+count, "wav") || !strcmp(_filename+count, "WAV"))
		return LoadWav(_filename);

	//should probably load .ogg's for compressed audio

	return false;
}

bool AudioManager::LoadWav(const char *_filename)
{
	WAVEFORMATEXTENSIBLE wfx = {0};
	//Open the file
	fstream wavFile;

	wavFile.open(_filename, ios_base::binary | ios_base::in);

	if(!wavFile.good())
	{
		MessageBox(0,_filename,"AUDIO FILE DOES NOT EXIST",0);
		return false;
	}

	DWORD fourCC = 0;
	DWORD size = 0;
	DWORD filetype = 0;

	//read the riff, size and filetype
	wavFile.read((char*)&fourCC, sizeof(DWORD));
	wavFile.read((char*)&size, sizeof(DWORD));
	wavFile.read((char*)&filetype, sizeof(DWORD));

	if(filetype != 'EVAW')
		return false;

	// read the fmt, size and copy its contents into a WAVEFORMATEXTENSIBLE structure (wfx)
	wavFile.read((char*)&fourCC, sizeof(DWORD));
	wavFile.read((char*)&size, sizeof(DWORD));
	wavFile.read((char*)&wfx, size);

	// read the data, size and copy its contents into a WAVEFORMATEXTENSIBLE structure (wfx)
	wavFile.read((char*)&fourCC, sizeof(DWORD));
	wavFile.read((char*)&size, sizeof(DWORD));
	wavFile.read((char*)dataBuffer+allocOffset, size);
	wavFile.close();
	// Create XAUDIO2 buffer with loaded data
	Sound sound;
	sound.buffer = new XAUDIO2_BUFFER();
	sound.buffer->AudioBytes = size;
	sound.buffer->pAudioData = dataBuffer+allocOffset;
	sound.buffer->Flags = XAUDIO2_END_OF_STREAM;
	sound.wfx = wfx;

	allocOffset+=size;

	sounds.push_back(sound);

	return true;
}

void AudioManager::PlaySound(unsigned int i)
{
	//shouldn't create a new source voice it's already created
	if(m_pXAudioDevice->CreateSourceVoice(&m_pXAudioSourceVoice, (WAVEFORMATEX*)&sounds[i].wfx))
		MessageBox(0,"FAILED TO CREATE SOURCE VOICE","FAILED TO PLAY SOUND",0);

	//should check to see if the sound is already playing beffor queueing it up
	if(m_pXAudioSourceVoice->SubmitSourceBuffer(sounds[i].buffer))
		MessageBox(0,"FAILED TO SUBMIT BUFFER","FAILED TO PLAY SOUND",0);

	//should check if it's already playing before starting it again
	if(m_pXAudioSourceVoice->Start(0, XAUDIO2_COMMIT_NOW))
		MessageBox(0,"FAILED TO START SOURCE VOICE","FAILED TO PLAY SOUND",0);
}

void AudioManager::Shutdown()
{
	if(m_pXAudioSourceVoice)
	{
		m_pXAudioSourceVoice->Stop(0);
		m_pXAudioSourceVoice->DestroyVoice();
		m_pXAudioSourceVoice = NULL;
	}

	for(unsigned int i = 0; i<sounds.size(); ++i)
		delete sounds[i].buffer;

	if(dataBuffer)
	{
		free(dataBuffer);
		dataBuffer = NULL;
	}
	if(m_pXAudioMasterVoice)
	{
		m_pXAudioMasterVoice->DestroyVoice();
		m_pXAudioMasterVoice = NULL;
	}
	if(m_pXAudioDevice)
	{
		m_pXAudioDevice->Release();
		m_pXAudioDevice = NULL;

		CoUninitialize();
	}
}