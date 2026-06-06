#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wav_header.h"
using namespace std;

#define PI 3.141592657 //set pi to pi value in DOOM! :P
#define MAX_AMPLITUDE 0x7FFF

int generate_square();
int generate_sine();

int main(int argc, char** argv)
{

	//generate_square();

	//generate sine
	generate_sine();

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
	float amplitude = 0.8;
	for(int i = 0; i < NumSamples; i++)
	{
		sample = (int)( MAX_AMPLITUDE * amplitude) * (i % SamplesPerWaveCycle + 1 <= SamplesPerHalfWaveCycle)
			+ (int)( MAX_AMPLITUDE * -1 * amplitude) * (i % SamplesPerWaveCycle + 1 > SamplesPerHalfWaveCycle);
		fwrite(&sample,	sizeof(sample), 1, file); 
	}
	fclose(file);

	printf("Wrote Function to File \n");

	return 0;
}

int generate_sine()
{
	//intitializing file
	FILE* file;
	file = fopen("../output/sine.wav", "wb");
	WriteHeaderToFile(file);
	fclose(file);

	printf("Wrote Header to File\n");
	
	//writing the function to the file	
	file = fopen("../output/sine.wav", "ab");
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

	printf("Wrote Function to File \n");

	return 0;
}
