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

//*********************************MQTT***************************************
boolean configTopic (String topic, String payload) {
  char log[160];
  payload = payload.substring(0, 30); //limita el número de carácteres
  if (topic.startsWith(deviceTopic, 0)) { //es un parámetro de configuración
    String param = topic;
    param.replace(deviceTopic, String(""));    //TODO: ver como gestionamos que el topic sea largo
    sprintf_P(log, PSTR("MQTT: Recibido Config Topic \"%s\" = %s"), topic.c_str(), payload.c_str());
    addLog(LOG_LEVEL_DEBUG, log);

    if (param == String("nodeName")) {
      payload.toCharArray(sysCfg.nodeName, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I1: Configurado nodeName");
      return true;
    }
    else if (param == String("nodeType")) {
      payload.toCharArray(sysCfg.nodeType, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I2: Configurado nodeType");
      return true;
    }
    else if (param == String("seriallog_level")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.seriallog_level = atoi(strVal);
      CFG_Save();
      setNodeMSG("I3: Configurado seriallog_level");
      return true;
    }
    else if (param == String("syslog_level")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.syslog_level = atoi(strVal);
      CFG_Save();
      setNodeMSG("I4: Configurado seriallog_level");
      return true;
    }
    else if (param == String("syslog_host")) {
      payload.toCharArray(sysCfg.syslog_host, payload.length() + 1);
      CFG_Save();
      setNodeMSG("I5: Configurado syslog_host");
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
    else if (param == String("nodeSendConfigTime")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendConfigTime = atoi(strVal);
      if (sysCfg.nodeSendConfigTime<60000){sysCfg.nodeSendConfigTime=60000;}
      CFG_Save();
      setNodeMSG("I7: Configurado nodeSendConfigTime");
      return true;
    }
    else if (param == String("nodeSendDataTime")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataTime = atoi(strVal);
      if (sysCfg.nodeSendDataTime<1000){sysCfg.nodeSendDataTime=1000;}
      CFG_Save();
      setNodeMSG("I7: Configurado nodeSendDataTime");
      return true;
    }
    else if (param == String("nodeSendDataThreshold")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSendDataThreshold = atoi(strVal);
      if (sysCfg.nodeSendDataThreshold<0){sysCfg.nodeSendDataThreshold=0;}
      CFG_Save();
      setNodeMSG("I7: Configurado nodeSendDataThreshold");
      return true;
    }
    else if (param == String("nodeSleep")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSleep = atoi(strVal);
      if (sysCfg.nodeSleep<0){sysCfg.nodeSleep=0;}
      CFG_Save();
      setNodeMSG("I7: Configurado nodeSleep");
      return true;
    }
    else if (param == String("nodeSleep")) {
      char strVal[4];
      payload.toCharArray(strVal, payload.length() + 1);
      sysCfg.nodeSleep = atoi(strVal);
      if (sysCfg.nodeSleep<0){sysCfg.nodeSleep=0;}
      CFG_Save();
      setNodeMSG("I7: Configurado nodeSleep");
      return true;
    }
      /*    else if (param==String("nodeThre")){
            payload=payload.substring(0,4);
            payload.toCharArray(nodeThre, payload.length()+1);
            if (atoi(nodeThre)!=0){
              thre=atoi(nodeThre);
              //TODO: ver como hacemos para que guarde saveParametersToFS ();
              setNodeMSG("I4: Configurado nodeThre");
              }
              else{
              setNodeMSG("E3: nodeThre no es un numero");
              }
            return true;
          }
        else if (param==String("nodeMSG")|| param==String("nodeMillis")){
            //No hace nada para no entrar en un bucle, es un mensaje o los millis
            return true;
          }
        else{
          setNodeMSG("E1: Configuración desconocida");
        return true;//Lo que ha llegado es un parametro de config incorrecto.
          }*/
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
  mqttClient.publish(deviceTopic + String("nodeName"), sysCfg.nodeName);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeType"), sysCfg.nodeType);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeSendConfigTime"), String(sysCfg.nodeSendConfigTime));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeSendDataTime"), String(sysCfg.nodeSendDataTime));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeSendDataThreshold"), String(sysCfg.nodeSendDataThreshold));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeSleep"), String(sysCfg.nodeSleep));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeHardwareVer"), HW_VER);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeFirmwareVer"), FW_VER);
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeRunTime"), String(millis()));
  mqttClient.loop();
  mqttClient.publish(deviceTopic + String("nodeVoltaje"), String(ESP.getVcc()/1024.00f));
  mqttClient.loop();
}
//*********************************MQTT***************************************

