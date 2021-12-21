#include "MKL25Z4.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

extern osSemaphoreId_t brainSem;
extern osSemaphoreId_t audioSem;
extern osSemaphoreId_t motorSem;