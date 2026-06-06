#include <stdlib.h>
#include <stdio.h>

int set_parameters(char** argv)
{
	FILE* params;
	params = fopen("./parameters.h", "w");
	fprintf(params, "in_SampleRate = %d;\n", atoi(argv[1]));
	fclose(params);

	return 0;
}

int main(int argc, char** argv)
{
	set_parameters(argv);

	return 0;
}
