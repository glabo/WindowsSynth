#include "WaveGenerator.h"
#include <stdio.h>
#include <string>

// copied from https://blog.demofox.org/2012/05/14/diy-synthesizer-chapter-1-sound-output/

#define CLAMP(value,min,max) {if(value > max) { value = max; }}

//–2,147,483,648 to 2,147,483,647
void ConvertFloatToAudioSample(float fFloat, int32_t& nOut)
{
	double dDouble = (double)fFloat;
	dDouble *= 2147483647.0;
	CLAMP(dDouble, -2147483648.0, 2147483647.0);
	nOut = (int32_t)dDouble;
}

bool WaveGenerator::WriteWaveFile(const char* szFileName, float* pRawData, int32_t nNumSamples, int16_t nNumChannels, int32_t nSampleRate, bool bNormalizeData)
{
	float* pOrigRawData = pRawData;

    //open the file if we can
	FILE* File;
	fopen_s(&File, szFileName, "w+b");
    if (!File)
    {
        return false;
    }

	//normalize the audio data if we should
	if (bNormalizeData)
	{
		pRawData = new float[nNumSamples];
		memcpy(pRawData, pOrigRawData, sizeof(float) * nNumSamples);
		NormalizeAudioData(pRawData, nNumSamples);
	}

    //calculate bits per sample and the data size
    int32_t nBitsPerSample = sizeof(int32_t) * 8;
    int nDataSize = nNumSamples * sizeof(int32_t);

    SMinimalWaveFileHeader waveHeader;

    //fill out the main chunk
    memcpy(waveHeader.m_szChunkID, "RIFF", 4);
    waveHeader.m_nChunkSize = nDataSize + 36;
    memcpy(waveHeader.m_szFormat, "WAVE", 4);

    //fill out sub chunk 1 "fmt "
    memcpy(waveHeader.m_szSubChunk1ID, "fmt ", 4);
    waveHeader.m_nSubChunk1Size = 16;
    waveHeader.m_nAudioFormat = 1;
    waveHeader.m_nNumChannels = nNumChannels;
    waveHeader.m_nSampleRate = nSampleRate;
    waveHeader.m_nByteRate = nSampleRate * nNumChannels * nBitsPerSample / 8;
    waveHeader.m_nBlockAlign = nNumChannels * nBitsPerSample / 8;
    waveHeader.m_nBitsPerSample = nBitsPerSample;

    //fill out sub chunk 2 "data"
    memcpy(waveHeader.m_szSubChunk2ID, "data", 4);
    waveHeader.m_nSubChunk2Size = nDataSize;

    //write the header
    fwrite(&waveHeader, sizeof(SMinimalWaveFileHeader), 1, File);

    //write the wave data itself, converting it from float to the type specified
    int32_t* pData = new int32_t[nNumSamples];
	for (int nIndex = 0; nIndex < nNumSamples; ++nIndex)
		ConvertFloatToAudioSample(pRawData[nIndex], pData[nIndex]);
	fwrite(pData, nDataSize, 1, File);
	delete[] pData;

	//if we normalized the data-, free the buffer we allocated
	if (bNormalizeData)
	{
		delete[] pRawData;
	}

	//close the file and return success
	fclose(File);
	return true;
}


float WaveGenerator::GenerateSineWave(float& fPhase, float fFrequency, float fSampleRate)
{
	fPhase += 2 * (float)M_PI * fFrequency / fSampleRate;

	while (fPhase >= 2 * (float)M_PI)
		fPhase -= 2 * (float)M_PI;

	while (fPhase < 0)
		fPhase += 2 * (float)M_PI;

	return sin(fPhase);
}

void WaveGenerator::PlayTone(WAVE_TYPE type, float freq)
{
	int numSeconds = 2;
	int numChannels = 2; // stereo
	if (type != SINE) {
		return;
	}

	//make our buffer to hold the samples
	int numSamples = SAMPLE_RATE * 2 * numSeconds;
	float* pData = new float[numSamples];

	//the phase of our oscilator, we don't really need to reset it between wave files
	//it just needs to stay continuous within a wave file
	float fPhase = 0;

	//make a sine wave
	for (int nIndex = 0; nIndex < numSamples; ++nIndex)
	{
		pData[nIndex] = GenerateSineWave(fPhase, freq, (float)SAMPLE_RATE);
	}
	
	WriteWaveFile("out.wav", pData, numSamples, numChannels, SAMPLE_RATE, true);
}

void WaveGenerator::NormalizeAudioData(float* pData, int nNumSamples)
{
	//figure out what the maximum and minimum value is
	float fMaxValue = pData[0];
	float fMinValue = pData[0];
	for (int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		if (pData[nIndex] > fMaxValue)
		{
			fMaxValue = pData[nIndex];
		}

		if (pData[nIndex] < fMinValue)
		{
			fMinValue = pData[nIndex];
		}
	}

	//calculate the center and the height
	float fCenter = (fMinValue + fMaxValue) / 2.0f;
	float fHeight = fMaxValue - fMinValue;

	//center and normalize the samples
	for (int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		//center the samples
		pData[nIndex] -= fCenter;

		//normalize the samples
		pData[nIndex] /= fHeight;
	}
}