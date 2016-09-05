//*****************Funciones de parpadeo del led de estado********************
void ledOff() {
  digitalWrite(LED, HIGH ^ estado);
}

void ledOn() {
  digitalWrite(LED, LOW ^ estado);
  apagaLed.once(tApagado, ledOff);
}

void ledBlink (double intervaloParpadeo, double tiempoEncendido) {
  if ( intervaloParpadeo > tiempoEncendido) {
    tApagado = tiempoEncendido;
    enciendeLed.detach();
    enciendeLed.attach(intervaloParpadeo, ledOn);
    return;
  }
  enciendeLed.detach();
}
//***FIN***********Funciones de parpadeo del led de estado********************

void pulsadoBoton() {
  detachInterrupt (BUTTON);
  if (!digitalRead(BUTTON)) { //Está en 0, se ha pulsado
    pulsado = millis();
    attachInterrupt(BUTTON, pulsadoBoton, CHANGE);
  }
  else {
    if ((millis() - pulsado) > INIT_PORTAL_TIME) {
      pulsaLarga();
    }
    else {
      onShortPush();
      rebote = true;
      rebotMillis = millis();
    }
  }
}

void pulsaLarga() {
  //Se he hecho una pulsación larga del botón, para configurar
  Serial.println(F("Long push"));
  //WB      WhatsBeeLib whatsbeeManager(LED, BUTTON);
  //WB      whatsbeeManager.resetSettings();
  ledBlink (0.1, 0.03);
  sysCfg.nextStartInitPortal = 1;
  CFG_Save();
  ESP.reset();
}
//****FIN*********Pulsación del botón*********************

void setupSerial() {
  //TODO:Ver si se puede integrar con el LOG
  Serial.begin(115200);
  Serial.println(F("WhatsBee"));
  Serial.print (F("HW ver: "));
  Serial.println (HW_VER);
  Serial.print (F("FW ver: "));
  Serial.println (FW_VER);
}

void setupPins () {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  ledBlink (0.5, 0.03);
  attachInterrupt(BUTTON, pulsadoBoton, CHANGE);
}

void setupGadget() {
  //CFG_Erase();//Solo para diagnóctico
  CFG_Load();
  String autoSSID = (String ("WhatsBee-") + String(ESP.getChipId()));
  deviceTopic = String("$DEV/") + String(sysCfg.MQTTUser) + String("/") + String(ESP.getChipId()) + String("/");
  autoSSID.toCharArray (autoSSID_name, 20);

  if (sysCfg.nextStartInitPortal) { //Se marcó para activar el portal en el proximo reset
    sysCfg.nextStartInitPortal = 0;
    CFG_Save(); //así en el proximo reinicio volverá a arrancar sin portal
    startConfigPortal(autoSSID_name, autoSSID_password);
  }
}

void setupPortal() {

  //  if (!WiFi_autoConnect(autoSSID_name, autoSSID_password)) {
  if (sysCfg.WifiSSID1 != "") {
    wifiMulti.addAP(sysCfg.WifiSSID1, sysCfg.WifiPassword);
  }
  if (sysCfg.WifiSSID2 != "") {
    wifiMulti.addAP(sysCfg.WifiSSID2, sysCfg.WifiPassword2);
  }
  if (sysCfg.WifiSSID3 != "") {
    wifiMulti.addAP(sysCfg.WifiSSID3, sysCfg.WifiPassword3);
  }
  if (!autoConnect(autoSSID_name, autoSSID_password)) {
    Serial.println(F("Connection failure"));
    delay(3000);
    ESP.reset();    //reset and try again, or maybe put it to deep sleep
    delay(5000);
  }
  //Si has llegado aqui estás conectado a la Wifi
  addLog(LOG_LEVEL_INFO, "Connected!!! :)");
}


