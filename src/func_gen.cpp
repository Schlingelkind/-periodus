#include <stdio.h>
#include "wav_header.h"
using namespace std;

int generate_square();

int main()
{
	generate_square();

	return 0;
}

int generate_square()
{
	//intitializing file
	FILE* file;
	file = fopen("../output/square.wav", "wb");
	WriteHeaderToFile(file);
	fclose(file);

	printf("Wrote Header to File\n");
	
	//writing the function to the file	
	file = fopen("../output/square.wav", "ab");
	short int sample = 0; //two bytes (See above!)
	for(int i = 0; i < NumSamples; i++)
	{
		sample = (int)(0x7FFF * 0.8) * (i % SamplesPerWaveCycle + 1 <= SamplesPerHalfWaveCycle)
			+ (int)(0x7FFF * -0.8) * (i % SamplesPerWaveCycle + 1 > SamplesPerHalfWaveCycle);
		fwrite(&sample,	sizeof(sample), 1, file); 
	}
	fclose(file);

	printf("Wrote Function to File \n");

	return 0;
}
