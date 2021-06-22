#ifndef __TRACKADDICT_H
#define __TRACKADDICT_H

#include <bluefruit.h>

#include "TrackAddictPidMap.h"

class TrackAddictBleCanHandler {
public:
  virtual ~TrackAddictBleCanHandler() {}

  virtual void allowAllPids(uint16_t updateIntervalMs);
  virtual void denyAllPids();
  virtual void allowPid(uint32_t pid, uint16_t updateIntervalMs);
};

class TrackAddictBleAgent {
public:
  TrackAddictBleAgent();

  // Seems like the length limit for 'bluetoothName' is 19 visible characters.
  void setUp(const char *bluetoothName, TrackAddictBleCanHandler *handler);

  void startAdvertising();

  // Returns true on success, false on failure.
  bool waitForConnection(uint32_t timeoutMs);

  bool isConnected() const;

  void sendCanData(uint32_t pid, const uint8_t *data, uint8_t len);

private:
  // BLEService docs: https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/bleservice
  // BLECharacteristic docs: https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/blecharacteristic

  BLEService _service;

  // TrackAddict uses two BLE characteristics:
  // 1) 0x02 to request which PIDs to send, and how frequently
  // 2) 0x01 to be notified of data received for those PIDs
  BLECharacteristic _pidRequestsCharacteristic;
  BLECharacteristic _canBusDataCharacteristic;
};

extern TrackAddictBleAgent TrackAddictBle;

#endif  // __TRACKADDICT_H
