
//TODO: Mirar si vale la pena que solo se mande el mensaje si cambia el valor
boolean configTopic (String topic, String payload) {
  char log[80];
  String shortTopic = topic;
  payload = payload.substring(0, 100); //limita el número de carácteres
  if (topic.startsWith(deviceTopic, 0)) { //es un parámetro de configuración porque está por debajo del devicetopic
    if (topic.startsWith(deviceTopic + String("EPT/"), 0)) { //Es un endPoinTopic
      shortTopic.replace(deviceTopic + String("EPT/"), String(""));    //TODO: ver como gestionamos que el topic sea largo
      
      //LED
      //RELE
      //BUTTON
      Serial.print ("se ha actualizado un endpointTopic: ");
      Serial.print (topic);
      Serial.print (", ");
      Serial.println (payload);
    }
    else { //No es un endPointTopic
      int saveConfig=0;   //0->no hace nada, 1->Salva la config y manda el log, 2-> No guarda y devuelve log de no permisos
      shortTopic.replace(deviceTopic, String(""));    //TODO: ver como gestionamos que el topic sea largo
      sprintf_P(log, PSTR("MQTT: Config topic received \"%s\" = \"%s\""), topic.c_str(), payload.c_str());
      addLog(LOG_LEVEL_DEBUG, log);
  
      if (shortTopic == String("setsNodeName")) {
        payload.toCharArray(sysCfg.nodeName, payload.length() + 1);
        saveConfig=1;
      }
      else if (shortTopic == String("setgNodeType")) {
        payload.toCharArray(sysCfg.nodeType, payload.length() + 1);
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSerialLogLevel")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSerialLogLevel = atoi(strVal);
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSysLogLevel")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSysLogLevel  = atoi(strVal);
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSyslogHost")) {
        payload.toCharArray(sysCfg.nodeSyslogHost, payload.length() + 1);
        saveConfig=1;
      }
      else if (shortTopic == String("nextStartInitPortal")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nextStartInitPortal = atoi(strVal);
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSendConfigInterval")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSendConfigInterval = atoi(strVal);
        if (sysCfg.nodeSendConfigInterval<60000){sysCfg.nodeSendConfigInterval=60000;}
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSendDataInterval")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSendDataInterval  = atoi(strVal);
        if (sysCfg.nodeSendDataInterval <1000){sysCfg.nodeSendDataInterval =1000;}
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSendDataThreshold")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSendDataThreshold = atoi(strVal);
        if (sysCfg.nodeSendDataThreshold<0){sysCfg.nodeSendDataThreshold=0;}
        saveConfig=1;
      }
      else if (shortTopic == String("setsNodeSleepInterval")) {
        char strVal[4];
        payload.toCharArray(strVal, payload.length() + 1);
        sysCfg.nodeSleepInterval = atoi(strVal);
        if (sysCfg.nodeSleepInterval<0){sysCfg.nodeSleepInterval=0;}
        saveConfig=1;
      }
      else if (shortTopic == String("seteMQTTServer")) {
          if (sysCfg.updMqttConfigFromMQTT){
            payload.toCharArray(sysCfg.MQTTServer, payload.length() + 1);
            saveConfig=1;
          }
          else{ saveConfig=2;}
        }
      else if (shortTopic == String("seteMQTTPort")) {
          if (sysCfg.updMqttConfigFromMQTT){
            payload.toCharArray(sysCfg.MQTTPort, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("seteMQTTUser")) {
          if (sysCfg.updMqttConfigFromMQTT){
            payload.toCharArray(sysCfg.MQTTUser, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setpMQTTPassword")) {
          if (sysCfg.updMqttConfigFromMQTT){
            payload.toCharArray(sysCfg.MQTTPassword, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("seteMQTTTopic")) {
          if (sysCfg.updMqttConfigFromMQTT){
            payload.toCharArray(sysCfg.MQTTTopic, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setsWifiSSID1")) {
          if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiSSID1, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setpWifiPassword1")) {
          if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiPassword, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setsWifiSSID2")) {
          if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiSSID2, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setpWifiPassword2")) {
          if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiPassword2, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("setsWifiSSID3")) {
          if (sysCfg.updWifiConfigFromMQTT){
            payload.toCharArray(sysCfg.WifiSSID3, payload.length() + 1);
            saveConfig=1;
          }
          else {saveConfig=2;}
     }
      else if (shortTopic == String("setpWifiPassword3") && sysCfg.updWifiConfigFromMQTT) {
          if (sysCfg.updWifiConfigFromMQTT){
              payload.toCharArray(sysCfg.WifiPassword3, payload.length() + 1);
              saveConfig=1;
          }
          else {saveConfig=2;}
      }
      else if (shortTopic == String("cReset")) {
        sendNodeLog(PSTR("COMMAND: Solicitado Reset por MQTT"));
        ESP.reset();
        return true;
      }
      else if (shortTopic == String("cPubConfig")) {
        sendConfigInfo();
        sendNodeLog (PSTR("COMMAND: Solicitada Configuración"));
        return true;
      }
      else if (shortTopic == String("cResetPortal")) {
        sendNodeLog (PSTR("COMMAND: Solicitado Reset con config"));
        sysCfg.nextStartInitPortal = 1;
        CFG_Save();
        ESP.reset();
        return true;
      }
      else if (shortTopic == String("cSetEndPointLed")) {
        sendNodeLog (PSTR("COMMAND: cambiado end point Led"));
        mqttClient.publish(deviceTopic + String("EPT/endPointLed"), payload);
        mqttClient.loop();
        callbackEndPointLed (payload);
        return true;
      }
      else if (shortTopic == String("cSetEndPointRele")) {
        sendNodeLog (PSTR("COMMAND: cambiado end point Rele"));
        mqttClient.publish(deviceTopic + String("EPT/endPointRele"), payload);
        mqttClient.loop();
        callbackEndPointRele (payload);
        return true;
      }
      else if (shortTopic == String("cSetEndPointButton")) {
        //sendNodeLog (PSTR("COMMAND: cambiado end point Button"));
        mqttClient.publish(deviceTopic + String("EPT/endPointButton"), payload);
        mqttClient.loop();
        callbackEndPointButton (payload);
        return true;
      }
      
  
      if (saveConfig==1){
        saveConfig=0;
        shortTopic.replace("set", String(""));
        CFG_Save();
        sprintf_P(log, PSTR("SUCCESS: Configured %s from broker."), shortTopic.c_str());
        sendNodeLog (log);
        sendConfigParam(shortTopic, payload); 
        }
      else if (saveConfig==2){
        saveConfig=0;
        sprintf_P(log, PSTR("ERROR: Configuring %s from broker. Insufficient permissions."), shortTopic.c_str());
        sendNodeLog (log);
        }
      return true;
    }
  } //Era un configTopic
  else {
    return false;//Lo que ha llegado no es un parametro de config porque no está por debajo del config topic
  }
}

