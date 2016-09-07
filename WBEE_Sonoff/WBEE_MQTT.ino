void connectMQTT() {
  char log[80];
  int intentosConexionMQTT = 1;
  while (!mqttClient.connect(autoSSID_name, sysCfg.MQTTUser, sysCfg.MQTTPassword)) {
    sprintf_P(log, PSTR("MQTT: Connection attempt %d of %d"), intentosConexionMQTT, MQTT_CONN_RETRYS);
    addLog(LOG_LEVEL_DEBUG, log);
    if (sysCfg.nodeSerialLogLevel) {Serial.print("M");}
    intentosConexionMQTT++;
    delay(500);
    if (intentosConexionMQTT > MQTT_CONN_RETRYS) {
      sprintf_P(log, PSTR("MQTT: more of %d connections attempts to broker, open config portal"), MQTT_CONN_RETRYS);
      addLog(LOG_LEVEL_INFO, log);
      sysCfg.nextStartInitPortal = 1; //TODO:Interceptar un error en las credenciales del MQTT
      CFG_Save();
      ESP.reset();
    }
  }
  sprintf_P(log, PSTR("MQTT: connected to the broker %s, user %s."), sysCfg.MQTTServer, sysCfg.MQTTUser);
  addLog(LOG_LEVEL_INFO, log);
  ledBlink (3, 0.05); //Señaliza la conexión correcta al servidor MQTT

  mqttClient.subscribe(deviceTopic + String("CFG/+")); //Sr suscribe a los mensajes de config
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed to \"%s%s\""), deviceTopic.c_str(), "CFG/+");
  addLog(LOG_LEVEL_INFO, log);
  
  mqttClient.subscribe(deviceTopic + String("EPT/+")); //Se suscribe a los End Point Topics
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed to \"%s%s\""), deviceTopic.c_str(), "EPT/+");
  addLog(LOG_LEVEL_INFO, log);

  mqttClient.subscribe(deviceTopic + String("CMD/+")); //Se suscribe a los Command Topics
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed to \"%s%s\""), deviceTopic.c_str(), "CMD/+");
  addLog(LOG_LEVEL_INFO, log);

  mqttClient.subscribe(sysCfg.MQTTTopic);
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed to \"%s\""), sysCfg.MQTTTopic);
  addLog(LOG_LEVEL_INFO, log);
}

//**********************se ha recibido un mensaje de MQTT********************************
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  if (!configTopic(topic, payload)) { //Ha llegado un topic, pero que no es de config
    onMQTTMsg (topic, payload, bytes, length);
  }
}

int getInterval (String payload) {
  char toString[6];
  payload.toCharArray(toString, payload.length() + 1);
  if (atoi(toString) != 0) {
    return atoi(toString);
  }
  return atoi(DEF_INTERVAL);
}

void sendConfigInfo(){
//********Configuraciones fijas del nodo*********
  sendConfigParam("gNodeHardwareVer", HW_VER);
  sendConfigParam("gNodeFirmwareVer", FW_VER);
  sendConfigParam("gNodeRuntime", String(millis()));
  sendConfigParam("gNodeVoltaje", String(ESP.getVcc()/1024.00f));
  sendConfigParam("sNodeName", sysCfg.nodeName);
  sendConfigParam("gNodeType", sysCfg.nodeType);
//********Configuraciones de datos*********
  sendConfigParam("sNodeSendConfigInterval", String(sysCfg.nodeSendConfigInterval));
  sendConfigParam("sNodeSendDataInterval", String(sysCfg.nodeSendDataInterval));
  sendConfigParam("sNodeSendDataThreshold", String(sysCfg.nodeSendDataThreshold));
  sendConfigParam("sNodeSleepInterval", String(sysCfg.nodeSleepInterval));
//********Configuraciones del syslog*********
  sendConfigParam("sNodeSyslogHost", sysCfg.nodeSyslogHost);
  sendConfigParam("sNodeSysLogLevel", String(sysCfg.nodeSysLogLevel));
  sendConfigParam("sNodeSerialLogLevel", String(sysCfg.nodeSerialLogLevel));
//*******Configuraciones de MQTT*********
  sendConfigParam("eMQTTServer", sysCfg.MQTTServer);
  sendConfigParam("eMQTTPort", sysCfg.MQTTPort);
  sendConfigParam("eMQTTUser", sysCfg.MQTTUser);
  //  sendConfigParam("pMQTTPassword", sysCfg.MQTTPassword);  
  sendConfigParam("eMQTTTopic", sysCfg.MQTTTopic);  
//*******Configuraciones de WIFI*********
  sendConfigParam("sWifiSSID1", sysCfg.WifiSSID1);  
  sendConfigParam("sWifiSSID2", sysCfg.WifiSSID2);  
  sendConfigParam("sWifiSSID3", sysCfg.WifiSSID3);  
  //  sendConfigParam("pWifiPassword1", sysCfg.wifiPassword1);  
  //  sendConfigParam("pWifiPassword2", sysCfg.wifiPassword2);  
  //  sendConfigParam("pWifiPassword3", sysCfg.wifiPassword3);  
}

void sendConfigParam(String topic, String payload)
  {//Envia un parámetro de configuración
  mqttClient.publish(deviceTopic + String("CFG/") + topic, payload);
  mqttClient.loop();
  }

void sendConfigParam(String topic, char payload)
  {//Sobrecarga de la anterior
  sendConfigParam(topic, String(payload));
  }

void sendNodeLog (String msg) {
  char log[80];
  sprintf_P(log, PSTR("MQTT: Log-> %s"), msg.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
  mqttClient.publish(deviceTopic + String("LOG/deviceLog"), msg);
  mqttClient.loop();
//  sendConfigParam ("LOG", msg);
}

void sendNodeValue (String topic, String payload){
    char log[80];
    sprintf_P(log, PSTR("MQTT: Published \"%s\" = %s"), topic.c_str(), nodeValue.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    mqttClient.publish(topic, payload);
    mqttClient.loop();
  }

