/* Comandos del dispositivo
Nombre V45          Send Config / Recibir MQTT / Recibir web / Enviar web  Descripción
sNodeName               X X x x                     Nombre común del nodo
gNodeType               X x                         Tipo de nodo
sSendConfigInterval     X X x x                     Intervalo de envio de los datos de configuración
sSendDataInterval       X x x x                     Intervalo de envio de los datos
sSendDataThreshold      X X x x                     Umbral que se tiene que superar para que envie los datos
sSleepInterval          X X x x                     Intervalo de Sleep (0 es no sleep)
gNodeHardwareVer            X N                         Versión del hardware
gFirmwareVer            X N                         Versión del firmware
gRunTime            X N                         Tiempo desde el encendido (en milisegundos)
gVoltage            X N                         Tensión de alimentación del nodo.
          
sSysLogHost         X x x x                     Host al que envía el syslog
sSysLogLevel        X X x x                     Nivel de syslog (de 0 a 5)
sSerialLogLevel     X X x x                     Nivel de syslog (de 0 a 5) para el puerto serie
          
sWifiSSID1              x x x x                     Primer SSID de Wifi
pWifiPassword1          N x x x                     Primer password
sWifiSSID2              x x x x                     Segundo SSID de Wifi
pWifiPassword2          N x x x                     Segundo password
sWifiSSID3              x x x x                     Tercer SSID de Wifi
pWifiPassword3          N x x x                     Tercer password
          
eMqttTopic              X x x x                     Topic en el que publica el nodo (en una rama que el usuario tenga permisos)
eMqttServer             X X x x                     Nombre de host o dirección Ip del broker MQTT
eMqttPort               X X x x                     Puerto de escucha del broker
eMqttUser               X x x x                     Usuario de Whatsbee
pMqttPassword           X x x x                     Password de Whatsbee
          
cReset                  X                           Resetea el nodo (comando)
cPubConfig              X                           Reenvia la configuración al broker (comando)
cResetPortal            x                           Resetea el nodo iniciando el portal de config
cDataTopic              x                           Envia el Data Topic
cEndPoint               x                           Envia todos los End Points
cButtonPush             x                           Pulsacion remota del botón
*/
/*CONFIG: Includes, defines*/
extern "C" {
  #include "spi_flash.h"
}
extern "C" uint32_t _SPIFFS_end;
#define CFG_LOCATION (((uint32_t)&_SPIFFS_end - 0x40200000) / SPI_FLASH_SEC_SIZE) - 2  // End of SPIFFS area
SYSCFG myCfg;
/*CONFIG: Salva la configuración en la memoria flash*/
void CFG_Save(){
  char log[80];

  if (memcmp(&myCfg, &sysCfg, sizeof(SYSCFG))) {
    noInterrupts();
    if (sysCfg.SaveFlag == 0) {  // Handle default and rollover
      spi_flash_erase_sector(CFG_LOCATION + (sysCfg.SaveFlag & 1));
      spi_flash_write((CFG_LOCATION + (sysCfg.SaveFlag & 1)) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
    }
    sysCfg.SaveFlag++;
    spi_flash_erase_sector(CFG_LOCATION + (sysCfg.SaveFlag & 1));
    spi_flash_write((CFG_LOCATION + (sysCfg.SaveFlag & 1)) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
    interrupts();
    sprintf_P(log, PSTR("Config: Saved configuration to flash at %X and count %d"), CFG_LOCATION + (sysCfg.SaveFlag & 1), sysCfg.SaveFlag);
    addLog(LOG_LEVEL_DEBUG, log);
    myCfg = sysCfg;
  }
}
/*CONFIG: Carga la configuración por defecto si no coincide el CfgHolder*/
void CFG_Default(){
  addLog(LOG_LEVEL_INFO, "Config: Use default configuration");
  memset(&sysCfg, 0x00, sizeof(SYSCFG));//borra el contenido del array
  memset(&myCfg, 0x00, sizeof(SYSCFG));//borra el contenido del array
  sysCfg.CfgHolder = CFG_HOLDER;
  sysCfg.SaveFlag = 0;
  sysCfg.SerialLogLevel = DEFAULT_SERIAL_LOG_LEVEL;
  sysCfg.SysLogLevel  = DEFAULT_SYSLOG_LEVEL;
  strcpy(sysCfg.SysLogHost, DEFAULT_SYSLOG_HOST);
  strcpy(sysCfg.WifiSSID1, DEFAULT_STA_SSID1);
  strcpy(sysCfg.WifiPassword1, DEFAULT_STA_PASS1);
  strcpy(sysCfg.WifiSSID2, DEFAULT_STA_SSID2);
  strcpy(sysCfg.WifiPassword2, DEFAULT_STA_PASS2);
  strcpy(sysCfg.WifiSSID3, DEFAULT_STA_SSID3);
  strcpy(sysCfg.WifiPassword3, DEFAULT_STA_PASS3);
  strcpy(sysCfg.MqttServer, DEFAULT_MQTT_SERVER);
  strcpy(sysCfg.MqttPort, MQTT_PORT);
  strcpy(sysCfg.MqttUser, DEFAULT_MQTT_USER);
  strcpy(sysCfg.MqttPassword, DEFAULT_MQTT_PASSWORD);
  strcpy(sysCfg.MqttTopic, DEFAULT_MQTT_TOPIC);
  strcpy(sysCfg.NodeName, DEFAULT_NODE_NAME);
  strcpy(sysCfg.NodeType, DEFAULT_NODE_TYPE);
  strcpy(sysCfg.APPassword, DEFAULT_AP_PASSWORD);
  sysCfg.updWifiConfigFromMQTT = UPD_WIFI_CFG_FROM_MQTT;
  sysCfg.updMqttConfigFromMQTT = UPD_MQTT_CFG_FROM_MQTT;
  sysCfg.TimeZone = DEFAULT_APP_TIMEZONE;
  sysCfg.Power = DEFAULT_APP_POWER;
  sysCfg.NextStartInitPortal = 1;
  sysCfg.SendConfigInterval = DEFAULT_CONFIG_TIME;
  sysCfg.SendDataInterval  = DEFAULT_DATA_INTERVAL;
  sysCfg.SendDataThreshold = DEFAULT_DATA_THRESHOLD;
  sysCfg.ReadSensorInterval = DEFAULT_SENSOR_INTERVAL;
  sysCfg.SleepInterval = DEFAULT_SLEEP_TIME;
  sysCfg.CachedWifi = 0;
  sysCfg.Permissions = DEFAULT_PERMISSIONS;
  strcpy(sysCfg.AdminName, DEFAULT_ADMIN_NAME);
  strcpy(sysCfg.AdminAddress, DEFAULT_ADMIN_ADDRESS);
  strcpy(sysCfg.AdminMail, DEFAULT_ADMIN_MAIL);
  strcpy(sysCfg.NodeDescr, DEFAULT_NODE_DESCR);
  strcpy(sysCfg.NodeLat, DEFAULT_NODE_LAT);
  strcpy(sysCfg.NodeLon, DEFAULT_NODE_LON);
  sysCfg.MqttLogLevel  = DEFAULT_MQTT_LOG_LEVEL;
  strcpy(sysCfg.PortalReason, DEFAULT_PORTAL_REASON);

  CFG_Save();
}
/*CONFIG: carga los datos guardados en la flash a la variable sisCfg*/
void CFG_Load(){
  char log[80];

  noInterrupts();
  spi_flash_read((CFG_LOCATION) * SPI_FLASH_SEC_SIZE, (uint32 *)&sysCfg, sizeof(SYSCFG));
  spi_flash_read((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE, (uint32 *)&myCfg, sizeof(SYSCFG));
  interrupts();
  if (sysCfg.SaveFlag < myCfg.SaveFlag) sysCfg = myCfg;

  sprintf_P(log, PSTR("Config: Loaded configuration from flash at %X and count %d"), CFG_LOCATION + (sysCfg.SaveFlag & 1), sysCfg.SaveFlag);
  addLog(LOG_LEVEL_DEBUG, log);
  if (sysCfg.CfgHolder != CFG_HOLDER) CFG_Default();
  myCfg = sysCfg;
  CFG_Print();
}
/*CONFIG: Borra la configuración de la flash*/
void CFG_Erase(){
  char log[80];
  SpiFlashOpResult result;

  uint32_t _sectorStart = (ESP.getSketchSize() / SPI_FLASH_SEC_SIZE) + 1;
  uint32_t _sectorEnd = ESP.getFlashChipRealSize() / SPI_FLASH_SEC_SIZE;
  byte SerialLogLevel = sysCfg.SerialLogLevel;

  sprintf_P(log, PSTR("Config: Erasing %d flash sectors"), _sectorEnd - _sectorStart);
  addLog(LOG_LEVEL_DEBUG, log);

  for (uint32_t _sector = _sectorStart; _sector < _sectorEnd; _sector++) {
    noInterrupts();
    result = spi_flash_erase_sector(_sector);
    interrupts();
    if (LOG_LEVEL_DEBUG_MORE <= SerialLogLevel) {
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
/*CONFIG: Imprime en la pantalla inicial los valores de configuración almacenados*/
void CFG_Print(){
  if (sysCfg.SerialLogLevel) {
  Serial.println(F("----------------------SYSCONFIG--------------------"));
  Serial.println(F("Parameter\t\t\t Value"));
  Serial.print (F("CfgHolder:\t\t\t  ")); Serial.println(sysCfg.CfgHolder);
  Serial.print (F("SaveFlag:\t\t\t  ")); Serial.println(sysCfg.SaveFlag);
  Serial.print (F("SerialLogLevel:\t\t\t  ")); Serial.println(sysCfg.SerialLogLevel);
  Serial.print (F("MqttLogLevel:\t\t\t  ")); Serial.println(sysCfg.MqttLogLevel);
  Serial.print (F("SysLogLevel:\t\t\t  ")); Serial.println(sysCfg.SysLogLevel );
  Serial.print (F("SysLogHost:\t\t\t  ")); Serial.println(sysCfg.SysLogHost);
  Serial.print (F("WifiSSID1:\t\t\t  ")); Serial.println(sysCfg.WifiSSID1);
  Serial.print (F("WifiPassword1:\t\t\t  ")); Serial.println(hidePassword (String(sysCfg.WifiPassword1)));
  Serial.print (F("WifiSSID2:\t\t\t  ")); Serial.println(sysCfg.WifiSSID2);
  Serial.print (F("WifiPassword2:\t\t\t  ")); Serial.println(hidePassword (String(sysCfg.WifiPassword2)));
  Serial.print (F("WifiSSID3:\t\t\t  ")); Serial.println(sysCfg.WifiSSID3);
  Serial.print (F("WifiPassword3:\t\t\t  ")); Serial.println(hidePassword (String(sysCfg.WifiPassword3)));
  Serial.print (F("MqttServer:\t\t\t  ")); Serial.println(sysCfg.MqttServer);
  Serial.print (F("MqttPort:\t\t\t  ")); Serial.println(sysCfg.MqttPort);
  Serial.print (F("MqttUser:\t\t\t  ")); Serial.println(sysCfg.MqttUser);
  Serial.print (F("MqttPassword:\t\t\t  ")); Serial.println(hidePassword (String(sysCfg.MqttPassword)));
  Serial.print (F("MqttTopic:\t\t\t  ")); Serial.println(sysCfg.MqttTopic);
  Serial.print (F("APPassword:\t\t\t  ")); Serial.println(hidePassword (String(sysCfg.APPassword)));
  Serial.print (F("NodeName:\t\t\t  ")); Serial.println(sysCfg.NodeName);
  Serial.print (F("NodeType:\t\t\t  ")); Serial.println(sysCfg.NodeType);
  Serial.print (F("updWifiConfigFromMQTT:\t\t  ")); Serial.println(sysCfg.updWifiConfigFromMQTT);
  Serial.print (F("updMqttConfigFromMQTT:\t\t  ")); Serial.println(sysCfg.updMqttConfigFromMQTT);
  Serial.print (F("TimeZone:\t\t\t  ")); Serial.println(sysCfg.TimeZone);
  Serial.print (F("Power:\t\t\t\t  ")); Serial.println(sysCfg.Power);
  Serial.print (F("NextStartInitPortal:\t\t  ")); Serial.println(sysCfg.NextStartInitPortal);
  Serial.print (F("SendConfigInterval:\t\t\t ")); Serial.println(sysCfg.SendConfigInterval);
  Serial.print (F("SendDataInterval:\t\t\t ")); Serial.println(sysCfg.SendDataInterval );
  Serial.print (F("SendDataThreshold:\t\t\t ")); Serial.println(sysCfg.SendDataThreshold);
  Serial.print (F("ReadSensorInterval:\t\t\t ")); Serial.println(sysCfg.ReadSensorInterval);
  Serial.print (F("CachedWifi:\t\t\t  ")); Serial.println(sysCfg.CachedWifi);
  Serial.print (F("Permissions:\t\t\t  ")); Serial.println(sysCfg.Permissions);
  Serial.print (F("AdminName:\t\t\t  ")); Serial.println(sysCfg.AdminName);
  Serial.print (F("AdminAddress:\t\t\t  ")); Serial.println(sysCfg.AdminAddress);
  Serial.print (F("AdminMail:\t\t\t  ")); Serial.println(sysCfg.AdminMail);
  Serial.print (F("NodeDescr:\t\t\t  ")); Serial.println(sysCfg.NodeDescr);
  Serial.print (F("NodeLat:\t\t\t  ")); Serial.println(sysCfg.NodeLat);
  Serial.print (F("NodeLon:\t\t\t  ")); Serial.println(sysCfg.NodeLon);
  Serial.print (F("PortalReason:\t\t\t  ")); Serial.println(sysCfg.PortalReason);
  Serial.println (F("***************SYSCFG*************************"));
  }
  else
  {
   Serial.print (F("sysCfg.SerialLogLevel: ")); Serial.println(sysCfg.SerialLogLevel);
  }
}
/*SYSLOG: Envia un mensaje al syslog*/
void syslog(const char *message){
  char mess[168], str[200];
  portUDP.beginPacket(sysCfg.SysLogHost, DEFAULT_SYSLOG_PORT);
  strncpy(mess, message, 166);
  mess[167] = 0;
  sprintf_P(str, PSTR("%s %s"), Hostname, mess);
  portUDP.write(str);
  portUDP.endPacket();
}
/*SYSLOG: Envia un mensaje(char) al syslog*/
void addLog(byte loglevel, const char *line){
  DEBUG_MSG("DebugMsg %s\n", line);
#ifdef SERIAL_IO
  if (loglevel <= sysCfg.SerialLogLevel) Serial.println(line);
#endif
  if ((WiFi.status() == WL_CONNECTED) && (loglevel <= sysCfg.SysLogLevel )){
    syslog(line);
  }
  if (conMQTT && (loglevel <= sysCfg.MqttLogLevel )){
//      if (!isInterrupt){            //Si está en una interrupción no lo manda con send Node, se resetea el ESP
//        sendNodeLog(String(line));
//      }
//      else{
        nodeLog = String(line);
        pendingNodeLog=true;
//      }
    }
}

/*SYSLOG: Envia un mensaje(string) al syslog*/
void addLog(byte loglevel, String& string){
  addLog(loglevel, string.c_str());
}


