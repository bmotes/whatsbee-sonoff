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
  sysCfg.seriallog_level = SERIAL_LOG_LEVEL;
  sysCfg.syslog_level = SYS_LOG_LEVEL;
  strcpy(sysCfg.syslog_host, SYS_LOG_HOST);
  strcpy(sysCfg.sta_ssid, STA_SSID);
  strcpy(sysCfg.sta_pwd, STA_PASS);
  strcpy(sysCfg.sta_ssid2, "");
  strcpy(sysCfg.sta_pwd2, "");
  strcpy(sysCfg.sta_ssid3, "");
  strcpy(sysCfg.sta_pwd3, "");
  strcpy(sysCfg.mqtt_server, MQTT_SERVER);
  strcpy(sysCfg.mqtt_port, MQTT_PORT);
  strcpy(sysCfg.mqtt_user, MQTT_USER);
  strcpy(sysCfg.mqtt_password, MQTT_PASSWORD);
  strcpy(sysCfg.mqtt_topic, MQTT_TOPIC);
  strcpy(sysCfg.nodeName, NODE_NAME);
  strcpy(sysCfg.nodeType, NODE_TYPE);
  strcpy(sysCfg.mqtt_subtopic, MQTT_TOPIC);
  sysCfg.timezone = APP_TIMEZONE;
  sysCfg.power = APP_POWER;
  sysCfg.reboot_setup = 1;
  sysCfg.nodeSendConfigTime = SEND_CONFIG_TIME;
  sysCfg.nodeSendDataTime = SEND_DATA_TIME;
  sysCfg.nodeSendDataThreshold = SEND_DATA_THRESHOLD;
  sysCfg.nodeSleep = NODE_SLEEP;


  //BORRAR  Serial.print ("Justo antes de guardar sysCfg: ");
  //BORRAR  Serial.println (sysCfg.mqtt_server);

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
  byte seriallog_level = sysCfg.seriallog_level;

  sprintf_P(log, PSTR("Config: Erasing %d flash sectors"), _sectorEnd - _sectorStart);
  addLog(LOG_LEVEL_DEBUG, log);

  for (uint32_t _sector = _sectorStart; _sector < _sectorEnd; _sector++) {
    noInterrupts();
    result = spi_flash_erase_sector(_sector);
    interrupts();
    if (LOG_LEVEL_DEBUG_MORE <= seriallog_level) {
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
{
  Serial.println("***************SYSCFG*************************");
  Serial.print ("sysCfg.cfg_holder: "); Serial.println(sysCfg.cfg_holder);
  Serial.print ("sysCfg.saveFlag: "); Serial.println(sysCfg.saveFlag);
  Serial.print ("sysCfg.seriallog_level: "); Serial.println(sysCfg.seriallog_level);
  Serial.print ("sysCfg.syslog_level: "); Serial.println(sysCfg.syslog_level);
  Serial.print ("sysCfg.syslog_host: "); Serial.println(sysCfg.syslog_host);
  Serial.print ("sysCfg.sta_ssid: "); Serial.println(sysCfg.sta_ssid);
  Serial.print ("sysCfg.sta_pwd: "); Serial.println(sysCfg.sta_pwd);
  Serial.print ("sysCfg.sta_ssid2: "); Serial.println(sysCfg.sta_ssid2);
  Serial.print ("sysCfg.sta_pwd2: "); Serial.println(sysCfg.sta_pwd2);
  Serial.print ("sysCfg.sta_ssid3: "); Serial.println(sysCfg.sta_ssid3);
  Serial.print ("sysCfg.sta_pwd3: "); Serial.println(sysCfg.sta_pwd3);
  Serial.print ("sysCfg.mqtt_server: "); Serial.println(sysCfg.mqtt_server);
  Serial.print ("sysCfg.mqtt_port: "); Serial.println(sysCfg.mqtt_port);
  Serial.print ("sysCfg.mqtt_user: "); Serial.println(sysCfg.mqtt_user);
  Serial.print ("sysCfg.mqtt_password: "); Serial.println(sysCfg.mqtt_password);
  Serial.print ("sysCfg.mqtt_topic: "); Serial.println(sysCfg.mqtt_topic);
  Serial.print ("sysCfg.nodeName: "); Serial.println(sysCfg.nodeName);
  Serial.print ("sysCfg.nodeType: "); Serial.println(sysCfg.nodeType);
  Serial.print ("sysCfg.mqtt_subtopic: "); Serial.println(sysCfg.mqtt_subtopic);
  Serial.print ("sysCfg.timezone: "); Serial.println(sysCfg.timezone);
  Serial.print ("sysCfg.power: "); Serial.println(sysCfg.power);
  Serial.print ("sysCfg.reboot_setup: "); Serial.println(sysCfg.reboot_setup);
  Serial.print ("sysCfg.nodeSendConfigTime: "); Serial.println(sysCfg.nodeSendConfigTime);
  Serial.print ("sysCfg.nodeSendDataTime: "); Serial.println(sysCfg.nodeSendDataTime);
  Serial.print ("sysCfg.nodeSendDataThreshold: "); Serial.println(sysCfg.nodeSendDataThreshold);
  Serial.print ("sysCfg.nodeSleep: "); Serial.println(sysCfg.nodeSleep);
  Serial.println("***************SYSCFG*************************");
}

