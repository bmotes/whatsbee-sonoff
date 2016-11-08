/* Conecta al servidor de MQTT y se suscribe al DataTopic y a los diferentes ConfigTopics*/
//TODO: comprobar credenciales de MQTT http://pubsubclient.knolleary.net/api.html

void connectMQTT() {
  char log[80];
  int intentosConexionMQTT = 1;
  while (!mqttClient.connect(ApSsid, sysCfg.MqttUser, sysCfg.MqttPassword)) {
    sprintf_P(log, PSTR("MQTT: Conn attempt %d of %d"), intentosConexionMQTT, MQTT_CONN_RETRYS);
    addLog(LOG_LEVEL_DEBUG, log);
    if (sysCfg.SerialLogLevel) {Serial.print("M");}
    intentosConexionMQTT++;
    delay(500);
    if (intentosConexionMQTT > MQTT_CONN_RETRYS) {
      razonPortal ("Datos de WhatsBee incorrectos (credenciales o nombre y puerto del servidor)");
      sprintf_P(log, PSTR("MQTT: > %d broker conns attempts, open portal"), MQTT_CONN_RETRYS);
      addLog(LOG_LEVEL_INFO, log);
      sysCfg.NextStartInitPortal = 1; //TODO:Interceptar un error en las credenciales del MQTT
      CFG_Save();
      ESP.reset();
    }
  }
  conMQTT=true;     //Indica al log que el servidor está disponible
  sprintf_P(log, PSTR("DEVI:Boot")); addLog(LOG_LEVEL_DEBUG, log);
  addLog(LOG_LEVEL_INFO, log);
  
  sprintf_P(log, PSTR("MQTT: conn to the broker %s, user %s."), sysCfg.MqttServer, sysCfg.MqttUser);
  addLog(LOG_LEVEL_INFO, log);
  ledBlink (3, 0.05); //Señaliza la conexión correcta al servidor MQTT

  mqttClient.subscribe(deviceTopic + String("CFG/+")); //Sr suscribe a los mensajes de config
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed->\"%s%s\""), deviceTopic.c_str(), "CFG/+");
  addLog(LOG_LEVEL_INFO, log);
  
  mqttClient.subscribe(deviceTopic + String("EPT/+")); //Se suscribe a los End Point Topics
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed->\"%s%s\""), deviceTopic.c_str(), "EPT/+");
  addLog(LOG_LEVEL_INFO, log);

  mqttClient.subscribe(deviceTopic + String("CMD/+")); //Se suscribe a los Command Topics
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed->\"%s%s\""), deviceTopic.c_str(), "CMD/+");
  addLog(LOG_LEVEL_INFO, log);

  mqttClient.subscribe(sysCfg.MqttTopic);
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed->\"%s\""), sysCfg.MqttTopic);
  addLog(LOG_LEVEL_INFO, log);
}
/*Callback de que se ha recibido un mensaje, comprueba que no sea de config y, si no lo es ejecuta el callback principal*/
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  if (!configTopic(topic, payload)) { //Ha llegado un topic, pero que no es de config
    onMQTTMsg (topic, payload, bytes, length);
  }
}
/* Verifica si es un configTopic y hace con él lo que haya que hacer */
boolean configTopic (String topic, String payload) {
//REC COMPIL  char log[80];
  String shortTopic = topic;
  payload = payload.substring(0, 200); //limita el número de carácteres
  if (topic.startsWith(deviceTopic, 0)) { //es un parámetro de configuración porque está por debajo del devicetopic
    if (topic.startsWith(deviceTopic + String("EPT/"), 0)) { //Es un endPoinTopic
      return handleEndPointTopic(topic, payload);
    }
    else if (topic.startsWith(deviceTopic + String("CMD/"), 0)) { //Es un commandTopic
      return handleCommandTopic(topic, payload);
    }
    else if (topic.startsWith(deviceTopic + String("CFG/"), 0)) { //Es un configTopic
      return handleConfigTopic(topic, payload);
    }
  } 
  else {
    return false;//Lo que ha llegado no es un parametro de config porque no está por debajo del config topic
  }
  return false;
}
/*Envia toda la info de configuración*/
void sendConfigInfo(){
  getCfg("gDeviceId", getUniqueId(), PERM_ALL);
  getCfg("gNodeHardwareVer", HW_VER, PERM_ALL);
  getCfg("FirmwareVer", FW_VER, PERM_ALL);
  getCfg("RunTime", String(millis()), PERM_ALL);
  getCfg("Voltage", String(ESP.getVcc()/1024.00f), PERM_ALL);
  getCfg("Permissions", sysCfg.Permissions, PERM_ALL);

  if ((sysCfg.Permissions & PERM_GET_WIFI) !=0){
    getCfg("WifiSSID1", sysCfg.WifiSSID1, PERM_GET_WIFI);
    getCfg("WifiPassword1", passwordProtect(sysCfg.WifiPassword1), PERM_GET_WIFI);
    getCfg("WifiSSID2", sysCfg.WifiSSID2, PERM_GET_WIFI);
    getCfg("WifiPassword2", passwordProtect(sysCfg.WifiPassword2), PERM_GET_WIFI);
    getCfg("WifiSSID3", sysCfg.WifiSSID3, PERM_GET_WIFI);
    getCfg("WifiPassword3", passwordProtect(sysCfg.WifiPassword3), PERM_GET_WIFI);
  }
  if ((sysCfg.Permissions & PERM_GET_MQTT) !=0){
    getCfg("MqttServer", sysCfg.MqttServer, PERM_GET_MQTT);
    getCfg("MqttPort", sysCfg.MqttPort, PERM_GET_MQTT);
    getCfg("MqttUser", sysCfg.MqttUser, PERM_GET_MQTT);
    getCfg("MqttPassword", passwordProtect(sysCfg.MqttPassword), PERM_GET_MQTT);
    getCfg("MqttTopic", sysCfg.MqttTopic, PERM_GET_MQTT);
  }
  if ((sysCfg.Permissions & PERM_GET_DEVICE) !=0){
    getCfg("NodeName", sysCfg.NodeName, PERM_GET_DEVICE);
    getCfg("NodeType", sysCfg.NodeType, PERM_GET_DEVICE);
    getCfg("AdminName", sysCfg.AdminName, PERM_GET_DEVICE);
    getCfg("AdminAddress", sysCfg.AdminAddress, PERM_GET_DEVICE);
    getCfg("AdminMail", sysCfg.AdminMail, PERM_GET_DEVICE);
    getCfg("NodeDescr", sysCfg.NodeDescr, PERM_GET_DEVICE);
    getCfg("NodeLat", sysCfg.NodeLat, PERM_GET_DEVICE);
    getCfg("NodeLon", sysCfg.NodeLon, PERM_GET_DEVICE);
  }
  if ((sysCfg.Permissions & PERM_GET_SENSOR) !=0){
    getCfg("SendConfigInterval", sysCfg.SendConfigInterval, PERM_GET_SENSOR);
    getCfg("SendDataInterval", sysCfg.SendDataInterval, PERM_GET_SENSOR);
    getCfg("SendDataThreshold", sysCfg.SendDataThreshold, PERM_GET_SENSOR);
    getCfg("SleepInterval", sysCfg.SleepInterval, PERM_GET_SENSOR);
    getCfg("ReadSensorInterval", sysCfg.ReadSensorInterval, PERM_GET_SENSOR);

//########################ESPECIFICO DEL NODO (CONFIGURACIONES)##################

//###############################################################################

  }
  if ((sysCfg.Permissions & PERM_GET_LOG) !=0){
    getCfg("SysLogHost", sysCfg.SysLogHost, PERM_GET_LOG);
    getCfg("SysLogLevel", sysCfg.SysLogLevel, PERM_GET_LOG);
    getCfg("SerialLogLevel", sysCfg.SerialLogLevel, PERM_GET_LOG);
    getCfg("MqttLogLevel", sysCfg.MqttLogLevel, PERM_GET_LOG);
  }
  if ((sysCfg.Permissions & PERM_GET_APPW) !=0){
    getCfg("APPassword", passwordProtect(sysCfg.APPassword), PERM_GET_APPW);
  }  
}
/* Envia un parámetro de configuración al configTopic*/
void sendConfigParam(String topic, String payload){
  mqttClient.publish(deviceTopic + String("CFG/") + topic, payload);
  mqttClient.loop();
  }
/* Sobrecarga de la función que envia un parámetro de configuración */
void sendConfigParam(String topic, char payload){
  sendConfigParam(topic, String(payload));
  }
/* Envia una línea de Log al logTopic*/
void sendNodeLog (String msg) {
//REC COMPIL  char log[80];
  if (!isInterrupt){
  mqttClient.publish(deviceTopic + String("LOG/deviceLog"), msg);
  mqttClient.loop();
  }
  else{
    nodeLog=msg;            //Previene que se utilice el objeto mqttClient dentro de una interrupción porque se resetea el ESP
    pendingNodeLog=true;
  }
}
/* Publica en cuanlquier topic */
void sendNodeValue (String topic, String payload){
    char log[80];
    sprintf_P(log, PSTR("MQTT: Pub-> \"%s\"->\"%s\""), topic.c_str(), payload.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    mqttClient.publish(topic, payload);
    mqttClient.loop();
  }

boolean handleConfigTopic(String topic, String payload){
    char log[80];
    if (findText("Password", topic)!=-1){  //Camufla los passwords en el Log
      payload=passwordProtect(payload);
    }
    sprintf_P(log, PSTR("MQTT: CFG rec \"%s\"->\"%s\""), topic.c_str(), payload.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    return true;
}
boolean handleEndPointTopic(String topic, String payload){
      char log[80];
      String shortTopic = topic;
      shortTopic.replace(deviceTopic + String("EPT/"), String(""));    //TODO: ver como gestionamos que el topic sea largo
      sprintf_P(log, PSTR("MQTT: EPT rec \"%s\"->\"%s\""), topic.c_str(), payload.c_str());
      addLog(LOG_LEVEL_DEBUG, log);
      return true;
}
boolean handleCommandTopic(String topic, String payload){
  char log[80];
  String verbo;
  String parametro;
  String shortTopic = topic;
  String pwdProtPayload=payload; 
  int saveConfig=9;   //9->no hace nada, 1->Salva la config y manda el log, 0-> No guarda y devuelve log de no permisos
  shortTopic.replace(deviceTopic + String("CMD/"), String(""));    //TODO: ver como gestionamos que el topic sea largo
  if (findText("Password", topic)!=-1){pwdProtPayload=passwordProtect(payload);}  //Evita los passwords en el LOG
  sprintf_P(log, PSTR("MQTT: CMD rec\"%s\"->\"%s\""), topic.c_str(), pwdProtPayload.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
  verbo=shortTopic.substring(0,3);
  parametro = shortTopic.substring(3);

       if (parametro == String("NodeName")) {setGetCfg (sysCfg.NodeName, payload.substring(0, sizeof(sysCfg.NodeName)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("NodeType")) {setGetCfg (sysCfg.NodeType, payload.substring(0, sizeof(sysCfg.NodeType)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("SerialLogLevel")){setGetCfg (sysCfg.SerialLogLevel, atoi(payload.c_str()), PERM_GET_LOG, PERM_SET_LOG, parametro, verbo);}
  else if (parametro == String("SysLogLevel")){setGetCfg (sysCfg.SysLogLevel, atoi(payload.c_str()), PERM_GET_LOG, PERM_SET_LOG, parametro, verbo);}
  else if (parametro == String("MqttLogLevel")){setGetCfg (sysCfg.MqttLogLevel, atoi(payload.c_str()), PERM_GET_LOG, PERM_SET_LOG, parametro, verbo);}
  else if (parametro == String("SysLogHost")) {setGetCfg (sysCfg.SysLogHost, payload.substring(0, sizeof(sysCfg.SysLogHost)), PERM_GET_LOG, PERM_SET_LOG, parametro, verbo);}
  else if (parametro == String("SendConfigInterval")) {setGetCfg (sysCfg.SendConfigInterval, atof(payload.c_str()), PERM_GET_SENSOR, PERM_SET_SENSOR, parametro, verbo);
      if (sysCfg.SendConfigInterval<60000){sysCfg.SendConfigInterval=60000;}
    }
  else if (parametro == String("SendDataInterval")) {setGetCfg (sysCfg.SendDataInterval, atof(payload.c_str()), PERM_GET_SENSOR, PERM_SET_SENSOR, parametro, verbo);
      if (sysCfg.SendDataInterval <1000){sysCfg.SendDataInterval =1000;}
     }      
  else if (parametro == String("ReadSensorInterval")) {setGetCfg (sysCfg.ReadSensorInterval, atof(payload.c_str()), PERM_GET_SENSOR, PERM_SET_SENSOR, parametro, verbo);
      if (sysCfg.ReadSensorInterval <1000){sysCfg.ReadSensorInterval =1000;}
    }
  else if (parametro == String("SendDataThreshold")) {setGetCfg (sysCfg.SendDataThreshold, atof(payload.c_str()), PERM_GET_SENSOR, PERM_SET_SENSOR, parametro, verbo);
      if (sysCfg.SendDataThreshold<0){sysCfg.SendDataThreshold=0;}
  }
  else if (parametro == String("SleepInterval")) {setGetCfg (sysCfg.SleepInterval, atof(payload.c_str()), PERM_GET_SENSOR, PERM_SET_SENSOR, parametro, verbo);
      if (sysCfg.SleepInterval<0){sysCfg.SleepInterval=0;}
    }
  else if (parametro == String("MqttServer")){setGetCfg (sysCfg.MqttServer, payload.substring(0, sizeof(sysCfg.MqttServer)), PERM_GET_MQTT, PERM_SET_MQTT, parametro, verbo);}
  else if (parametro == String("MqttPort")){setGetCfg (sysCfg.MqttPort, payload.substring(0, sizeof(sysCfg.MqttPort)), PERM_GET_MQTT, PERM_SET_MQTT, parametro, verbo);}
  else if (parametro == String("MqttUser")){setGetCfg (sysCfg.MqttUser, payload.substring(0, sizeof(sysCfg.MqttUser)), PERM_GET_MQTT, PERM_SET_MQTT, parametro, verbo);}
  else if ((parametro == String("MqttPassword")) && (payload != String(HIDDEN_PASSWORD))){setGetCfg (sysCfg.MqttPassword, payload.substring(0, sizeof(sysCfg.MqttPassword)), PERM_GET_MQTT, PERM_SET_MQTT, parametro, verbo);}
  else if (parametro == String("MqttTopic")){setGetCfg (sysCfg.MqttTopic, payload.substring(0, sizeof(sysCfg.MqttTopic)), PERM_GET_MQTT, PERM_SET_MQTT, parametro, verbo);}
  else if (parametro == String("WifiSSID1")){setGetCfg (sysCfg.WifiSSID1, payload.substring(0, sizeof(sysCfg.WifiSSID1)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if ((parametro == String("WifiPassword1")) && (payload != String(HIDDEN_PASSWORD))){setGetCfg (sysCfg.WifiPassword1, payload.substring(0, sizeof(sysCfg.WifiPassword1)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if (parametro == String("WifiSSID2")){setGetCfg (sysCfg.WifiSSID2, payload.substring(0, sizeof(sysCfg.WifiSSID2)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if ((parametro == String("WifiPassword2")) && (payload != String(HIDDEN_PASSWORD))){setGetCfg (sysCfg.WifiPassword2, payload.substring(0, sizeof(sysCfg.WifiPassword2)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if (parametro == String("WifiSSID3")){setGetCfg (sysCfg.WifiSSID3, payload.substring(0, sizeof(sysCfg.WifiSSID3)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if ((parametro == String("WifiPassword3")) && (payload != String(HIDDEN_PASSWORD))){setGetCfg (sysCfg.WifiPassword3, payload.substring(0, sizeof(sysCfg.WifiPassword3)), PERM_GET_WIFI, PERM_SET_WIFI, parametro, verbo);}
  else if ((parametro == String("APPassword")) && (payload != String(HIDDEN_PASSWORD))){setGetCfg (sysCfg.APPassword, payload.substring(0, sizeof(sysCfg.APPassword)), PERM_GET_APPW, PERM_SET_APPW, parametro, verbo);}
  else if (parametro == String("AdminName")){setGetCfg (sysCfg.AdminName, payload.substring(0, sizeof(sysCfg.AdminName)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("AdminAddress")){setGetCfg (sysCfg.AdminAddress, payload.substring(0, sizeof(sysCfg.AdminAddress)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("AdminMail")){setGetCfg (sysCfg.AdminMail, payload.substring(0, sizeof(sysCfg.AdminMail)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("NodeDescr")){setGetCfg (sysCfg.NodeDescr, payload.substring(0, sizeof(sysCfg.NodeDescr)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("NodeLat")){setGetCfg (sysCfg.NodeLat, payload.substring(0, sizeof(sysCfg.NodeLat)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}
  else if (parametro == String("NodeLon")){setGetCfg (sysCfg.NodeLon, payload.substring(0, sizeof(sysCfg.NodeLon)), PERM_GET_DEVICE, PERM_SET_DEVICE, parametro, verbo);}

//########################ESPECIFICO DEL NODO (COMANDOS CONFIG)##################

//###############################################################################

//*******************Comandos*********************************
  else if (shortTopic == String("cmdReset")) {
    saveConfig = hasPermissions (PERM_EXEC_CMD);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Reset req"));
      addLog(LOG_LEVEL_INFO, log);
      ESP.reset();
      return true;
      }
  }
  else if (shortTopic == String("cmdPubConfig")) {
    saveConfig = hasPermissions (PERM_EXEC_CMD);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Pub CFG req"));
      addLog(LOG_LEVEL_INFO, log);
      sendConfigInfo();
      return true;
      }
  }
  else if (shortTopic == String("cmdPortal")) {
    saveConfig = hasPermissions (PERM_EXEC_CMD);
    if (saveConfig){
      razonPortal ("Solicitado inicio del portal desde el servidor.");
      sprintf_P(log, PSTR("CMD: Start portal req"));
      addLog(LOG_LEVEL_INFO, log);
      sysCfg.NextStartInitPortal = 1;
      CFG_Save();
      ESP.reset();
      return true;
    }
  }
  else if (shortTopic == String("cmdDataTopic")) {
    saveConfig = hasPermissions (PERM_EXEC_CMD);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Send dataTopic req"));
      addLog(LOG_LEVEL_INFO, log);
      pendingNodeValue = true; //Se activa un semaforo para enviar el topic en el loop https://github.com/knolleary/pubsubclient/issues/99
      return true;
    }
  }
  else if (shortTopic == String("cmdEndPoints")) {
    saveConfig = hasPermissions (PERM_EXEC_CMD);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Send EndPoints req"));
      addLog(LOG_LEVEL_INFO, log);
      mqttClient.publish(deviceTopic + String("EPT/endPointRele"), endPointRele);
      mqttClient.loop();
      mqttClient.publish(deviceTopic + String("EPT/endPointLed"), endPointLed);
      mqttClient.loop();
      return true;
    }
  }
  else if (shortTopic == String("cmdUpgradeFW")) {
//TODO: documentar en el log la version actual y la que piden
    saveConfig = hasPermissions (PERM_UPGR_FW);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Remote FW Upgr req %s"), payload.c_str());
      addLog(LOG_LEVEL_INFO, log);
      httpOTA = true;
      upgradeFW(payload);
      return true;
    }
  }      
  else if (shortTopic == String("cmdButtonPush")) {
    saveConfig = hasPermissions (PERM_SET_ENDPOINTS);
    if (saveConfig){
      sprintf_P(log, PSTR("CMD: Button pushed remotely"));
      addLog(LOG_LEVEL_INFO, log);
      onRemoteButtonPush();             //ejecuta el callback de boton pulsado en remoto
      return true;
    }
  }
  else{
      sprintf_P(log, PSTR("ERROR: unknown CMD %s"), shortTopic.c_str()); //TODO: poner el comando
      addLog(LOG_LEVEL_ERROR, log);
  }
  return true;
}


