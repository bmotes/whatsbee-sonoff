/* Funciones de Setup del dispositivo

 */

//*****************Funciones de parpadeo del led de estado********************
void ledOn(){
if (digitalRead(LED)==HIGH){
  ledInvertido = true;
  digitalWrite(LED, LOW);  //es lógica inversa
  endPointLed="on";
  onLedChange();
  }
}
void ledOff(){
  if (digitalRead(LED)==LOW){
    ledInvertido = false;
    digitalWrite(LED, HIGH); //es lógica inversa
    endPointLed="off";
    onLedChange();  
  }
}

void ledBlinkOff() {
  digitalWrite(LED, HIGH ^ ledInvertido);
}

void ledBlinkOn() {
  digitalWrite(LED, LOW ^ ledInvertido);
  initBlinkLedOff.once(tApagado, ledBlinkOff);
}

void ledBlink (double intervaloParpadeo, double tiempoEncendido) {
  if ( intervaloParpadeo > tiempoEncendido) {
    tApagado = tiempoEncendido;
    initBlinkLedOn.detach();
    initBlinkLedOn.attach(intervaloParpadeo, ledBlinkOn);
    return;
  }
  initBlinkLedOn.detach();
}
// Determina el tipo de pulsacion
void tipoPulsacion(){
  char log[80];
  if (tiempoPulsacion){                                   //Se ha pulsado el botón se hace una cosa o la otra en función de la duración
      sprintf_P(log, PSTR("DEV: button pushed %lu ms"), tiempoPulsacion);
      addLog(LOG_LEVEL_DEBUG_MORE, log);
      if (tiempoPulsacion >PUSH_TIME_FOR_RESET_ALL){
         tiempoPulsacion=0;
         pulsaReset();
      }
      else {
        if (tiempoPulsacion >PUSH_TIME_FOR_START_PORTAL){
         tiempoPulsacion=0;
         pulsaLarga();
        }
        else {
          if (tiempoPulsacion <75){
                tiempoPulsacion=0; //es un rebote del interruptor
          }
          else{
            tiempoPulsacion=0;
            onButtonPush();
          }
        }
      }
  }
}
// Interrupción de la pulsación del botón
void pulsadoBoton() { 
  Serial.print ("BORRAR:PulsadoBoton ");
  Serial.println (digitalRead(BUTTON));        
  isInterrupt=true;
  if (!digitalRead(BUTTON)){pulsado = millis();Serial.println ("BORRAR:Se ha pulsado");}                //se ha pulsado (está en 0)
  else{tiempoPulsacion = millis()- pulsado;Serial.println ("BORRAR:Se ha soltado");}                     //se ha soltado (esté en 1)
  isInterrupt=false;
}
//Recibida pulsación larga, se abre el portal
void pulsaLarga() {           
  ledBlink (0.1, 0.03);
  razonPortal ("Solicitado pulsando el botón del dispositivo.", 1);
  //BORRAR: sysCfg.NextStartInitPortal = 1;
  //BORRAR: CFG_Save();
//BORRAR:  ESP.reset();
}
//Recibida una pulsación muy larga, se resetea a su config por defecto
void pulsaReset(){
      char log[80];
      sprintf_P(log, PSTR("CNF: Hard reset req"));
      addLog(LOG_LEVEL_DEBUG, log);
      CFG_Default();
      sysCfg.NextStartInitPortal = 1;
      CFG_Save();
      ESP.reset();
}
//Enciende el relé
void releOn(){
  if(digitalRead(RELE)==LOW){
    digitalWrite(RELE, HIGH);
    endPointRele="on";
    onReleChange();
    }
 }
//Apaga el relé
void releOff(){
  if(digitalRead(RELE)==HIGH){
    digitalWrite(RELE, LOW);
    endPointRele="off";
    onReleChange();
  }
}
//Cambia el estado al relé (independientemente de cual tenga)
void releToggle(){
  if (digitalRead(RELE)==HIGH){
    digitalWrite(RELE, LOW);
    endPointRele="off";
  }
  else{
    digitalWrite(RELE, HIGH);
    endPointRele="on";
  }
  onReleChange();
}

//Setup del dispositivo
void setup() {
  onIniSetup();             //Callback de inicio de stup
  setupSerial();            //Configuracion inicial del puerto serie
  setupPins();              //Configuracion inicial de los pins
  setupGadget();                //Configuracion inicial del sistema de ficheros y el Json
  setupPortal();            //Se conecta a la wifi o inicializa el portal

  if (mqttClient.begin(sysCfg.MqttServer, atoi(sysCfg.MqttPort), secureClient)) {
    ledBlink (2, 0.05); 
  }

  connectMQTT();
  sendConfigInfo();
  onEndSetup();             //Callback de fin de Setup
}
//Setup del puerto serie
void setupSerial() {
  Serial.begin(115200);
  Serial.println(F("WhatsBee"));
  Serial.print (F("HW ver: "));
  Serial.println (HW_VER);
  Serial.print (F("FW ver: "));
  Serial.println (FW_VER);
}
/* Setup del hardware de los dispositivos*/
void setupPins () {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  ledBlink (0.5, 0.03);
  attachInterrupt(BUTTON, pulsadoBoton, CHANGE);
}
/* Setup del propio dispositivo*/
void setupGadget() {
  //CFG_Erase();//Solo para diagnóctico
  CFG_Load();
  String AP_SSID = (String ("WhatsBee-") + String(DEVICE_ID) + getUniqueId());
  String AP_PWD = (String (sysCfg.APPassword));
  AP_SSID.toCharArray (ApSsid, 30);
  AP_PWD.toCharArray (ApPassword, 30);
  deviceTopic = String("$DEV/") + String(sysCfg.MqttUser) + String("/") + getUniqueId() + String("/");
  if (sysCfg.NextStartInitPortal!=0){// ||((String(sysCfg.WifiSSID1)==String("")) && (String(sysCfg.WifiSSID2)==String("")) &&(String(sysCfg.WifiSSID3)==String("")))) { //Se marcó para activar el portal en el proximo reset
    Serial.println("BORRAR:está marcada para arrancar el portal");
    sysCfg.NextStartInitPortal = 0;
    CFG_Save(); //así en el proximo reinicio volverá a arrancar sin portal
    startConfigPortal(ApSsid, ApPassword);
  }
}
//Setup del portal
void setupPortal() {
  //  if (!WiFi_autoConnect(ApSsid, ApPassword)) {
  if (String(sysCfg.WifiSSID1) != "") {
    wifiMulti.addAP(sysCfg.WifiSSID1, sysCfg.WifiPassword1); //TODO:warning: comparison with string literal results in unspecified behaviour [-Waddress]
  }
  if (String(sysCfg.WifiSSID2) != "") {
    wifiMulti.addAP(sysCfg.WifiSSID2, sysCfg.WifiPassword2); //TODO:warning: comparison with string literal results in unspecified behaviour [-Waddress]
  }
  if (String(sysCfg.WifiSSID3) != "") {
    wifiMulti.addAP(sysCfg.WifiSSID3, sysCfg.WifiPassword3); //TODO:warning: comparison with string literal results in unspecified behaviour [-Waddress]
  }
  if (!autoConnect(ApSsid, ApPassword)) {
    delay(3000);
    ESP.reset();    //reset and try again, or maybe put it to deep sleep
    delay(5000);
  }
  //Si has llegado aqui estás conectado a la Wifi
  //  addLog(LOG_LEVEL_INFO, "Connected!!! :)");
}
//Loop principal
void loop() {
  char log[80];
tipoPulsacion();                //Determina el tipo de pulsacion
mqttClient.loop();
  delay(10);                    // <- fixes some issues with WiFi stability
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  //Se ejecuta periodicamente cada vez que le toca enviar la config
    if(millis() - lastConfigTime > sysCfg.SendConfigInterval) {
      char log[80];
      lastConfigTime = millis();
      sprintf_P(log, PSTR("MQTT: Send config info"));
      addLog(LOG_LEVEL_INFO, log);
      onSendConfigInterval();
      }

  //Se ejecuta periodicamente cada vez que le toca enviar los datos
    if(millis() - lastDataTime > sysCfg.SendDataInterval ) {
      char log[80];
      lastDataTime = millis();
      sprintf_P(log, PSTR("MQTT: Send dataTopic"));
      addLog(LOG_LEVEL_DEBUG, log);
      onSendDataInterval();
      }

  //Se ejecuta periodicamente para comprobar que está conectado
    if(millis() - lastCheckWifiTime > CHECK_CONECTION_TIME ) {
      char log[80];
      lastCheckWifiTime = millis();
      sprintf_P(log, PSTR("MQTT: Check conn stat"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
        if (WiFi.status()!= WL_CONNECTED){
          autoConnect(ApSsid, ApPassword);        
        }
      }

  //Se ejecuta periodicamente cada vez que le toca leer un sensor
    if((millis() - lastSensorTime > sysCfg.ReadSensorInterval) || (millis() - lastSensorTime > sensorErrorInterval)) {
      if (sensorErrorInterval!=sysCfg.ReadSensorInterval){sensorErrorInterval=sysCfg.ReadSensorInterval;}
      char log[80];
      lastSensorTime = millis();
      sprintf_P(log, PSTR("MQTT: Read sensor"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
      onReadSensorInterval();
      }

  //Retrasa la activación de las interrupciones despues de pulsar el botón para evitar rebotes
/*  if ((millis() - rebotMillis > 500) && rebote) {
    rebote = false;
    attachInterrupt(BUTTON, pulsadoBoton, CHANGE);
  }*/

  //Escribe las actualizaciones pendientes de estado en el broker
  if (pendingNodeValue) {
    pendingNodeValue = false;
    sprintf_P(log, PSTR("MQTT: Pub \"%s\"->\"%s\""), sysCfg.MqttTopic, nodeValue.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    mqttClient.publish(sysCfg.MqttTopic, nodeValue);
    mqttClient.loop();
  }
  if (endPointReleLoop){
    mqttClient.publish(deviceTopic + String("EPT/endPointRele"), endPointRele); //TODO:Se ejecuta dentro de la interrupción
    mqttClient.loop();
    endPointReleLoop=false;
  }
  if (endPointLedLoop){
    mqttClient.publish(deviceTopic + String("EPT/endPointLed"), endPointLed);
    mqttClient.loop();
    endPointLedLoop=false;
  }
  
//########################ESPECIFICO DEL NODO (INSTRUCCIONES DEL LOOP)#############################


//#############################################################################################

  if(pendingNodeLog) {
      mqttClient.publish(deviceTopic + String("LOG/deviceLog"), nodeLog);
      mqttClient.loop();
    pendingNodeLog=false;
  }
   yield(); // Do (almost) nothing -- yield to allow ESP8266 background functions
}



