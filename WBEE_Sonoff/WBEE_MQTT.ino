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

  mqttClient.subscribe(deviceTopic + String("+"));
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: suscribed to \"%s%s\""), deviceTopic.c_str(), "#");
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

//TODO: Mirar si vale la pena que solo se mande el mensaje si cambia el valor
boolean configTopic (String topic, String payload) {
  char log[80];
  payload = payload.substring(0, 30); //limita el número de carácteres
  if (topic.startsWith(deviceTopic, 0)) { //es un parámetro de configuración porque está por debajo del devicetopic
    String param = topic;
    int saveConfig=0;   //0->no hace nada, 1->Salva la config y manda el log, 2-> No guarda y devuelve log de no permisos
    param.replace(deviceTopic, String(""));    //TODO: ver como gestionamos que el topic sea largo
    sprintf_P(log, PSTR("MQTT: Config topic received \"%s\" = \"%s\""), topic.c_str(), payload.c_str());
    addLog(LOG_LEVEL_DEBUG, log);

    if (param == String("setsNodeName")) {
      payload.toCharArray(sysCfg.nodeName, payload.length() + 1);
      saveConfig=1;
    }
    else if (param == String("setgNodeType")) {
      payload.toCharArray(sysCfg.nodeType, payload.length() + 1);
      saveConfig=1;
    }
    else if (param == String("setsNodeSerialLogLevel")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSerialLogLevel = atoi(strVal);
      saveConfig=1;
    }
    else if (param == String("setsNodeSysLogLevel")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSysLogLevel  = atoi(strVal);
      saveConfig=1;
    }
    else if (param == String("setsNodeSyslogHost")) {
      payload.toCharArray(sysCfg.nodeSyslogHost, payload.length() + 1);
      saveConfig=1;
    }
    else if (param == String("nextStartInitPortal")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nextStartInitPortal = atoi(strVal);
      saveConfig=1;
    }
    else if (param == String("setsNodeSendConfigInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendConfigInterval = atoi(strVal);
      if (sysCfg.nodeSendConfigInterval<60000){sysCfg.nodeSendConfigInterval=60000;}
      saveConfig=1;
    }
    else if (param == String("setsNodeSendDataInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataInterval  = atoi(strVal);
      if (sysCfg.nodeSendDataInterval <1000){sysCfg.nodeSendDataInterval =1000;}
      saveConfig=1;
    }
    else if (param == String("setsNodeSendDataThreshold")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataThreshold = atoi(strVal);
      if (sysCfg.nodeSendDataThreshold<0){sysCfg.nodeSendDataThreshold=0;}
      saveConfig=1;
    }
    else if (param == String("setsNodeSleepInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSleepInterval = atoi(strVal);
      if (sysCfg.nodeSleepInterval<0){sysCfg.nodeSleepInterval=0;}
      saveConfig=1;
    }
    else if (param == String("seteMQTTServer")) {
        if (sysCfg.updMqttConfigFromMQTT){
          payload.toCharArray(sysCfg.MQTTServer, payload.length() + 1);
          saveConfig=1;
        }
        else{ saveConfig=2;}
      }
    else if (param == String("seteMQTTPort")) {
        if (sysCfg.updMqttConfigFromMQTT){
          payload.toCharArray(sysCfg.MQTTPort, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("seteMQTTUser")) {
        if (sysCfg.updMqttConfigFromMQTT){
          payload.toCharArray(sysCfg.MQTTUser, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setpMQTTPassword")) {
        if (sysCfg.updMqttConfigFromMQTT){
          payload.toCharArray(sysCfg.MQTTPassword, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("seteMQTTTopic")) {
        if (sysCfg.updMqttConfigFromMQTT){
          payload.toCharArray(sysCfg.MQTTTopic, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setsWifiSSID1")) {
        if (sysCfg.updWifiConfigFromMQTT){
          payload.toCharArray(sysCfg.WifiSSID1, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setpWifiPassword1")) {
        if (sysCfg.updWifiConfigFromMQTT){
          payload.toCharArray(sysCfg.WifiPassword, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setsWifiSSID2")) {
        if (sysCfg.updWifiConfigFromMQTT){
          payload.toCharArray(sysCfg.WifiSSID2, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setpWifiPassword2")) {
        if (sysCfg.updWifiConfigFromMQTT){
          payload.toCharArray(sysCfg.WifiPassword2, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("setsWifiSSID3")) {
        if (sysCfg.updWifiConfigFromMQTT){
          payload.toCharArray(sysCfg.WifiSSID3, payload.length() + 1);
          saveConfig=1;
        }
        else {saveConfig=2;}
   }
    else if (param == String("setpWifiPassword3") && sysCfg.updWifiConfigFromMQTT) {
        if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiPassword3, payload.length() + 1);
            saveConfig=1;
        }
        else {saveConfig=2;}
    }
    else if (param == String("cReset")) {
      sendNodeLog(PSTR("COMMAND: Solicitado Reset por MQTT"));
      ESP.reset();
      return true;
    }
    else if (param == String("cPubConfig")) {
      sendConfigInfo();
      sendNodeLog (PSTR("COMMAND: Solicitada Configuración"));
      return true;
    }
    else if (param == String("cResetPortal")) {
      sendNodeLog (PSTR("COMMAND: Solicitado Reset con config"));
      sysCfg.nextStartInitPortal = 1;
      CFG_Save();
      ESP.reset();
      return true;
    }

    if (saveConfig==1){
      saveConfig=0;
      param.replace("set", String(""));
      CFG_Save();
      sprintf_P(log, PSTR("SUCCESS: Configured %s from broker."), param.c_str());
      sendNodeLog (log);
      sendConfigParam(param, payload); 
      }
    else if (saveConfig==2){
      saveConfig=0;
      sprintf_P(log, PSTR("ERROR: Configuring %s from broker. Insufficient permissions."), param.c_str());
      sendNodeLog (log);
      }
    return true;
  }
  else {
    return false;//Lo que ha llegado no es un parametro de config porque no está por debajo del config topic
  }
}

/*
void setNodeMSG (String msg) {
  char log[80];
  sprintf_P(log, PSTR("MQTT: Log-> %s"), msg.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
  sendConfigParam ("LOG", msg);
}
*/

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
  mqttClient.publish(deviceTopic + topic, payload);
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

