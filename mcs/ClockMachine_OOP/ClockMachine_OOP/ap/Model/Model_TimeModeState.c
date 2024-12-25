#include "Model_TimeModeState.h"

uint8_t TimeModeStateData;

uint8_t Model_getTimeModeData()
{
	return TimeModeStateData;
}

void Model_setTimeModeData(uint8_t state)
{
	TimeModeStateData = state;
}