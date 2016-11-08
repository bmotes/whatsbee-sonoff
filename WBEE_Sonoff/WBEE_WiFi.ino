/*Diferentes intentos de conexión a la wifi*/
int autoConnect (char const *apName, char const *apPassword) {
  if (wifiConnectCache()!= WL_CONNECTED){
    if (wifiConnectStored()!=WL_CONNECTED){
      razonPortal ("Incorrect wifi user/password. WiFi.status = " + String (WiFi.status()));
      return startConfigPortal(apName, apPassword);
    }
  }
}//TODO: warning: control reaches end of non-void function [-Wreturn-type]
/* BORRAR, está resuelto el problema
int autoConnect (char const *apName, char const *apPassword) {
  //Primer intento de conectar con las credenciales almacenadas
  char log[80];
  wifiStart = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  sprintf_P(log, PSTR("\nWIFI: Connection attempt (cached credentials)"));
  addLog(LOG_LEVEL_INFO, log);
  while (WiFi.status() != WL_CONNECTED && millis() < wifiStart + WIFI_CONNECT_CACHE_TIME) {  //intento de conexión con credenciales en cache (es más rápido)
    delay(1000);
    if (sysCfg.SerialLogLevel) {Serial.print("C");}
  }
  if (WiFi.status() == WL_CONNECTED) {
    sprintf_P(log, PSTR("\nWIFI: Connected to WiFi: %s"), WiFi.SSID().c_str());
    addLog(LOG_LEVEL_INFO, log);
    return WiFi.status();
  }
  else {//No se ha conseguido conectar despues del tiempo
    sprintf_P(log, PSTR("\nWIFI: Connection attempt (stored credentials)"));
    addLog(LOG_LEVEL_INFO, log);
    wifiMulti.run();
    wifiStart = millis();
    while ((wifiMulti.run() != WL_CONNECTED) && (millis() < wifiStart + WIFI_CONNECT_STORED_TIME)) {
      delay(1000);
      if (sysCfg.SerialLogLevel) {Serial.print("W");}
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      sprintf_P(log, PSTR("\nWIFI: Connected to WiFi: %s"), WiFi.SSID().c_str());
      addLog(LOG_LEVEL_INFO, log);
    return WiFi.status();
    }
    else { //no se ha conectado a la Wifi
      return startConfigPortal(apName, apPassword);
    }
  }
}
*/

/* Intento de conexión a la wifi con credenciales en caché (más rápido)*/
int wifiConnectCache () {
char log[80];
  if (sysCfg.CachedWifi){
    wifiStart = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    sprintf_P(log, PSTR("\nWIFI: Conn attempt (cached)"));
    addLog(LOG_LEVEL_INFO, log);
    while ((WiFi.status() != WL_CONNECTED) && (millis() < (wifiStart + WIFI_CONNECT_CACHE_TIME))) { 
      delay(500);
      if (sysCfg.SerialLogLevel) {Serial.print("C");}
    }
    if (WiFi.status() == WL_CONNECTED) {
      sprintf_P(log, PSTR("\nWIFI: Conn OK WiFi: %s"), WiFi.SSID().c_str());
      addLog(LOG_LEVEL_INFO, log);
    }
  }
  else{
    sprintf_P(log, PSTR("WIFI: cahed creds enabled"));
    addLog(LOG_LEVEL_INFO, log);
    sysCfg.CachedWifi = 1;
    CFG_Save();
  }
    return WiFi.status();
}

/* Intento de conexión a la wifi con credenciales en almacenadas*/
int wifiConnectStored(){
    char log[80];                                
    sprintf_P(log, PSTR("\nWIFI: Conn attempt (stored)"));
    addLog(LOG_LEVEL_INFO, log);
    wifiMulti.run();
    wifiStart = millis();
    while ((wifiMulti.run() != WL_CONNECTED) && (millis() < (wifiStart + WIFI_CONNECT_STORED_TIME))) {  
      delay(500);
      if (sysCfg.SerialLogLevel) {Serial.print("W");}
    }
    if (WiFi.status() == WL_CONNECTED) {
      sprintf_P(log, PSTR("\nWIFI: Conn OK WiFi: %s"), WiFi.SSID().c_str());
      addLog(LOG_LEVEL_INFO, log);
    }
    return WiFi.status();
}


