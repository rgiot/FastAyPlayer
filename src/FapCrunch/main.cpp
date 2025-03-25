#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include "Fap.h"



///////////////////////////////////////////////////////////////////////////////////
//
// Entry Point
//
///////////////////////////////////////////////////////////////////////////////////

void PrintUsageAndExit()
{
	printf("Invalid number of arguments.\nUsage: FapCrunch <Source YM file> <Destination Hicks file> [-1|-2]\n");
	exit(-1);
}

int main(int argc, char* argv[])
{
	FapConfig config;

	if (argc < 3 || argc > 4)
	{
		PrintUsageAndExit();
	}

	if (argc == 4)
	{
		if (strlen(argv[3]) != 2 || argv[3][0] != '-')
		{
			PrintUsageAndExit();
		}
		switch (argv[3][1])
		{
		case '1':
			config.threshold = 0.005f;
			break;

		case '2':
			config.threshold = 0.01f;
			break;

		case '3':
			config.threshold = 0.015f;
			break;

		default:
			PrintUsageAndExit();
		}
	}

	config.srcFile = argv[1];
	config.dstFile = argv[2];

	Fap fap = config.instantiate();
	FapResult res = fap.handle();

	if (res.code == FapResultCode::CannotLoadInputFile) {
		printf("Cannot load file %s\n", config.srcFile);
		return -1;
	}
	
	if (config.print) {printf("%s", res.payload.repr().c_str());}


	else if (res.code != FapResultCode::Ok) {
		printf("Error while write result file\n");
		abort();
	}






	return 0;
}
