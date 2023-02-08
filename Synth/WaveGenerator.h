#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>
#include "WaveTypes.h"
#include "AudioConstants.h"

class WaveGenerator
{
private:
	struct SMinimalWaveFileHeader
	{
		//the main chunk
		unsigned char m_szChunkID[4];
		uint32_t m_nChunkSize;
		unsigned char m_szFormat[4];

		//sub chunk 1 "fmt "
		unsigned char m_szSubChunk1ID[4];
		uint32_t m_nSubChunk1Size;
		uint16_t m_nAudioFormat;
		uint16_t m_nNumChannels;
		uint32_t m_nSampleRate;
		uint32_t m_nByteRate;
		uint16_t m_nBlockAlign;
		uint16_t m_nBitsPerSample;

		//sub chunk 2 "data"
		unsigned char m_szSubChunk2ID[4];
		uint32_t m_nSubChunk2Size;

		//then comes the data!
	};
	void NormalizeAudioData(float* pData, int nNumSamples);
public:
	float GenerateSineWave(float& fPhase, float fFrequency, float fSampleRate);
	bool WriteWaveFile(const char* szFileName, float* pRawData, int32_t nNumSamples, int16_t nNumChannels, int32_t nSampleRate, bool bNormalizeData);
	void PlayTone(WAVE_TYPE type, float freq);
};

