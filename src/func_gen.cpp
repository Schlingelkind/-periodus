#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define PI 3.141592657 //set pi to pi value in DOOM! :P
#define MAX_AMPLITUDE 0x7FFF

int WriteHeaderToFile(FILE* file, char** argv);
int generate_square_file(char** argv);
int generate_sine_file(char** argv);
int generate_saw_file(char** argv);

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Usage: func_gen Sample-Rate (number) Bits-Per-Sample (number, must be multiple of 8) length(seconds) (number) frequency (number, must not be bigger than nyquist(half sample rate))\nWARNING: There is no bad input correction/catch.");
	}

	//generate functions
	generate_sine_file(argv);
	generate_square_file(argv);
	generate_saw_file(argv);


	return 0;
}

int generate_square_file(char** argv)
{
	//intitializing file
	FILE* file;
	file = fopen("../output/square.wav", "wb");
	WriteHeaderToFile(file, argv);
	fclose(file);

	printf("Wrote Header to File\n");
	
	//writing the function to the file	
	file = fopen("../output/square.wav", "ab");
	short int sample = 0; //two bytes (See above!)
	float amplitude = 0.8;
	for(int i = 0; i < NumSamples; i++)
	{
		sample = (int)( MAX_AMPLITUDE * amplitude) * (i % SamplesPerWaveCycle + 1 <= SamplesPerHalfWaveCycle)
			+ (int)( MAX_AMPLITUDE * -1 * amplitude) * (i % SamplesPerWaveCycle + 1 > SamplesPerHalfWaveCycle);
		fwrite(&sample,	sizeof(sample), 1, file); 
	}
	fclose(file);

	printf("Wrote Square to File \n");

	return 0;
}

int generate_sine_file(char** argv)
{
	//intitializing file
	FILE* file;
	file = fopen("../output/sine.wav", "wb");
	WriteHeaderToFile(file, argv);
	fclose(file);

	printf("Wrote Header to File\n");
	
	//writing the function to the file	
	file = fopen("../output/si-ne.wav", "ab");
	short int sample = 0; //two bytes (See above!)
	float phase = 0;
	float amplitude = 0.8;
	for(int i = 0; i < NumSamples; i++)
	{
		phase = 2.0 * PI * ((float)(i%SamplesPerWaveCycle)/(float)SamplesPerWaveCycle);
		sample = (int)( MAX_AMPLITUDE * amplitude * sin(phase));
		//printf("%f\n", sin(phase));
		fwrite(&sample,	sizeof(sample), 1, file); 
	}
	fclose(file);

	printf("Wrote Sine to File\n");

	return 0;
}

int generate_saw_file(char** argv)
{
	//intitializing file
	FILE* file;
	file = fopen("../output/saw.wav", "wb");
	WriteHeaderToFile(file, argv);
	fclose(file);

	printf("Wrote Header to File\n");
	
	//writing the function to the file	
	file = fopen("../output/saw.wav", "ab");
	short int sample = 0; //two bytes (See above!)
	float amplitude = 0.8;
	for(int i = 0; i < NumSamples; i++)
	{
		sample = MAX_AMPLITUDE * amplitude * 2 * ((float)(i%SamplesPerWaveCycle)/(float)SamplesPerWaveCycle) - amplitude * MAX_AMPLITUDE;
		fwrite(&sample,	sizeof(sample), 1, file);
		//printf("%i, sample: %i\n", i%SamplesPerWaveCycle, sample);
	}
	fclose(file);

	printf("Wrote Saw to File \n");

	return 0;
}


int WriteHeaderToFile(FILE* file, char** argv)
{
	//offset; size, content, comments -- BEWARE OF ORDER, SEE OFFSET!
	const int ChunkID = /*0x52494646;*/0x46464952; //0; 4 bytes, "RIFF" (ASCII)
	const int Format = /*0x57415645;/*/0x45564157; //(8; 4 bytes, "WAVE" (ASCII)
	const int Subchunk1ID = /* 0x666d7420 ;*/ 0x20746d66; //12; 4 bytes "fmt " (ASCII)
	const int Subchunk1Size = 16; //16; 4 bytes, PCM -> 16
	const short int AudioFormat = 1; //20; 2 bytes, PCM = 1
	const short int NumChannels = 1; //22; 2 bytes - should be user inputable
	int SampleRate = atoi(argv[1]); //24; 4 bytes - should be user inputable
	short int BitsPerSample = (short int)atoi(argv[2]); //34; 2 bytes, should be user inputable
	const int ByteRate = SampleRate * NumChannels * (BitsPerSample/8); //28; 4 bytes
	const short int BlockAlign = NumChannels * (BitsPerSample/8); //32; 2 bytes
	const int Subchunk2ID = /*0x64617461;*/ 0x61746164; //36; 4 bytes, "data" (ASCII)
			      
	const float LengthSeconds = atof(argv[3]); //Not Part of WAV-header, should be inputable.			
	const int NumSamples = SampleRate * LengthSeconds;

	const int Subchunk2Size = NumSamples * NumChannels * (BitsPerSample/8); //40; 4 bytes -- REMEMBER TO SET LATER IF NEEDED
	const int ChunkSize = 36 + Subchunk2Size; //4; 4 bytes

	//not part of wav header!
	int FrequencyHertz = atoi(argv[4]);
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
	
	fwrite(&header, sizeof(WavHeader), 1, file);
	
	return 0;
}

