#ifndef FCDSensorTMBufferStatusH
#define FCDSensorTMBufferStatusH

#include <platform/basic_types.h>

#define SENSORS_DMA_BUFFERS 4

class CDSensorTMBufferStatus{
	
	public:
	
	uint32_t timestamp_Y2K;
	uint32_t sensorRxPointer[SENSORS_DMA_BUFFERS];
	
	void GetCurrentStatus();

	protected:
	
	private:
	
};
#endif
