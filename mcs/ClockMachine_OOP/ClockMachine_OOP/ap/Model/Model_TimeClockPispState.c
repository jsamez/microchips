#include "Model_TimeClockPispState.h"

uint8_t TimeClockStateData;

uint8_t Model_getTimeClockData()
{
	return TimeClockStateData;
}

void Model_setTimeClockData(uint8_t state)
{
	TimeClockStateData = state;
}