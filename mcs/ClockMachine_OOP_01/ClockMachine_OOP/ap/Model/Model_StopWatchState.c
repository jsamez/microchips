#include "Model_StopWatchState.h"

uint8_t StopWatchStateData;

uint8_t Model_getStopWatchData()
{
	return StopWatchStateData;
}

void Model_setStopWatchData(uint8_t state)
{
	StopWatchStateData = state;
}