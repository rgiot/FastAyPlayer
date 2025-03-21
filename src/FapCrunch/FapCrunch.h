#ifndef __FAP_CRUNCH_H__
#define __FAP_CRUNCH_H__

#include "YmData.h"


static uint8_t regOrder[] = { 0, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
#define NR_FAP_REGISTERS sizeof(regOrder)

bool WriteFile(char* fileName,
	YmData& ymData,
	uint8_t* crunchData[NR_FAP_REGISTERS],
	int crunchSize[NR_FAP_REGISTERS],
	int loopOffset[NR_FAP_REGISTERS],
	uint8_t registersToPlay);




void CrunchSong(YmData& ymData,
	uint8_t* crunchData[NR_FAP_REGISTERS],
	int crunchSize[NR_FAP_REGISTERS],
	int loopOffset[NR_FAP_REGISTERS]);
#endif