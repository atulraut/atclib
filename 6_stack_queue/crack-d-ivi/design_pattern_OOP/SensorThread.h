#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H
#include "O2Sensor.h"
#include "GasData.h"
/*
  …
  initial declaratons stuff above
  …
*/
typedef struct SensorThread SensorThread;
struct SensorThread {
  struct GasDataQueue* itsGasDataQueue;
  // struct HeSensor itsHeSensor;
  //  struct N2Sensor itsN2Sensor;
  struct O2Sensor itsO2Sensor;
};
/* Operations */
void SensorThread_updateData(SensorThread* const me);

#endif
