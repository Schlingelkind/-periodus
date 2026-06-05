/* 2026-06-05
 * reading/writing a wav header */


#include <stdio.h>

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
	const int ChunkSize = 36 + SubChunk2Size; //4; 4 bytes

	

	return 0;
}
