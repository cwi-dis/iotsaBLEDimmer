#ifndef _IOTSABLECLIENT_H_
#define _IOTSABLECLIENT_H_
#include "iotsa.h"
#include "iotsaApi.h"
#include <BLEDevice.h>
#include "iotsaBLEClientConnection.h"

typedef std::function<void(BLEAdvertisedDevice&)> BleDeviceFoundCallback;
typedef const char *UUIDString;

class IotsaBLEClientMod : public IotsaMod, public BLEAdvertisedDeviceCallbacks {
public:
  IotsaBLEClientMod(IotsaApplication& app) : IotsaMod(app) {}
  using IotsaMod::IotsaMod;
  void setup();
  void serverSetup();
  void loop();
  String info() { return ""; }
  void findUnknownClients(bool on);
  void setDeviceFoundCallback(BleDeviceFoundCallback _callback);
  void setServiceFilter(const BLEUUID& serviceUUID);
  void setManufacturerFilter(uint16_t manufacturerID);

  // These are all the known devices (known by the application, not by this module)
  std::map<std::string, IotsaBLEClientConnection*> devices;
  IotsaBLEClientConnection* addDevice(std::string id);
  IotsaBLEClientConnection* addDevice(String id);
  IotsaBLEClientConnection* getDevice(std::string id);
  IotsaBLEClientConnection* getDevice(String id);
  void delDevice(std::string id);
  void delDevice(String id);
  bool deviceSeen(std::string id, BLEAdvertisedDevice& device, bool add=false);
  void deviceNotSeen(std::string id);
  void deviceNotSeen(String id);
protected:
  void configLoad();
  void configSave();
  void onResult(BLEAdvertisedDevice advertisedDevice);
  void updateScanning();
  void startScanning();
  void stopScanning();
  static void scanComplete(BLEScanResults results);
  static IotsaBLEClientMod *scanningMod;
  bool scanForUnknownClients = false;
  bool shouldUpdateScan = false;
  BLEScan *scanner = NULL;
  BleDeviceFoundCallback callback = NULL;
  BLEUUID* serviceFilter = NULL;
  uint16_t manufacturerFilter;
  bool hasManufacturerFilter = false;
};

#endif
