const char HTTP_HEAD_END[] PROGMEM = "</head><body><div style='text-align: left; display: inline-block;'>";
const char HTTP_ITEM_PADLOCK[] PROGMEM = "<img src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==' width='13px'/>";
const char HTTP_END[] PROGMEM = "</div></body></html>";
const char WB_HEAD[] PROGMEM = "<!DOCTYPE html><html lang=\"es\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>{v}</title>";
const char WB_STYLE[] PROGMEM = "<style>.fr{width:450px;padding:30px;margin:40px auto;background:#FFF;border-radius:10px;box-shadow:0 0 10px rgba(0,0,0,0.23);font:normal 18px Arial}.iw{padding:30px;background:#f8f8f8;border-radius:6px;margin-bottom:15px}.fr h1{background:#1ea213;padding:20px 30px 15px 95px;margin:-30px -30px 30px -30px;border-radius:10px 10px 0 0;color:#fff;text-shadow:1px 1px 3px rgba(0,0,0,0.12);font:normal 30px Arial;box-shadow:inset 0 2px 2px 0 rgba(255,255,255,0.17);border:1px solid #257c9e}.fr h1>span{display:block;margin-top:2px;font:13px Arial}.fr label{display:block;font-size:13px;color:#888;margin-bottom:15px}.fr input[type=text],.fr input[type=password],.fr input[type=number],.fr select{display:block;box-sizing:border-box;-moz-box-sizing:border-box;width:100%;padding:8px;border-radius:6px;border:2px solid #fff;box-shadow:inset 0 1px 1px rgba(0,0,0,0.33)}.fr .sc{font-size:20px;color:#1ea213;margin-bottom:5px;margin-left:20px}.sc span{background:#1ea213;padding:5px 10px 5px 10px;position:absolute;border-radius:50%;font-size:14px;margin-left:-45px;color:#fff;margin-top:-3px}.fr .bs{width:150px;background:#1ea213;padding:8px 20px 8px 20px;border-radius:30px;color:#fff;font-size:18px;margin:2px}.bs:hover{background:#116d09}</style>";
const char WB_SCRIPT[] PROGMEM = "<script>function tgl(){if(document.getElementById('oc').style.display=='block'){document.getElementById('oc').style.display='none';}else{document.getElementById('oc').style.display='block';}}function setAp(x){document.getElementById('sWifiSSID1').value = x.value;document.getElementById('pWifiPassword1').focus();tgl();}function setAp2(x){document.getElementById('sWifiSSID2').value = x.value;document.getElementById('pWifiPassword2').focus();tgl();}function setAp3(x){document.getElementById('sWifiSSID3').value = x.value;document.getElementById('pWifiPassword3').focus();tgl();}</script>";
const char WB_HEAD_END[] PROGMEM = "</head><body><div class='fr'><img style = \"position: absolute;margin: -20px;\" src = \"data:image/png;base64,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\"/>";
const char WB_HEAD_TITLE1[] PROGMEM = "<h1>Configura tu WhatsMote!!<span>Escribe los parámetros para WhatsBee</span></h1>";
const char WB_HEAD_TITLE2[] PROGMEM = "<h1>Configura tu WhatsMote!!<span>Datos guardados!!</span></h1>";
const char WB_HEAD_TITLE3[] PROGMEM = "<h1>Configura tu WhatsMote!!<span>Actualización de firmware</span></h1>";
const char WB_WIFI_DETECT[] PROGMEM = "<form action='wifisave' method='post'> <div class='sc'><span>1</span>Configuración de la wifi</div> <div class='iw'><Label><a href='#' onclick='tgl();'>Mostar redes detectadas</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"/wifi\">(Reescanear)</a></Label> <div id='oc' style='display:none'> ";
const char WB_FORM_WIFI[] PROGMEM = "<label><input type='radio' name='xx' onclick='setAp(this)' value='{v}'><input type='radio' name='yy' onclick='setAp2(this)' value='{v}'><input type='radio' name='zz' onclick='setAp3(this)' value='{v}'>{v} {r}% {i}<br></label>";
const char WB_INPUT_WIFI[] PROGMEM = "<label>SSID<input id='sWifiSSID1' type='text' name='sWifiSSID1' value='{v}'/></label><label>Password<input id='pWifiPassword1' type='password' name='pWifiPassword1' value='PasswordProtect'/></label>";
const char WB_INPUT_WIFI2[] PROGMEM = "<label>SSID (backup)<input id='sWifiSSID2' type='text' name='sWifiSSID2' value='{v}'/></label><label>Password (backup)<input id='pWifiPassword2' type='password' name='pWifiPassword2' value='PasswordProtect'/></label>";
const char WB_INPUT_WIFI3[] PROGMEM = "<label>SSID (backup 2)<input id='sWifiSSID3' type='text' name='sWifiSSID3' value='{v}'/></label><label>Password (backup 2)<input id='pWifiPassword3' type='password' name='pWifiPassword3' value='PasswordProtect'/></label>";
const char WB_FORM_BROKER[] PROGMEM = "<div class='sc'><span>2</span>Configuracion del broker</div><div class='iw'>";
const char WB_FORM_ADV[] PROGMEM = "<div class='sc'><span>3</span>Configuracion avanzada</div><div class='iw'>";
const char WB_FORM_PARAM[] PROGMEM = "<label>{p}<input id='{i}' type='{t}' name='{n}' value='{v}' /></label>";
const char WB_FORM_PARAM_LOG[] PROGMEM ="<label>{p}<select id='{i}' name='{n}'><option value='0'>None</option><option value='1'>Error</option><option value='2'>Info</option><option value='3'>Log</option><option value='4'>More log</option></select></label><script>document.getElementById(\"{i}\").value=\"{v}\";</script>";
const char WB_FORM_PARAM_SINO[] PROGMEM ="<label>{p}<select id='{i}' name='{n}'><option value='0'>No</option><option value='1'>Sí</option></select></label><script>document.getElementById(\"{i}\").value=\"{v}\";</script>";
const char WB_FORM_PARAM_NUMBER[] PROGMEM = "<label>{p}<input id='{i}' type='{t}' name='{n}' {r} value='{v}' /></label>";
const char WB_NODE_CONF[] PROGMEM = "<div class='sc'><span>4</span >Información del nodo</div><div class='iw'>";
const char WB_SCAN_LINK[] PROGMEM = "<div class='ba'><a href='wifi'><input class='bs' type='button' name='Scan'></a></div>";
const char WB_LINK_ADV[] PROGMEM = "<Label><a href='#' onclick=\"if(document.getElementById('wifiadv').style.display=='none'){document.getElementById('wifiadv').style.display='block';}else{document.getElementById('wifiadv').style.display='none';}if(document.getElementById('cfgadv').style.display=='none'){document.getElementById('cfgadv').style.display='block';}else{document.getElementById('cfgadv').style.display='none';}\">Configuración avanzada</a></Label>";
const char WB_BUTT_SUBMIT[] PROGMEM = "<div class = 'ba'><input class='bs' type='submit' name = 'Guardar'></div>";
const char WB_SAVED[] PROGMEM = "<div><h2>La configuración ha sido guardada</h2><span><br />El dispositivo se intentará conectar a la WiFi que has configurado.<br />En el momento en el que se haya conectado el led parpadeará una vez cada tres segundos. Puedes entrar de nuevo en el AP de configuración pulsando el botón más de 4 segundos.</span></div>";
const char WB_END[] PROGMEM = "</div></body></html>";
const char WB_FORM_UPLOAD[] PROGMEM = "<form method='POST' action='/update' enctype='multipart/form-data'><input type = 'file' name = 'update'><input type = 'submit' value = 'Update'></form>";
const char WB_UPGRADE_OK[] PROGMEM = "Se ha completado la actualización de firmware, el dispositivo arrancará de nuevo en menos de un minuto.<script>setTimeout(function(){ window.location.href='http://192.168.4.1';}, 6000);</script>";
const char WB_CIERRE_DIV[] PROGMEM = "</div>";

boolean       connect;
boolean       endUpload = false;//arreglar
unsigned long timeout = TIMEOUT;
unsigned long start = 0;
String        contenido;

int autoConnect (char const *apName, char const *apPassword) {
  //Primer intento de conectar con las credenciales almacenadas
  char log[80];
  wifiStart = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  sprintf_P(log, PSTR("\nWIFI: Connection attempt (cached credentials)"));
  addLog(LOG_LEVEL_INFO, log);
  while (WiFi.status() != WL_CONNECTED && millis() < wifiStart + WIFI_BEGIN_TIMEOUT) {
    delay(500);
    if (sysCfg.nodeSerialLogLevel) {Serial.print("C");}
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
    while (wifiMulti.run() != WL_CONNECTED && millis() < wifiStart + WIFI_BEGIN_CRED_TIMEOUT) {
      delay(500);
      if (sysCfg.nodeSerialLogLevel) {Serial.print("W");}
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


boolean  startConfigPortal(char const *apName, char const *apPassword) {//Inicia el Config Portal
  WiFi.mode(WIFI_AP);
  connect = false;
  ledBlink (0.1, 0.05);
  setupConfigPortal();

  while (timeout == 0 || millis() < start + timeout) {//Este es al bucle de la web
#if CAPTIVE_PORTAL
    dnsServer.processNextRequest(); //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
#endif
    server.handleClient(); //HTTP
    if (connect) { //connect es el flag de que tiene que intentar conectar a un AP, se activa después de enviar el form de config
      connect = false;
      delay(2000);
      addLog(LOG_LEVEL_INFO, "Portal: Connecting to new AP");
      // using user-provided  _ssid, _pass in place of system-stored ssid and pass
      if (autoConnect(sysCfg.WifiSSID1, sysCfg.WifiPassword) != WL_CONNECTED) {
        addLog(LOG_LEVEL_INFO, "Portal: Failed to connect");
      }//TODO: Hacer algo en este punto para que no se quede aqui.
      else { //Se ha conectado con la nueva configuración acabada de guardar
        WiFi.mode(WIFI_STA);
        //TODO: verificar en este punto si es más razonable que solo salve si se conecta
        break;
      }
    }//Fin del connect
    yield();
  }//Fin del bucle

  //server.reset(); //No se para que sirve esto
  //dnsServer.reset();   //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
  return  WiFi.status() == WL_CONNECTED;
}

void setupConfigPortal() {
  char log[80];
  char ip[16];

#if CAPTIVE_PORTAL
  dnsServer.reset(new DNSServer());   //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
  server.reset(new ESP8266WebServer(80));
#endif

  start = millis();

  sprintf_P(log, PSTR("Portal: Configuring Access point %s"), autoSSID_name);
  addLog(LOG_LEVEL_INFO, log);
  WiFi.softAP(autoSSID_name, autoSSID_password);
  delay(500); // Without delay I've seen the IP address blank

  strcpy (ip, toStringIp(WiFi.softAPIP()).c_str());
  sprintf_P(log, PSTR("Portal: AP IP Adress %s"), ip);
  addLog(LOG_LEVEL_INFO, log);

  /* Setup the DNS server redirecting all the domains to the apIP */
#if CAPTIVE_PORTAL
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());   //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
#endif
  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  server.on("/", &handleWifi);
  server.on("/wifi", &handleWifi);
  server.on("/wifisave", &handleWifiSave);
  server.on("/r", &handleReset);
  server.on("/update", HTTP_GET, &handleUpdateGet);//OTA
  server.on("/update", HTTP_POST, &handleUpdatePost, &handleUpload);//OTA
  server.onNotFound (&handleNotFound);
  server.begin(); // Web server start

  sprintf_P(log, PSTR("Portal: HTTP server started"));
  addLog(LOG_LEVEL_INFO, log);
}

//*****************************HANDLES WEB*******************************************************************
/** Wifi config page handler */
void handleWifi() {
  char log[80];
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String head = FPSTR(WB_HEAD);
  head.replace("{v}", "Config WhatsMote");
  server.sendContent(head);
  server.sendContent_P(WB_SCRIPT);
  server.sendContent_P(WB_STYLE);
  server.sendContent_P(WB_HEAD_END);
  server.sendContent_P(WB_HEAD_TITLE1);
  server.sendContent_P(WB_WIFI_DETECT);

  if (true) { //TODO: sustituye al scan que habñia en la funcion
    int n = WiFi.scanNetworks();
    sprintf_P(log, PSTR("Portal: Wifi Scan done"));
    addLog(LOG_LEVEL_INFO, log);
    if (n == 0) {
      sprintf_P(log, PSTR("Portal: No networks found."));
      addLog(LOG_LEVEL_ERROR, log);
      server.sendContent("No networks found. Refresh to scan again.");
    }
    else {
      String contenido;
      char log [80];
      char nomSSID[32];
      for (int i = 0; i < n; ++i)
      { //TODO: Hacer aqui el combo para mostar las Wifis
        WiFi.SSID(i).toCharArray (nomSSID, WiFi.SSID(i).length() + 1);
        //strcpy(nomSSID, WiFi.SSID(i).toCharArray()); //TODO:Poner el nombre de la Wifitambiñen en la linea de abajo
        sprintf_P(log, PSTR("Portal: SSID-> %s %d dB"), nomSSID, WiFi.RSSI(i));
        addLog(LOG_LEVEL_INFO, log);
        //        DEBUG_WM("SSID-> " + WiFi.SSID(i) + " " + WiFi.RSSI(i) + " dB");
        int quality = getRSSIasQuality(WiFi.RSSI(i));

//        if (_minimumQuality == -1 || _minimumQuality < quality) {

          String item = FPSTR(WB_FORM_WIFI);
          String rssiQ;
          rssiQ += quality;
          item.replace("{v}", WiFi.SSID(i));
          item.replace("{r}", rssiQ);
          if (WiFi.encryptionType(i) != ENC_TYPE_NONE) {
            item.replace("{i}", "");  //BMOTES: Antes (para poner el candado)  item.replace("{i}", FPSTR(WB_ITEM_PADLOCK));
          }
          else {
            item.replace("{i}", "***RED NO SEGURA***");
          }
          contenido += item;
          //server.sendContent(item);
          delay(0);
 //       }
 //       else {
 //         sprintf_P(log, PSTR("Portal: Skipping due to quality"));
 //         addLog(LOG_LEVEL_DEBUG, log);
 //       }

      }
      sprintf_P(log, PSTR("Portal: Send AP list"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
      server.sendContent(contenido);
      server.sendContent("<br/>");
      sprintf_P(log, PSTR("Portal: AP list sended"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
    }
  }

  server.sendContent_P(WB_CIERRE_DIV);
  contenido = FPSTR(WB_INPUT_WIFI);
  contenido.replace("{v}", sysCfg.WifiSSID1);
  server.sendContent(contenido);
  sprintf_P(log, PSTR("Portal: Send form init"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);

  server.sendContent ("<div id='wifiadv' style='display:none'>");
  contenido = FPSTR(WB_INPUT_WIFI2);
  contenido.replace("{v}", sysCfg.WifiSSID2);
  server.sendContent(contenido);

  contenido = FPSTR(WB_INPUT_WIFI3);
  contenido.replace("{v}", sysCfg.WifiSSID3);
  server.sendContent(contenido);

  server.sendContent_P(WB_CIERRE_DIV); //El cierre del display:none

  server.sendContent_P(WB_CIERRE_DIV);
  server.sendContent_P(WB_FORM_BROKER);

  //  char parLength[2];
  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "eMQTTServer");
  contenido.replace("{n}", "eMQTTServer");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "MQTT host");
  contenido.replace("{v}", sysCfg.MQTTServer);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "eMQTTPort");
  contenido.replace("{n}", "eMQTTPort");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "MQTT port");
  contenido.replace("{v}", sysCfg.MQTTPort);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "eMQTTUser");
  contenido.replace("{n}", "eMQTTUser");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "MQTT User");
  contenido.replace("{v}", sysCfg.MQTTUser);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "pMQTTPassword");
  contenido.replace("{n}", "pMQTTPassword");
  contenido.replace("{t}", "password");
  contenido.replace("{p}", "MQTT Password");
  contenido.replace("{v}", sysCfg.MQTTPassword);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "eMQTTTopic");
  contenido.replace("{n}", "eMQTTTopic");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "Topic");
  contenido.replace("{v}", sysCfg.MQTTTopic);
  server.sendContent(contenido);
  server.sendContent_P(WB_CIERRE_DIV);

  server.sendContent("<div id='cfgadv' style='display:none'>");
  //Esto es para la config avanzada**************************************************
  server.sendContent_P(WB_FORM_ADV);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "sNodeName");
  contenido.replace("{n}", "sNodeName");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "Nombre del nodo");
  contenido.replace("{v}", sysCfg.nodeName);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM);
  contenido.replace("{i}", "sNodeSyslogHost");
  contenido.replace("{n}", "sNodeSyslogHost");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "Syslog Host");
  contenido.replace("{v}", sysCfg.nodeSyslogHost);
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_LOG);
  contenido.replace("{i}", "sNodeSysLogLevel");
  contenido.replace("{n}", "sNodeSysLogLevel");
  //contenido.replace("{t}", "text");
  contenido.replace("{p}", "Syslog Level");
  contenido.replace("{v}", String(sysCfg.nodeSysLogLevel ));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_LOG);
  contenido.replace("{i}", "sNodeSerialLogLevel");
  contenido.replace("{n}", "sNodeSerialLogLevel");
  //contenido.replace("{t}", "text");
  contenido.replace("{p}", "Serial Log level");
  contenido.replace("{v}", String(sysCfg.nodeSerialLogLevel));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_NUMBER);
  contenido.replace("{i}", "sNodeSendConfigInterval");
  contenido.replace("{n}", "sNodeSendConfigInterval");
  contenido.replace("{t}", "number");
  contenido.replace("{r}", "min='60000'");
  contenido.replace("{p}", "Send Config Interval (ms)");
  contenido.replace("{v}", String(sysCfg.nodeSendConfigInterval));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_NUMBER);
  contenido.replace("{i}", "sNodeSendDataInterval");
  contenido.replace("{n}", "sNodeSendDataInterval");
  contenido.replace("{t}", "number");
  contenido.replace("{r}", "min='1000'");
  contenido.replace("{p}", "Send Data Interval (ms)");
  contenido.replace("{v}", String(sysCfg.nodeSendDataInterval ));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_NUMBER);
  contenido.replace("{i}", "sNodeSendDataThreshold");
  contenido.replace("{n}", "sNodeSendDataThreshold");
  contenido.replace("{t}", "number");
  contenido.replace("{r}", "min='0' max='100'");
  contenido.replace("{p}", "Send Data Threshold");
  contenido.replace("{v}", String(sysCfg.nodeSendDataThreshold));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_NUMBER);
  contenido.replace("{i}", "sNodeSleepInterval");
  contenido.replace("{n}", "sNodeSleepInterval");
  contenido.replace("{t}", "number");
  contenido.replace("{r}", "min='0' max='10000'");
  contenido.replace("{p}", "Send Sleep Interval (s)");
  contenido.replace("{v}", String(sysCfg.nodeSleepInterval));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_SINO);
  contenido.replace("{i}", "updtWifi");
  contenido.replace("{n}", "updtWifi");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "Permitir actualiz. remotas de config Wifi");
  contenido.replace("{v}", String(sysCfg.updWifiConfigFromMQTT));
  server.sendContent(contenido);

  contenido = FPSTR(WB_FORM_PARAM_SINO);
  contenido.replace("{i}", "updtMqtt");
  contenido.replace("{n}", "updtMqtt");
  contenido.replace("{t}", "text");
  contenido.replace("{p}", "Permitir actualiz. remotas de config MQTT");
  contenido.replace("{v}", String(sysCfg.updMqttConfigFromMQTT));
  server.sendContent(contenido);

  server.sendContent_P(WB_CIERRE_DIV);

  server.sendContent_P(WB_NODE_CONF);
  sprintf_P(log, PSTR("Portal: Enviado fin del form"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);

  String contenido = F("<label><table style=\"width:100%\"><tr><td>Chip ID</td><td>");
  contenido += ESP.getChipId();
  contenido += F("</td></tr><tr><td>Flash ID</td><td>");
  contenido += ESP.getFlashChipId();
  contenido += F("</td></tr><tr><td>Soft AP MAC</td><td>");
  contenido += WiFi.softAPmacAddress();
  contenido += F("</td></tr><tr><td>Station MAC</td><td>");
  contenido += WiFi.macAddress();
  contenido += F("</td></tr><tr><td>Flash Size</td><td>");
  contenido += ESP.getFlashChipSize();
  contenido += F("</td></tr><tr><td>Soft AP IP</td><td>");
  contenido += WiFi.softAPIP().toString();
  contenido += F("</td></tr><tr><td>Version HW</td><td>");
  contenido += HW_VER;
  contenido += F("</td></tr><tr><td>Version FW <a href='/update'>(Actualizar)</a></td><td>");
  contenido += FW_VER;
  contenido += F("</td></tr><tr><td>Voltaje</td><td>");
  contenido += ESP.getVcc()/1024.00f;
  contenido += " Volts";
  contenido += F("</td></tr></table></label>");
  server.sendContent(contenido);

  server.sendContent_P(WB_CIERRE_DIV);
  server.sendContent_P(WB_CIERRE_DIV);//Este es el cierre del Div de la config avanzada

  sprintf_P(log, PSTR("Portal: Sended config end"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);
  server.sendContent_P(WB_LINK_ADV);
  //server.sendContent ("<Label><a href='#' onclick=\"if(document.getElementById('wifiadv').style.display=='none'){document.getElementById('wifiadv').style.display='block';}else{document.getElementById('wifiadv').style.display='none';}if(document.getElementById('cfgadv').style.display=='none'){document.getElementById('cfgadv').style.display='block';}else{document.getElementById('cfgadv').style.display='none';}\">Configuración avanzada</a></Label>");
  server.sendContent_P(WB_BUTT_SUBMIT);
  sprintf_P(log, PSTR("Portal: Enviado butt submit"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);

  server.sendContent_P("</form></div></body></html>");
  sprintf_P(log, PSTR("Portal: html end"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);

  server.client().stop();
  sprintf_P(log, PSTR("Portal: Sended client().Stop. End of page"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);
}

/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  char log[80];
  String value;
  sprintf_P(log, PSTR("Portal: Handle WifiSave"));
  addLog(LOG_LEVEL_DEBUG, log);

  //SAVE/connect here
  value = urldecode(server.arg("sWifiSSID1").c_str());
  value.toCharArray(sysCfg.WifiSSID1, value.length() + 1);

  value = urldecode(server.arg("pWifiPassword1").c_str());
  if (value.substring(0, 15) != String("PasswordProtect")) { //TODO: Cortamos a 15 por si los espacios
    value.toCharArray(sysCfg.WifiPassword, value.length() + 1);
  }

  value = urldecode(server.arg("sWifiSSID2").c_str());
  value.toCharArray(sysCfg.WifiSSID2, value.length() + 1);

  value = urldecode(server.arg("pWifiPassword2").c_str());
  if (value.substring(0, 15) != String("PasswordProtect")) { //TODO: Cortamos a 15 por si los espacios
    value.toCharArray(sysCfg.WifiPassword2, value.length() + 1);
  }

  value = urldecode(server.arg("sWifiSSID3").c_str());
  value.toCharArray(sysCfg.WifiSSID3, value.length() + 1);

  value = urldecode(server.arg("pWifiPassword3").c_str());
  if (value.substring(0, 15) != String("PasswordProtect")) { //TODO: Cortamos a 15 por si los espacios
    value.toCharArray(sysCfg.WifiPassword3, value.length() + 1);
  }

  value = urldecode(server.arg("eMQTTServer").c_str());
  value.toCharArray(sysCfg.MQTTServer, value.length() + 1);

  value = urldecode(server.arg("eMQTTPort").c_str());
  value.toCharArray(sysCfg.MQTTPort, value.length() + 1);

  value = urldecode(server.arg("eMQTTUser").c_str());
  value.toCharArray(sysCfg.MQTTUser, value.length() + 1);

  value = urldecode(server.arg("pMQTTPassword").c_str());
  value.toCharArray(sysCfg.MQTTPassword, value.length() + 1);

  value = urldecode(server.arg("eMQTTTopic").c_str());
  value.toCharArray(sysCfg.MQTTTopic, value.length() + 1);
  
  value = urldecode(server.arg("sNodeName").c_str());
  value.toCharArray(sysCfg.nodeName, value.length() + 1);

  value = urldecode(server.arg("sNodeSyslogHost").c_str());
  value.toCharArray(sysCfg.nodeSyslogHost, value.length() + 1);

  value = urldecode(server.arg("sNodeSysLogLevel").c_str());
  sysCfg.nodeSysLogLevel  = atoi(value.c_str());

  value = urldecode(server.arg("sNodeSerialLogLevel").c_str());
  sysCfg.nodeSerialLogLevel = atoi(value.c_str());

  value = urldecode(server.arg("sNodeSendConfigInterval").c_str());
  sysCfg.nodeSendConfigInterval = atoi(value.c_str());
if (sysCfg.nodeSendConfigInterval<60000){sysCfg.nodeSendConfigInterval=60000;}

  value = urldecode(server.arg("sNodeSendDataInterval").c_str());
  sysCfg.nodeSendDataInterval  = atoi(value.c_str());
  if (sysCfg.nodeSendDataInterval <1000){sysCfg.nodeSendDataInterval =1000;}

  value = urldecode(server.arg("sNodeSendDataThreshold").c_str());
  sysCfg.nodeSendDataThreshold = atoi(value.c_str());

  value = urldecode(server.arg("sNodeSleepInterval").c_str());
  sysCfg.nodeSleepInterval = atoi(value.c_str());

 value = urldecode(server.arg("updtWifi").c_str());
  sysCfg.updWifiConfigFromMQTT = atoi(value.c_str());
  
  value = urldecode(server.arg("updtMqtt").c_str());
  sysCfg.updMqttConfigFromMQTT = atoi(value.c_str());

  sysCfg.nextStartInitPortal = 0;
  //TODO: creo que no hace falta sysCfg.cfg_holder = CFG_HOLDER;
  //TODO: creo que no hace falta sysCfg.saveFlag++;
  CFG_Save();

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.

  String contenido = FPSTR(WB_HEAD);
  contenido.replace("{v}", "Credentials Saved");
  server.sendContent(contenido);
  server.sendContent_P(WB_SCRIPT);
  server.sendContent_P(WB_STYLE);
  server.sendContent_P(WB_HEAD_END);
  server.sendContent_P(WB_HEAD_TITLE2);
  server.sendContent_P(WB_SAVED);

  server.sendContent_P(WB_END);
  server.client().stop();
  sprintf_P(log, PSTR("Portal: Fin Handle WifiSave"));
  addLog(LOG_LEVEL_DEBUG, log);

  delay(5000);
  ESP.reset();
  //TODO: Como hacemos un reset mejor mirar si eliminamos todo el tema del connect
  //connect = true; //signal ready to connect/reset
}

/** Handle the reset page */
void handleReset() {
  char log[80];

  String contenido = FPSTR(WB_HEAD);
  contenido.replace("{v}", "Info");
  contenido += FPSTR(WB_SCRIPT);
  contenido += FPSTR(WB_STYLE);
  contenido += FPSTR(HTTP_HEAD_END);
  contenido += F("Module will reset in a few seconds.");
  contenido += FPSTR(HTTP_END);
  server.send(200, "text/html", contenido);

  //DEBUG_WM(F("Sent reset page"));
  sprintf_P(log, PSTR("Portal: Sent reset page"));
  addLog (LOG_LEVEL_INFO, log);
  delay(5000);
  ESP.reset();
  delay(2000);
}

void handleUpdateGet() {//OTA
  char log[80];
  //DEBUG_WM(F("HANDLE HANDLE UpdateGet"));
  sprintf_P(log, PSTR("OTA: Handle Update"));
  addLog(LOG_LEVEL_DEBUG, log);
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String contenido = FPSTR(WB_HEAD);
  contenido.replace("{v}", "Actualizacion de firmware");
  server.sendContent(contenido);
  server.sendContent_P(WB_SCRIPT);
  server.sendContent_P(WB_STYLE);
  server.sendContent_P(WB_HEAD_END);
  server.sendContent_P(WB_HEAD_TITLE3);
  server.sendContent_P(WB_FORM_UPLOAD);
  server.sendContent_P(WB_END);
  server.client().stop();
  sprintf_P(log, PSTR("OTA: FIN Handle UpdateGet"));
  addLog(LOG_LEVEL_DEBUG, log);

}

void handleUpdatePost() {//OTA
  char log[80];
  //DEBUG_WM("HANDLE UPDATEPOST");
  sprintf_P(log, PSTR("OTA: Handle Update Post"));
  addLog(LOG_LEVEL_DEBUG, log);
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String contenido = FPSTR(WB_HEAD);
  contenido.replace("{v}", "Resultado de la actualización");
  server.sendContent(contenido);
  server.sendContent_P(WB_SCRIPT);
  server.sendContent_P(WB_STYLE);
  server.sendContent_P(WB_HEAD_END);
  server.sendContent_P(WB_HEAD_TITLE3);
  if (endUpload) {
    server.sendContent_P(WB_UPGRADE_OK);
  }

  server.sendContent_P(WB_END);
  server.client().stop();
  ESP.reset();

}

void handleUpload() {//OTA
  char log[80];
  // handler for the file upload, get's the sketch bytes, and writes them through the Update object
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    //if (_serial_output)
    Serial.setDebugOutput(true);
    WiFiUDP::stopAll();
    sprintf_P(log, PSTR("OTA: Update filename-> %s"), upload.filename.c_str());
    addLog(LOG_LEVEL_INFO, log);
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
    if (!Update.begin(maxSketchSpace)) { //start with max available size
      if (sysCfg.nodeSerialLogLevel!=0) Update.printError(Serial); //TODO: mirar que hacemos con esto del debug
    }
  }
  else if (upload.status == UPLOAD_FILE_WRITE) {
    if (sysCfg.nodeSerialLogLevel!=0) Serial.printf(".");
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      if (sysCfg.nodeSerialLogLevel!=0) Update.printError(Serial);

    }
  }
  else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
      //if (_serial_output)
      sprintf_P(log, PSTR("\nOTA: Update Success. \nRebooting..."));
      addLog(LOG_LEVEL_INFO, log);
      //Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      endUpload = true;
    }
    else {
      if (sysCfg.nodeSerialLogLevel!=0) Update.printError(Serial);
    }
    //if (_serial_output)
    Serial.setDebugOutput(false);
  }
  else if (upload.status == UPLOAD_FILE_ABORTED) {
    Update.end();
    //DEBUG_WM("Update was aborted");
    sprintf_P(log, PSTR("OTA: Update was aborted"));
    addLog(LOG_LEVEL_INFO, log);

  }
  delay(0);
}

void handleNotFound() {
  char log[80];
  if (captivePortal()) { // If captive portal redirect instead of displaying the error page.
    return;
  }

  addLog(LOG_LEVEL_ERROR, "Portal: Recurso no encontrado");
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  sprintf_P(log, PSTR("Portal: recurso web no encontrado"));
  addLog(LOG_LEVEL_ERROR, log);

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send ( 404, "text/plain", message );
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
boolean captivePortal() {
  char log[80];
if (!isIp(server.hostHeader())) {
    sprintf_P(log, PSTR("Portal: Redirección al Captive portal"));
    addLog(LOG_LEVEL_DEBUG, log);
    Serial.print ("servidor al que redirige ");Serial.println (toStringIp(server.client().localIP()));
/*    server.sendHeader("Location", String("http://") + toStringIp(WiFi.softAPIP()), true);
    server.send (302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); */// Stop is needed because we sent no content length
    sprintf_P(log, PSTR("Portal: salida del Captive portal"));
    addLog(LOG_LEVEL_DEBUG, log);

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "<html><head><meta http-equiv=\"Refresh\" content=\"0;url=http://192.168.4.1\"></head></html>");
  server.client().stop();
  // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String head = FPSTR(WB_HEAD);
  head.replace("{v}", "Config ESP");
  server.sendContent(head);
    return true;
  }
  return false;
}

String urldecode(const char *src)
{
  String decoded = "";
  char a, b;
  while (*src) {
    if ((*src == '%') &&
        ((a = src[1]) && (b = src[2])) &&
        (isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
        a -= 'a' - 'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a' - 'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';

      decoded += char(16 * a + b);
      src += 3;
    } else if (*src == '+') {
      decoded += ' ';
      *src++;
    } else {
      decoded += *src;
      *src++;
    }
  }
  decoded += '\0';

  return decoded;
}

int getRSSIasQuality(int RSSI) {
  int quality = 0;

  if (RSSI <= -100) {
    quality = 0;
  } else if (RSSI >= -50) {
    quality = 100;
  } else {
    quality = 2 * (RSSI + 100);
  }
  return quality;
}
/** Is this an IP? */
boolean isIp(String str) {
  for (int i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}


