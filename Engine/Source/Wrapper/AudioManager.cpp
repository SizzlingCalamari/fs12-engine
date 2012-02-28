#include "AudioManager.h"
#include "Input.h"

AudioManager::AudioManager()
{
	dataBuffer				= NULL;
	XAudioDevice			= NULL;
	XAudioMasterVoice		= NULL;
	XAudioSourceVoice		= NULL;

	maxAllocSize			= AUDIO_LIB_SIZE*1024*1024; // amount of memory to allocate for audio
	allocOffset				= 0;
	elapsedTime				= 0.0f;
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
	if(!XAudioDevice)
	{
		if(XAudio2Create(&XAudioDevice, XAUDIO2_DEBUG_ENGINE, XAUDIO2_DEFAULT_PROCESSOR)) // create the audio device ??DEBUG?? will look into that
			MessageBox(0,"FAILED TO CREATE AUDIO DEVICE",0,0);
	}
	if(!XAudioMasterVoice)
	{
		if(XAudioDevice->CreateMasteringVoice(&XAudioMasterVoice)) // Master Voice serves as a mixing master for all subvoices
			MessageBox(0,"FAILED TO CREATE AUDIO MASTER VOICE",0,0);
	}
	if(!dataBuffer)
		dataBuffer = (BYTE*)malloc(maxAllocSize); // allocate enough memory to allocate our audio library
}

int AudioManager::LoadSound(char *_filename)
{
	map<char*, unsigned int>::iterator it;
	
	it = soundMap.find(_filename);

	if (it == soundMap.end())
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
			if(!LoadWav(_filename))
				return -1;

		//should probably load .ogg's for compressed audio

		return sounds.size()-1;
	}else
		return it->second;

	return false;
}

bool AudioManager::LoadWav(char *_filename)
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
	if(XAudioDevice->CreateSourceVoice(&XAudioSourceVoice, (WAVEFORMATEX*)&sounds[i].wfx,XAUDIO2_VOICE_USEFILTER))
		MessageBox(0,"FAILED TO CREATE SOURCE VOICE","FAILED TO PLAY SOUND",0);

	filterParams.Frequency = 0.1f;
	filterParams.OneOverQ = 0.1f;
    filterParams.Type = LowPassFilter;

	XAudioSourceVoice->SetFilterParameters(&filterParams, XAUDIO2_COMMIT_NOW);

	//should check to see if the sound is already playing beffor queueing it up
	if(XAudioSourceVoice->SubmitSourceBuffer(sounds[i].buffer))
		MessageBox(0,"FAILED TO SUBMIT BUFFER","FAILED TO PLAY SOUND",0);

	//should check if it's already playing before starting it again
	if(XAudioSourceVoice->Start(0, XAUDIO2_COMMIT_NOW))
		MessageBox(0,"FAILED TO START SOURCE VOICE","FAILED TO PLAY SOUND",0);
}

void AudioManager::UpdateFilters(float dt)
{
	if(XAudioSourceVoice)
	{
		elapsedTime+=dt*0.25f;

		filterParams.Frequency += ((float)Input::GetInstance()->GetRelativeCursorPosition().y)*0.001f;
		if(filterParams.Frequency <= 0.0f)
			filterParams.Frequency = 0.01f;
		else if(filterParams.Frequency > XAUDIO2_MAX_FILTER_FREQUENCY)
			filterParams.Frequency = XAUDIO2_MAX_FILTER_FREQUENCY;
		filterParams.OneOverQ = 0.5f;
		filterParams.Type = LowPassFilter;
		XAudioSourceVoice->SetFilterParameters(&filterParams, XAUDIO2_COMMIT_NOW);
	}
}

void AudioManager::Shutdown()
{
	if(XAudioSourceVoice)
	{
		XAudioSourceVoice->Stop(0);
		XAudioSourceVoice->DestroyVoice();
		XAudioSourceVoice = NULL;
	}

	for(unsigned int i = 0; i<sounds.size(); ++i)
		delete sounds[i].buffer;

	if(dataBuffer)
	{
		free(dataBuffer);
		dataBuffer = NULL;
	}
	if(XAudioMasterVoice)
	{
		XAudioMasterVoice->DestroyVoice();
		XAudioMasterVoice = NULL;
	}
	if(XAudioDevice)
	{
		XAudioDevice->Release();
		XAudioDevice = NULL;

		CoUninitialize();
	}
}