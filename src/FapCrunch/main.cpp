#include <stdlib.h>
#include <stdio.h>
#include "FapCrunch.h"
#include <cstring>



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
	float threshold = 0;
	YmData ymData;

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
			threshold = 0.005f;
			break;

		case '2':
			threshold = 0.01f;
			break;

		case '3':
			threshold = 0.015f;
			break;

		default:
			PrintUsageAndExit();
		}
	}

	char* srcFile = argv[1];
	char* dstFile = argv[2];

	if (!ymData.LoadFile(srcFile))
	{
		printf("Cannot load file %s\n", srcFile);
		return -1;
	}

	ymData.Optimize();
	uint8_t nrRegistersToPlay = ymData.CountAndLimitRegChanges(threshold);

	uint8_t* crunchData[NR_FAP_REGISTERS] = { 0 };
	int crunchSize[NR_FAP_REGISTERS] = { 0 };
	int loopOffset[NR_FAP_REGISTERS] = { 0 };

	CrunchSong(ymData, crunchData, crunchSize, loopOffset);

	printf("\nSummary:\n");
	printf("  - Max registers to program: %d\n", nrRegistersToPlay);
	printf("  - Constant Register 12: %s\n", ymData.R12IsConst() ? "YES" : "NO... Damn your musician!");

	bool success = WriteFile(dstFile, ymData, crunchData, crunchSize, loopOffset, nrRegistersToPlay);
	if (!success)
	{
		printf("Error while write result file\n");
		abort();
	}

	if (ymData.R12IsConst())
	{
		int exeTime[] = { 592, 616, 640, 664 };
		printf("  - Play time: %d NOPS\n", exeTime[nrRegistersToPlay - 11]);
		printf("  - Decrunch buffer size: 3144 (#B42)\n");
	}
	else
	{
		int exeTime[] = { 660, 684, 708, 732 };

		printf("  - Play time: %d NOPS\n", exeTime[nrRegistersToPlay - 11]);
		printf("  - Decrunch buffer size: 2888 (#C48)\n");
	}

	return 0;
}
