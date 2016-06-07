void connectMQTT() {
  char log[80];
  int intentosConexionMQTT = 1;
  sprintf_P(log, PSTR("MQTT: Conectando a broker MQTT %s"), sysCfg.mqtt_server);
  addLog(LOG_LEVEL_INFO, log);
  while (!mqttClient.connect(autoSSID_name, sysCfg.mqtt_user, sysCfg.mqtt_password)) {
    sprintf_P(log, PSTR("MQTT: Intento de conexión %d de %d"), intentosConexionMQTT, MQTT_CONN_RETRYS);
    addLog(LOG_LEVEL_DEBUG, log);
    Serial.print(".");
    intentosConexionMQTT++;
    delay(500);
    if (intentosConexionMQTT > MQTT_CONN_RETRYS) {
      sprintf_P(log, PSTR("MQTT: Más de %d intentos de conexión al servidor MQTT, desviando al config portal"), MQTT_CONN_RETRYS);
      addLog(LOG_LEVEL_INFO, log);
      sysCfg.reboot_setup = 1; //TODO:Interceptar un error en las credenciales del MQTT
      CFG_Save();
      ESP.reset();
    }
  }
  sprintf_P(log, PSTR("MQTT: conectado al servidor MQTT %s, usuario %s."), sysCfg.mqtt_server, sysCfg.mqtt_user);
  addLog(LOG_LEVEL_INFO, log);
  ledBlink (3, 0.05); //Señaliza la conexión correcta al servidor MQTT

  mqttClient.subscribe(deviceTopic + String("+"));
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: Suscrito a \"%s%s\""), deviceTopic.c_str(), "#");
  addLog(LOG_LEVEL_INFO, log);

  mqttClient.subscribe(sysCfg.mqtt_topic);
  mqttClient.loop();  // Solve LmacRxBlk:1 messages
  sprintf_P(log, PSTR("MQTT: Suscrito a \"%s\""), sysCfg.mqtt_topic);
  addLog(LOG_LEVEL_INFO, log);
}

//**********************se ha recibido un mensaje de MQTT********************************
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  char log[80];
  //char paramArray[10];
  sprintf_P(log, PSTR("MQTT: Recibido \"%s\" = %s"), topic.c_str(), payload.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
  //  Serial.println(String("incoming: ") +topic + String(" - ")+payload);
  if (!configTopic(topic, payload)) { //Ha llegado un topic, pero que no es de config
    if (payload == "on") { //TODO: verificar que es el topic correcto
      estado = true;
      digitalWrite(RELE, HIGH);
      digitalWrite(LED, LOW);
    }
    else {
      estado = false;
      digitalWrite(RELE, LOW);
      digitalWrite(LED, HIGH);
    }
  }
}

boolean configTopic (String topic, String payload) {
  char log[80];
  payload = payload.substring(0, 30); //limita el número de carácteres
  if (topic.startsWith(deviceTopic, 0)) { //es un parámetro de configuración
    String param = topic;
    param.replace(deviceTopic, String(""));    //TODO: ver como gestionamos que el topic sea largo
    sprintf_P(log, PSTR("MQTT: Recibido Config Topic \"%s\" = %s"), topic.c_str(), payload.c_str());
    addLog(LOG_LEVEL_DEBUG, log);

    if (param == String("sNodeName")) {
      payload.toCharArray(sysCfg.nodeName, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I1: Configurado nodeName");
      return true;
    }
    else if (param == String("gNodeType")) {
      payload.toCharArray(sysCfg.nodeType, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I2: Configurado nodeType");
      return true;
    }
    else if (param == String("sNodeSerialLogLevel")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSerialLogLevel = atoi(strVal);
      CFG_Save();
      setNodeMSG("I3: Configurado sNodeSerialLogLevel");
      return true;
    }
    else if (param == String("sNodeSysLogLevel")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSysLogLevel  = atoi(strVal);
      CFG_Save();
      setNodeMSG("I4: Configurado sNodeSysLogLevel");
      return true;
    }
    else if (param == String("sNodeSyslogHost")) {
      payload.toCharArray(sysCfg.nodeSyslogHost, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I5: Configurado sNodeSyslogHost");
      return true;
    }
    else if (param == String("reboot_setup")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.reboot_setup = atoi(strVal);
      CFG_Save();
      setNodeMSG("I6: Configurado reboot_setup");
      return true;
    }
    else if (param == String("sNodeSendConfigInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendConfigInterval = atoi(strVal);
      if (sysCfg.nodeSendConfigInterval<60000){sysCfg.nodeSendConfigInterval=60000;}
      CFG_Save();
      setNodeMSG("I7: Configurado sNodeSendConfigInterval");
      return true;
    }
    else if (param == String("sNodeSendDataInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataInterval  = atoi(strVal);
      if (sysCfg.nodeSendDataInterval <1000){sysCfg.nodeSendDataInterval =1000;}
      CFG_Save();
      setNodeMSG("I7: Configurado sNodeSendDataInterval");
      return true;
    }
    else if (param == String("sNodeSendDataThreshold")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataThreshold = atoi(strVal);
      if (sysCfg.nodeSendDataThreshold<0){sysCfg.nodeSendDataThreshold=0;}
      CFG_Save();
      setNodeMSG("I7: Configurado sNodeSendDataThreshold");
      return true;
    }
    else if (param == String("sNodeSleepInterval")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSleepInterval = atoi(strVal);
      if (sysCfg.nodeSleepInterval<0){sysCfg.nodeSleepInterval=0;}
      CFG_Save();
      setNodeMSG("I7: Configurado sNodeSleepInterval");
      return true;
    }
    else if (param == String("cReset")) {
      setNodeMSG("I8: Solicitado Reset por MQTT");
      ESP.reset();
      return true;
    }
    else if (param == String("cPubConfig")) {
      sendConfigInfo();
      setNodeMSG("I9: Solicitada Configuración");
      return true;
    }
    else if (param == String("cResetPortal")) {
      setNodeMSG("IA: Solicitado Reset con config");
      sysCfg.reboot_setup = 1;
      CFG_Save();
      ESP.reset();
      return true;
    }
  }
  else {
    return false;//Lo que ha llegado no es un parametro de config.
  }
}


void setNodeMSG (String msg) {
  char log[80];
  sprintf_P(log, PSTR("MQTT: Log-> %s"), msg.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
  nodeMSG = msg;
  pendingNodeMSG = true;
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
  mqttClient.publish(deviceTopic + String("sNodeName"), sysCfg.nodeName);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeType"), sysCfg.nodeType);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSendConfigInterval"), String(sysCfg.nodeSendConfigInterval));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSendDataInterval"), String(sysCfg.nodeSendDataInterval ));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSendDataThreshold"), String(sysCfg.nodeSendDataThreshold));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSleepInterval"), String(sysCfg.nodeSleepInterval));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeHardwareVer"), HW_VER);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeFirmwareVer"), FW_VER);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeRuntime"), String(millis()));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeVoltaje"), String(ESP.getVcc()/1024.00f));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSyslogHost"), sysCfg.nodeSyslogHost);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("sNodeSysLogLevel"), String(sysCfg.nodeSysLogLevel ));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("gNodeVoltaje"), String(sysCfg.nodeSerialLogLevel));
  //Adicionales, ver si finalmente los incluimos o no
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("eMQTTTopic"), sysCfg.mqtt_topic);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("eMQTTserver"), sysCfg.mqtt_server);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("eMQTTPort"), sysCfg.mqtt_port);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("eMQTTUser"), sysCfg.mqtt_user);
  mqttClient.loop();
  //mqttClient.publish(deviceTopic + String("pMQTTPassword"), sysCfg.mqtt_password);
  //mqttClient.loop();
}


