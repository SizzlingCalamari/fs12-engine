#include "XAudio.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

XAudio::XAudio()
{

}

XAudio::~XAudio()
{
	
}

HRESULT XAudio::InitXAudioDevice(XAudio* AudioDevice)
{
	HRESULT hr;
	if(FAILED(hr = XAudio2Create(&m_pXAudioDevice, XAUDIO2_DEBUG_ENGINE, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;

	if(FAILED(hr = m_pXAudioDevice->CreateMasteringVoice(&m_pXAudioMasterVoice)))
		return hr;

	return hr;
}

XAudio* XAudio::GetInstance()
{
	static XAudio instance;
	return &instance;
}

HRESULT XAudio::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
        return HRESULT_FROM_WIN32( GetLastError() );

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
            hr = HRESULT_FROM_WIN32( GetLastError() );

        if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
            hr = HRESULT_FROM_WIN32( GetLastError() );

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
                hr = HRESULT_FROM_WIN32( GetLastError() );
            break;

        default:
            if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
            return HRESULT_FROM_WIN32( GetLastError() );            
        }

        dwOffset += sizeof(DWORD) * 2;
        
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;
        
        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    
    return S_OK;
}

HRESULT XAudio::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
        return HRESULT_FROM_WIN32( GetLastError() );
    DWORD dwRead;
    if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
        hr = HRESULT_FROM_WIN32( GetLastError() );
    return hr;
}

HRESULT XAudio::OpenFile(XAUDIO2_BUFFER* buffer, TCHAR* filePath)
{
	HRESULT hr = S_OK;
	//Declare the "WAVEFORMATEXTENSIBLE" structure
	WAVEFORMATEXTENSIBLE wfx = {0};

	//Open the file
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if(INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if(INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	//Locate the RIFF chunk in the audio file, and check the file type
	DWORD dwChunkSize;
	DWORD dwChunkPosition;

	//Check the filetype, should be FOURCCWAVE or 'XMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if(filetype != fourccWAVE)
		return S_FALSE;

	//Locate tge 'fmt' chunk, and copy its contents into a WAVEFORMATEXTENSIBLE structure (wfx)
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//Locate tge 'data' chunk, and read its contents into a buffer
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	//Populate the passed in buffer
	buffer->AudioBytes = dwChunkSize;	//Buffer containing audio data
	buffer->pAudioData = pDataBuffer;
	buffer->Flags = XAUDIO2_END_OF_STREAM;

	if(FAILED(hr = m_pXAudioDevice->CreateSourceVoice(&m_pXAudioSourceVoice, (WAVEFORMATEX*)&wfx)))
		return hr;

	if(FAILED(hr = m_pXAudioSourceVoice->SubmitSourceBuffer(buffer)))
		return hr;

	return hr;
}

HRESULT XAudio::PlaySoundA()
{
	HRESULT hr = S_OK;
	if(FAILED(hr = m_pXAudioSourceVoice->Start(0, XAUDIO2_COMMIT_NOW)))
		return hr;

	return hr;
}

HRESULT XAudio::StopSound()
{
	HRESULT hr = S_OK;
	if(FAILED(hr = m_pXAudioSourceVoice->Stop(0)))
		return hr;

	return hr;
}

void XAudio::Shutdown()
{
	if(m_pXAudioSourceVoice)
	{
		m_pXAudioSourceVoice->Stop(0);
		m_pXAudioSourceVoice->DestroyVoice();
		m_pXAudioSourceVoice = NULL;
	}
	if(m_pXAudioMasterVoice)
	{
		m_pXAudioMasterVoice->DestroyVoice();
		m_pXAudioMasterVoice = NULL;
	}
	if(m_pXAudioDevice)
	{
		SAFE_RELEASE(m_pXAudioDevice);
		CoUninitialize();
	}
}