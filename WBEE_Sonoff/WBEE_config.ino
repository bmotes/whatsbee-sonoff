/*
Nombre V45          Send Config / Recibir MQTT / Recibir web / Enviar web  Descripción
sNodeName               X X x x                     Nombre común del nodo
gNodeType               X x                         Tipo de nodo
sNodeSendConfigInterval X X x x                     Intervalo de envio de los datos de configuración
sNodeSendDataInterval   X x x x                     Intervalo de envio de los datos
sNodeSendDataThreshold  X X x x                     Umbral que se tiene que superar para que envie los datos
sNodeSleepInterval      X X x x                     Intervalo de Sleep (0 es no sleep)
gNodeHardwareVer        X N                         Versión del hardware
gNodeFirmwareVer        X N                         Versión del firmware
gNodeRuntime            X N                         Tiempo desde el encendido (en milisegundos)
gNodeVoltaje            X N                         Tensión de alimentación del nodo.
          
sNodeSyslogHost         X x x x                     Host al que envía el syslog
sNodeSysLogLevel        X X x x                     Nivel de syslog (de 0 a 5)
sNodeSerialLogLevel     X X x x                     Nivel de syslog (de 0 a 5) para el puerto serie
          
sWifiSSID1              x x x x                     Primer SSID de Wifi
pWifiPassword1          N x x x                     Primer password
sWifiSSID2              x x x x                     Segundo SSID de Wifi
pWifiPassword2          N x x x                     Segundo password
sWifiSSID3              x x x x                     Tercer SSID de Wifi
pWifiPassword3          N x x x                     Tercer password
          
eMQTTTopic              X x x x                     Topic en el que publica el nodo (en una rama que el usuario tenga permisos)
eMQTTServer             X X x x                     Nombre de host o dirección Ip del broker MQTT
eMQTTPort               X X x x                     Puerto de escucha del broker
eMQTTUser               X x x x                     Usuario de Whatsbee
pMQTTPassword           X x x x                     Password de Whatsbee
          
cReset                  X                           Resetea el nodo (comando)
cPubConfig              X                           Reenvia la configuración al broker (comando)
cResetPortal            x                           Resetea el nodo iniciando el portal de config
*/

extern "C" {
#include "spi_flash.h"
}

extern "C" uint32_t _SPIFFS_end;
#define CFG_LOCATION (((uint32_t)&_SPIFFS_end - 0x40200000) / SPI_FLASH_SEC_SIZE) - 2  // End of SPIFFS area

SYSCFG myCfg;

void CFG_Save()
{
  char log[80];

  if (memcmp(&myCfg, &sysCfg, sizeof(SYSCFG))) {
    noInterrupts();
    if (sysCfg.saveFlag == 0) {  // Handle default and rollover
      spi_flash_erase_sector(CFG_LOCATION + (sysCfg.saveFlag & 1));
      spi_flash_write((CFG_LOCATION + (sysCfg.saveFlag & 1)) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
    }
    sysCfg.saveFlag++;
    spi_flash_erase_sector(CFG_LOCATION + (sysCfg.saveFlag & 1));
    spi_flash_write((CFG_LOCATION + (sysCfg.saveFlag & 1)) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
    interrupts();
    sprintf_P(log, PSTR("Config: Saved configuration to flash at %X and count %d"), CFG_LOCATION + (sysCfg.saveFlag & 1), sysCfg.saveFlag);
    addLog(LOG_LEVEL_DEBUG, log);
    myCfg = sysCfg;
  }
}

void CFG_Default()
{
  addLog(LOG_LEVEL_INFO, "Config: Use default configuration");
  memset(&sysCfg, 0x00, sizeof(SYSCFG));//borra el contenido del array
  memset(&myCfg, 0x00, sizeof(SYSCFG));//borra el contenido del array
  sysCfg.cfg_holder = CFG_HOLDER;
  sysCfg.saveFlag = 0;
  sysCfg.nodeSerialLogLevel = SERIAL_LOG_LEVEL;
  sysCfg.nodeSysLogLevel  = SYS_LOG_LEVEL;
  strcpy(sysCfg.nodeSyslogHost, SYS_LOG_HOST);
  strcpy(sysCfg.WifiSSID1, STA_SSID);
  strcpy(sysCfg.WifiPassword, STA_PASS);
  strcpy(sysCfg.WifiSSID2, "");
  strcpy(sysCfg.WifiPassword2, "");
  strcpy(sysCfg.WifiSSID3, "");
  strcpy(sysCfg.WifiPassword3, "");
  strcpy(sysCfg.MQTTServer, MQTT_SERVER);
  strcpy(sysCfg.MQTTPort, MQTT_PORT);
  strcpy(sysCfg.MQTTUser, MQTT_USER);
  strcpy(sysCfg.MQTTPassword, MQTT_PASSWORD);
  strcpy(sysCfg.MQTTTopic, MQTT_TOPIC);
  strcpy(sysCfg.nodeName, NODE_NAME);
  strcpy(sysCfg.nodeType, NODE_TYPE);
  sysCfg.updWifiConfigFromMQTT = UPD_WIFI_CFG_FROM_MQTT;
  sysCfg.updMqttConfigFromMQTT = UPD_MQTT_CFG_FROM_MQTT;
  sysCfg.timezone = APP_TIMEZONE;
  sysCfg.power = APP_POWER;
  sysCfg.nextStartInitPortal = 1;
  sysCfg.nodeSendConfigInterval = SEND_CONFIG_TIME;
  sysCfg.nodeSendDataInterval  = SEND_DATA_TIME;
  sysCfg.nodeSendDataThreshold = SEND_DATA_THRESHOLD;
  sysCfg.nodeSleepInterval = NODE_SLEEP;


  //BORRAR  Serial.print ("Justo antes de guardar sysCfg: ");
  //BORRAR  Serial.println (sysCfg.MQTTServer);

  CFG_Save();
}

void CFG_Load()
{
  char log[80];

  noInterrupts();
  spi_flash_read((CFG_LOCATION) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
  spi_flash_read((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE, (uint32 *)&myCfg, sizeof(SYSCFG));
  interrupts();
  if (sysCfg.saveFlag < myCfg.saveFlag) sysCfg = myCfg;

  sprintf_P(log, PSTR("Config: Loaded configuration from flash at %X and count %d"), CFG_LOCATION + (sysCfg.saveFlag & 1), sysCfg.saveFlag);
  addLog(LOG_LEVEL_DEBUG, log);
  if (sysCfg.cfg_holder != CFG_HOLDER) CFG_Default();
  myCfg = sysCfg;
  CFG_Print();
}

void CFG_Erase()
{
  char log[80];
  SpiFlashOpResult result;

  uint32_t _sectorStart = (ESP.getSketchSize() / SPI_FLASH_SEC_SIZE) + 1;
  uint32_t _sectorEnd = ESP.getFlashChipRealSize() / SPI_FLASH_SEC_SIZE;
  byte nodeSerialLogLevel = sysCfg.nodeSerialLogLevel;

  sprintf_P(log, PSTR("Config: Erasing %d flash sectors"), _sectorEnd - _sectorStart);
  addLog(LOG_LEVEL_DEBUG, log);

  for (uint32_t _sector = _sectorStart; _sector < _sectorEnd; _sector++) {
    noInterrupts();
    result = spi_flash_erase_sector(_sector);
    interrupts();
    if (LOG_LEVEL_DEBUG_MORE <= nodeSerialLogLevel) {
      Serial.print(F("Flash: Erased sector "));
      Serial.print(_sector);
      if (result == SPI_FLASH_RESULT_OK)
        Serial.println(F(" OK"));
      else
        Serial.println(F(" Error"));
      delay(10);
    }
  }
}

//TODO:En la version definitiva esto debe de borrarse y todas las referencias
void CFG_Print()
{//TODO:grabar en la memoria estatica
  if (sysCfg.nodeSerialLogLevel) {
  Serial.println(F("----------------------SYSCONFIG--------------------"));
  Serial.print (F("cfg_holder: ")); Serial.println(sysCfg.cfg_holder);
  Serial.print (F("saveFlag: ")); Serial.println(sysCfg.saveFlag);
  Serial.print (F("nodeSerialLogLevel: ")); Serial.println(sysCfg.nodeSerialLogLevel);
  Serial.print (F("nodeSysLogLevel : ")); Serial.println(sysCfg.nodeSysLogLevel );
  Serial.print (F("nodeSyslogHost: ")); Serial.println(sysCfg.nodeSyslogHost);
  Serial.print (F("WifiSSID1: ")); Serial.println(sysCfg.WifiSSID1);
  Serial.print (F("WifiPassword: ")); Serial.println(sysCfg.WifiPassword);
  Serial.print (F("WifiSSID2: ")); Serial.println(sysCfg.WifiSSID2);
  Serial.print (F("WifiPassword2: ")); Serial.println(sysCfg.WifiPassword2);
  Serial.print (F("WifiSSID3: ")); Serial.println(sysCfg.WifiSSID3);
  Serial.print (F("WifiPassword3: ")); Serial.println(sysCfg.WifiPassword3);
  Serial.print (F("MQTTServer: ")); Serial.println(sysCfg.MQTTServer);
  Serial.print (F("MQTTPort: ")); Serial.println(sysCfg.MQTTPort);
  Serial.print (F("MQTTUser: ")); Serial.println(sysCfg.MQTTUser);
  Serial.print (F("MQTTPassword: ")); Serial.println(sysCfg.MQTTPassword);
  Serial.print (F("MQTTTopic: ")); Serial.println(sysCfg.MQTTTopic);
  Serial.print (F("nodeName: ")); Serial.println(sysCfg.nodeName);
  Serial.print (F("nodeType: ")); Serial.println(sysCfg.nodeType);
  Serial.print (F("updWifiConfigFromMQTT: ")); Serial.println(sysCfg.updWifiConfigFromMQTT);
  Serial.print (F("updMqttConfigFromMQTT: ")); Serial.println(sysCfg.updMqttConfigFromMQTT);
  Serial.print (F("timezone: ")); Serial.println(sysCfg.timezone);
  Serial.print (F("power: ")); Serial.println(sysCfg.power);
  Serial.print (F("nextStartInitPortal: ")); Serial.println(sysCfg.nextStartInitPortal);
  Serial.print (F("nodeSendConfigInterval: ")); Serial.println(sysCfg.nodeSendConfigInterval);
  Serial.print (F("nodeSendDataInterval : ")); Serial.println(sysCfg.nodeSendDataInterval );
  Serial.print (F("nodeSendDataThreshold: ")); Serial.println(sysCfg.nodeSendDataThreshold);
  Serial.print (F("nodeSleepInterval: ")); Serial.println(sysCfg.nodeSleepInterval);
  Serial.println (F("***************SYSCFG*************************"));
  }
  else
  {
   Serial.print ("sysCfg.nodeSerialLogLevel: "); Serial.println(sysCfg.nodeSerialLogLevel);
  }
}

