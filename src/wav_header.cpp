/* 2026-06-05
 * writing a wav header and rectangle function */


#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define FILENAME "../output.wav"

int WriteHeaderToFile(FILE* file);

const int ChunkID = /*0x52494646;*/0x46464952; //0; 4 bytes, "RIFF" (ASCII)
const int Format = /*0x57415645;/*/0x45564157; //(8; 4 bytes, "WAVE" (ASCII)
const int Subchunk1ID = /* 0x666d7420 ;*/ 0x20746d66; //12; 4 bytes "fmt " (ASCII)
const int Subchunk1Size = 16; //16; 4 bytes, PCM -> 16
const short int AudioFormat = 1; //20; 2 bytes, PCM = 1
const short int NumChannels = 1; //22; 2 bytes - should be user inputable
const int SampleRate = 48000; //24; 4 bytes - should be user inputable
const int ByteRate = SampleRate * NumChannels; //28; 4 bytes
const short int BitsPerSample = 16; //34; 2 bytes, should be user inputable
const short int BlockAlign = NumChannels * (BitsPerSample/8); //32; 2 bytes
const int Subchunk2ID = /*0x64617461;*/ 0x61746164; //36; 4 bytes, "data" (ASCII)
			      
const float LengthSeconds = 0.001; //Not Part of WAV-header, should be inputable.			
const int NumSamples = SampleRate * LengthSeconds;

const int Subchunk2Size = NumSamples * NumChannels * (BitsPerSample/8); //40; 4 bytes -- REMEMBER TO SET LATER IF NEEDED
const int ChunkSize = 36 + Subchunk2Size; //4; 4 bytes

//not part of wav header!
int FrequencyHertz = 1000;
int SamplesPerWaveCycle = SampleRate/FrequencyHertz;
int SamplesPerHalfWaveCycle = SamplesPerWaveCycle/2;
//printf("whole: %d, half: %d", SamplesPerWaveCycle, SamplesPerHalfWaveCycle);

typedef struct
{
	int ChunkID; // = ChunkID;
	int ChunkSize; // = ChunkSize;
	int Format; // = Format;
	int Subchunk1ID; //= Subchunk1ID;
	int Subchunk1Size; // = Subchunk1Size;
	short int AudioFormat; // = AudioFormat;
	short int NumChannels;// = NumChannels; 
	int SampleRate;// = SampleRate;
	int ByteRate;// = ByteRate;
	short BlockAlign;// = BlockAlign;
	short BitsPerSample;// = BitsPerSample;
	int Subchunk2ID;// = Subchunk2ID;
	int Subchunk2Size;// = Subchunk2Size;
} WavHeader;

WavHeader header = 
	{
		ChunkID,
		ChunkSize,
		Format,
		Subchunk1ID,
		Subchunk1Size,
		AudioFormat,
		NumChannels,
		SampleRate,
		ByteRate,
		BlockAlign,
		BitsPerSample,
		Subchunk2ID,
		Subchunk2Size
	};


int main(int argc, char** argv)
{
	//offset; size, content, comments -- BEWARE OF ORDER, SEE OFFSET!
	


	//create file:
	FILE* file;
	file = fopen(FILENAME, "wb");
	
	//writing struct to file
	WriteHeaderToFile(file);
	fclose(file);

	//writing the function to the file
	file = fopen(FILENAME, "ab");
	short int sample = 0; //two bytes (See above!)
	for(int i = 0; i < NumSamples; i++)
	{
		sample = (int)(0x7FFF * 0.8) * (i % SamplesPerWaveCycle + 1 <= SamplesPerHalfWaveCycle)
			+ (int)(0x7FFF * -0.8) * (i % SamplesPerWaveCycle + 1 > SamplesPerHalfWaveCycle);
		fwrite(&sample,	sizeof(sample), 1, file); 
	}

	//closing file
	//fprintf(file, "%c", EOF);
	fclose(file);

	return 0;
}

int WriteHeaderToFile(FILE* file)
{
	fwrite(&header, sizeof(WavHeader), 1, file);
	return 0;
}
