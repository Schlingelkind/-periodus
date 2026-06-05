/* 2026-06-05
 * reading/writing a wav header */


#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
{
	//offset; size, content, comments -- BEWARE OF ORDER, SEE OFFSET!
	
	const int ChunkID = 0x46464952; //0; 4 bytes, "RIFF" (ASCII)
	const int Format = 0x45564157; //(8; 4 bytes, "WAVE" (ASCII)
	const int Subchunk1ID = 0x20746d66; //12; 4 bytes "fmt " (ASCII)
	const int Subchunk1Size = 16; //16; 4 bytes, PCM -> 16
	const short int AudioFormat = 1; //20; 2 bytes, PCM = 1
	const short int NumChannels = 1; //22; 2 bytes - should be user inputable
	const int SampleRate = 48000; //24; 4 bytes - should be user inputable
	const int ByteRate = SampleRate * NumChannels; //28; 4 bytes
	const short int BitsPerSample = 16; //34; 2 bytes, should be user inputable
	const short int BlockAlign = NumChannels * BitsPerSample/8; //32; 2 bytes
	const int Subchunk2ID = 0x61746164; //36; 4 bytes, "data" (ASCII)
				      
	const int LengthSeconds = 10; //Not Part of WAV-header, should be inputable.			
	const int NumSamples = SampleRate * LengthSeconds;

	const int Subchunk2Size = NumSamples * NumChannels * BitsPerSample/8; //40; 4 bytes -- REMEMBER TO SET LATER IF NEEDED
	const int ChunkSize = 36 + Subchunk2Size; //4; 4 bytes

	//not part of wav header!
	int FrequencyHertz = 1000;
	int SamplesPerHalfWaveCycle = SampleRate/FrequencyHertz;

	//create file:
	FILE* file;
	file = fopen("../output.wav", "wb");
	

	//initialize file
	fwrite(&ChunkID, sizeof(ChunkID), 1, file);
	fclose(file);
	file = fopen("../output.wav", "ab");


	//append rest of header
	fwrite(&ChunkSize, sizeof(ChunkSize), 1, file);
	fwrite(&Format, sizeof(Format), 1, file);
	fwrite(&Subchunk1ID, sizeof(Subchunk1ID), 1, file);
	fwrite(&Subchunk1Size, sizeof(Subchunk1Size), 1, file);
	fwrite(&AudioFormat, sizeof(AudioFormat), 1, file);
	fwrite(&NumChannels, sizeof(NumChannels), 1, file);
	fwrite(&SampleRate, sizeof(SampleRate), 1, file);
	fwrite(&ByteRate, sizeof(ByteRate), 1, file);
	fwrite(&BlockAlign, sizeof(BlockAlign), 1, file);
	fwrite(&Subchunk2ID, sizeof(Subchunk2ID), 1, file);
	fwrite(&Subchunk2Size, sizeof(Subchunk2Size), 1, file);
	
	//writing the function to the file


	//closing file
	fprintf(file, "%c", EOF);
	fclose(file);

	return 0;
}
