#include <stdlib.h>
#include <stdio.h>

int set_parameters(char** argv)
{
	FILE* params;
	params = fopen("./parameters.h", "w");
	fprintf(params, "#define IN_SAMPLERATE %d;\n", atoi(argv[1]));
	fprintf(params, "#define IN_BITSPERSAMPLE 16\n");
	fprintf(params, "#define IN_NUMCHANNELS 1\n");
	fclose(params);

	return 0;
}

int main(int argc, char** argv)
{
	set_parameters(argv);

	return 0;
}
