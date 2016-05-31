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
      pulsaCorta();
      rebote = true;
      rebotMillis = millis();
    }
  }
}

void pulsaLarga() {
  //Se he hecho una pulsación larga del botón, para configurar
  Serial.println(F("Pulsación larga"));
  //WB      WhatsBeeLib whatsbeeManager(LED, BUTTON);
  //WB      whatsbeeManager.resetSettings();
  ledBlink (0.1, 0.03);
  sysCfg.reboot_setup = 1;
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

void setupFS() {
  //CFG_Erase();//Solo para diagnóctico
  CFG_Load();
  String autoSSID = (String ("WhatsBee-") + String(ESP.getChipId()));
  deviceTopic = String("$DEV/") + String(sysCfg.mqtt_user) + String("/") + String(ESP.getChipId()) + String("/");
  autoSSID.toCharArray (autoSSID_name, 20);

  if (sysCfg.reboot_setup) { //Se marcó para activar el portal en el proximo reset
    sysCfg.reboot_setup = 0;
    CFG_Save(); //así en el proximo reinicio volverá a arrancar sin portal
    startConfigPortal(autoSSID_name, autoSSID_password);
  }
}

void setupPortal() {

  //  if (!WiFi_autoConnect(autoSSID_name, autoSSID_password)) {
  if (sysCfg.sta_ssid != "") {
    wifiMulti.addAP(sysCfg.sta_ssid, sysCfg.sta_pwd);
  }
  if (sysCfg.sta_ssid2 != "") {
    wifiMulti.addAP(sysCfg.sta_ssid2, sysCfg.sta_pwd2);
  }
  if (sysCfg.sta_ssid3 != "") {
    wifiMulti.addAP(sysCfg.sta_ssid3, sysCfg.sta_pwd3);
  }
  if (!autoConnect(autoSSID_name, autoSSID_password)) {
    Serial.println(F("fallo de conexión"));
    delay(3000);
    ESP.reset();    //reset and try again, or maybe put it to deep sleep
    delay(5000);
  }
  //Si has llegado aqui estás conectado a la Wifi
  addLog(LOG_LEVEL_INFO, "Conectado!!! :)");
}


