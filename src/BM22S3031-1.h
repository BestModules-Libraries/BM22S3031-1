/*****************************************************************
File:        BM22S3031-1.h
Author:      BESTMODULES
Description: Define classes and required variables
History:     None
V1.0.1  --Initial version; 2023-03-20; Arduino IDE : v1.8.19
******************************************************************/
#ifndef _BM22S3031_1_H_
#define _BM22S3031_1_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

#define BAUDRATE 9600
#define AUTO 0x08
#define PASSIVE 0x00
#define HIGH_LEVEL 0x08
#define LOW_LEVEL 0x00

#define CHECK_OK 0
#define CHECK_ERROR 1
#define TIMEOUT_ERROR 2

class BM22S3031_1
{
public:
  BM22S3031_1(uint8_t statusPin, HardwareSerial *theSerial = &Serial);
  BM22S3031_1(uint8_t statusPin, uint8_t rxPin, uint8_t txPin);
  void begin();
  void preheatCountdown();
  uint8_t getSTATUS();
  uint8_t getWorkStatus();
  uint16_t readGasValue();
  uint16_t readADValue();
  uint16_t readRefValue();
  uint8_t requestInfoPackage(uint8_t array[]);
  bool isInfoAvailable();
  void readInfoPackage(uint8_t array[]);
  uint8_t resetModule();
  uint8_t restoreDefault();

  uint16_t getFWVer();
  uint8_t getProDate(uint8_t array[]);
  bool isAutoTx();
  uint8_t getStatusPinActiveMode();
  uint16_t getAlarmThreshold();
  uint16_t getExitAlarmThreshold();
  uint8_t getCALTime();

  uint8_t setAutoTx(uint8_t autoTx = AUTO);
  uint8_t setStatusPinActiveMode(uint8_t statusMode = HIGH_LEVEL);
  uint8_t setAlarmThreshold(uint16_t alarmThreshold = 4500);
  uint8_t setExitAlarmThreshold(uint16_t exitAlarmThreshold = 1500);
  uint8_t setCALTime(uint8_t CALtime = 120);
  uint8_t calibrateModule();
  void calibrateCountdown();

private:
  uint8_t _statusPin, _rxPin, _txPin;
  uint8_t _recBuf[34] = {0}; // Array for storing received data
  uint8_t _calTime = 120;
  const uint8_t _preheat = 1, _calibration = 0, _preheatTime = 180;

  void clear_UART_FIFO();
  void writeBytes(uint8_t wbuf[], uint8_t wlen);
  uint8_t readBytes(uint8_t rbuf[], uint8_t rlen, uint16_t timeout = 20);
  void countdown(uint8_t type = 1);
  HardwareSerial *_hardSerial = NULL;
  SoftwareSerial *_softSerial = NULL;
};

#endif
