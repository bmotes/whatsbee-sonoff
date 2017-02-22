//const char NW_STYLE [] PROGMEM="<style>.fr{max-width:450px;padding:30px;margin:40px auto;background:#FFF;border-radius:10px;box-shadow:0 0 10px rgba(0,0,0,0.23);font:normal 18px Arial}.iw{padding:25px;background:#F8F8F8;border-radius:10px;margin-bottom:10px}.fr h1{background:#1ea213;padding:20px 30px 15px 95px;margin:-30px -30px 30px;border-radius:10px 10px 0 0;color:#fff;text-shadow:1px 1px 3px rgba(0,0,0,0.12);font:normal 30px Arial;box-shadow:inset 0 2px 2px 0 rgba(255,255,255,0.17);border:1px solid #257C9E}.fr h1 > span{display:block;margin-top:2px;font:13px Arial}.fr label{display:block;font-size:13px;color:#888;margin-bottom:4px;margin-top:15px}.fr input[type=text],.fr input[type=number],.fr input[type=password],.fr select{display:block;box-sizing:border-box;-moz-box-sizing:border-box;width:100%;padding:8px;border-radius:6px;border:2px solid #fff;box-shadow:inset 0 1px 1px rgba(0,0,0,0.33)}.fr .sc{font-size:20px;color:#1ea213;margin-bottom:5px;margin-left:20px}.sc span{background:#1ea213;padding:3px 8px;position:relative;border-radius:50%;font-size:14px;margin-left:-45px;color:#fff;margin-top:-3px;margin-right:10px;top:-2px}.fr .bs{width:150px;background:#1ea213;padding:8px 20px;border-radius:30px;color:#fff;font-size:18px;margin:2px}.bs:hover{background:#116D09}.iw{position:relative}.avanzado{display:none}.bt-av:hover{background:#116D09}.bt-av{width:70px;background:#1ea213;border-radius:10px;color:#fff;font-size:12px;position:absolute;botton:0;right:0}.ss{width:calc(100% - 30px)!important;display:inline!important}.modal{display:none;position:fixed;z-index:1;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:#000;background-color:rgba(0,0,0,0.4)}.modal-content{background-color:#fefefe;margin:5% auto;padding:5px;border:3px solid #116d09;width:90%;max-width:450px;}.close{color:#aaa;float:right;font-size:22px;font-weight:700}.close:hover{color:#000;text-decoration:none;cursor:pointer}.ib{width:27px;height:27px;background-color:#1ea213;color:#fff;display:inline;position:absolute;right:0;top:4px;border-radius:4px}.ib:hover{background-color:#116D09}.li{margin:10px}.li:hover{cursor:pointer}</Style>";
const char NW_STYLE [] PROGMEM="<style>.fr{max-width:450px;padding:30px;margin:40px auto;background:#FFF;border-radius:10px;box-shadow:0 0 10px rgba(0,0,0,0.23);font:normal 18px Arial}.iw{padding:25px;background:#F8F8F8;border-radius:10px;margin-bottom:10px}.fr h1{background:#1ea213;padding:20px 30px 15px 95px;margin:-30px -30px 30px;border-radius:10px 10px 0 0;color:#fff;text-shadow:1px 1px 3px rgba(0,0,0,0.12);font:normal 30px Arial;box-shadow:inset 0 2px 2px 0 rgba(255,255,255,0.17);border:1px solid #257C9E}.fr h1 > span{display:block;margin-top:2px;font:13px Arial}.fr label{display:block;font-size:13px;color:#888;margin-bottom:4px;margin-top:15px}.fr input[type=text],.fr input[type=number],.fr input[type=password],.fr select{display:block;box-sizing:border-box;-moz-box-sizing:border-box;width:100%;padding:8px;border-radius:6px;border:2px solid #fff;box-shadow:inset 0 1px 1px rgba(0,0,0,0.33)}.fr h3{font-size:20px;color:#1ea213;margin-bottom:5px;margin-left:20px}h3 span{background:#1ea213;padding:3px 8px;position:relative;border-radius:50%;font-size:14px;margin-left:-45px;color:#fff;margin-top:-3px;margin-right:10px;top:-2px}.fr .bs{width:150px;background:#1ea213;padding:8px 20px;border-radius:30px;color:#fff;font-size:18px;margin:2px}.bs:hover{background:#116D09}.iw{position:relative}.avanzado{display:none}.bt-av:hover{background:#116D09}.bt-av{width:70px;background:#1ea213;border-radius:10px;color:#fff;font-size:12px;position:absolute;botton:0;right:0}.ss{width:calc(100% - 30px)!important;display:inline!important}.modal{display:none;position:fixed;z-index:1;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:#000;background-color:rgba(0,0,0,0.4)}.modal-content{background-color:#fefefe;margin:5% auto;padding:5px;border:3px solid #116d09;width:90%;max-width:450px;}.close{color:#aaa;float:right;font-size:22px;font-weight:700}.close:hover{color:#000;text-decoration:none;cursor:pointer}.ib{width:27px;height:27px;background-color:#1ea213;color:#fff;display:inline;position:absolute;right:0;top:4px;border-radius:4px}.ib:hover{background-color:#116D09}.li{margin:10px}.li:hover{cursor:pointer}.wl{display:inline;margin:20px;color:grey;}</Style>";
const char NW_SCRIPT [] PROGMEM="<SCRIPT>function setAp(a,b){document.getElementById('mod').style.display='none',document.getElementById('WifiSSID'+b).value=a,document.getElementById('WifiPassword'+b).focus()}function adv(a,b){'block'==document.getElementById(a).style.display?(document.getElementById(a).style.display='none',document.getElementById(b).value='Avanzado'):(document.getElementById(a).style.display='block',document.getElementById(b).value='Básico')}function showWifi(a){modal=document.getElementById('mod'),modal.style.display='block',modal.value=a}</SCRIPT>";
const char NW_HEAD[] PROGMEM = "<!DOCTYPE html><html lang=\"es\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>{v}</title>";
const char NW_HEAD_END[] PROGMEM ="</head><body><div class='fr'><img style=\"position: absolute;margin: -20px;\" src=\"data:image/png;base64,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\"/>";
const char NW_HEAD_TITLE1[] PROGMEM = "<h1>Configura tu WhatsBee!!<span>Introduce a continuación los parámetros de configuración</span></h1>";
const char NW_MODAL_WIFI_OPEN[] PROGMEM = "<div id='mod' class='modal'><div class='modal-content'><span class='close' onclick=\"document.getElementById('mod').style.display='none'\">x</span><ul style='list-style-type:none;pading:10px;cursor:pointer'><li><p>Selecciona WiFi</p></li>";
const char NW_BUSCANDO_WIFI[] PROGMEM = "<div id='msg' style:'text-align: center; width:100%;'>Buscando redes WiFi</div><SCRIPT>document.body.style.cursor='wait'</SCRIPT>";
const char NW_OCULTAR_BUSCANDO_WIFI[] PROGMEM = "<SCRIPT>document.getElementById('msg').style.display = 'none'; document.body.style.cursor = ''</SCRIPT>";
//const char NW_MODAL_WIFI_ITEM[] PROGMEM = "<tr class='li' onclick=\"setAp('{n}', document.getElementById('mod').value);\"><td><label>{n}</label></td><td><label>{s}</label></td><td><label>{i}</label></td></tr>";
const char NW_MODAL_WIFI_ITEM[] PROGMEM = "<li onclick=\"setAp('{n}', document.getElementById('mod').value);\"><div class='wl'>{s}</div><div class='wl'>{n}</div><div class='wl'>{i}</div></li>";// <tr class='li' onclick=\"setAp('{n}', document.getElementById('mod').value);\"><td><label>{n}</label></td><td><label>{s}</label></td><td><label>{i}</label></td></tr>";
const char NW_MODAL_WIFI_CLOSE[] PROGMEM = "</ul></div></div>";
const char NW_FORM_INIT[] PROGMEM = "<form action='wifisave' method='post'>";
//const char NW_SECTION1[] PROGMEM = "<form action='wifisave' method='post'><div class='sc'><span>1</span>Configuración de la wifi</div><div class='iw'>";
//const char NW_SECTION1[] PROGMEM = "<div class='sc'><span>1</span>Configuración de la wifi</div><div class='iw'>";
const char NW_SECTION1[] PROGMEM = "<h3><span>1</span>Configuración de la wifi</h3><div class='iw'>";
const char NW_SECTION2[] PROGMEM = "<h3><span>2</span>Configuracion de WhatsBee</h3><div class='iw'>";
const char NW_SECTION3[] PROGMEM = "<h3><span>3</span>Configuracion de ubicación</h3><div class='iw'>";
const char NW_SECTION4[] PROGMEM = "<h3><span>4</span>Configuracion del sensor</h3><div class='iw'>";
const char NW_SECTION5[] PROGMEM = "<h3><span>5</span>Configuración avanzada y seguridad</h3><div class='iw'>";
const char NW_SECTION6[] PROGMEM = "<h3><span>6</span>Información y firmware</h3><div class='iw'>";
const char NW_INPUT_WIFI1[] PROGMEM = "<label for='WifiSSID{n}'>SSID {n}</label><div style='position: relative;'><div class='uiit wifi'><input class='ss' id='WifiSSID{n}' type='text' name='WifiSSID{n}' value='{sv}'/></div><button id='wb{n}' class='ib' type='button' onclick=\"showWifi({n});\">)))</button></div><label for='WifiPassword{n}'>Password {n}</label><div class='uiit'><input id='WifiPassword{n}' type='password' name='WifiPassword{n}' value='{pv}' /></div>";
const char NW_OPEN_DIV_ADV[] PROGMEM = "<div id='{id}'  class='avanzado'>";
const char NW_BUTTON_ADV[] PROGMEM = "<input class='bt-av' id='{n}' type='button' onclick=\"adv('{id}', '{n}');\" value='Avanzado'>";
//const char NW_FORM_PARAM[] PROGMEM = "<label for='{i}'>{p}</label><input id='{i}' type='{t}' name='{i}' value='{v}' />";
const char NW_FORM_PARAM[] PROGMEM = "<label for='{i}'>{p}</label><div class='uiit'><input id='{i}' type='{t}' name='{i}' {r} value='{v}' /></div>";
const char NW_FORM_PARAM_LOG[] PROGMEM ="<label for='{i}' class='select'>{p}</label><div class='ui-select'><select id='{i}' name='{i}'><option value='0'>None</option><option value='1'>Error</option><option value='2'>Info</option><option value='3'>Log</option><option value='4'>More log</option></select></div><script>document.getElementById(\"{i}\").value=\"{v}\";</script>";
const char NW_TABLE_INFO1[] PROGMEM ="<label><table style='width:100%'><tbody><tr><td>Identificador del dispositivo</td><td>{id}</td></tr></tbody></table></label>";
const char NW_SAVE_BUTTON[] PROGMEM ="<div class='ba'><input class='bs' type='submit' name='Guardar'>";
const char NW_PERMISSIONS[] PROGMEM ="<label><input type='checkbox' id='sec{n}' {c} name='sec{n}' value={v} />{t}<br /></label>";
const char NW_CIERRE_DIV[] PROGMEM = "</div>";

const char NW_HEAD_TITLE2[] PROGMEM = "<h1>Configura tu WhatsBee!!<span>Datos guardados!!</span></h1>";
const char NW_HEAD_TITLE3[] PROGMEM = "<h1>Configura tu WhatsBee!!<span>Actualización de firmware</span></h1>";
const char NW_SAVED [] PROGMEM = "<div><h2>La configuración ha sido guardada</h2><span><br />El dispositivo se intentará conectar a la WiFi que has configurado.<br />En el momento en el que se haya conectado el led parpadeará una vez cada tres segundos. Puedes entrar de nuevo en el AP de configuración pulsando el botón más de 4 segundos.</span></div>";
const char NW_END[] PROGMEM = "</div></body></html>";
const char NW_FORM_UPLOAD[] PROGMEM = "<form method='POST' action='/update' enctype='multipart/form-data'><input type = 'file' name = 'update'><input type = 'submit' value = 'Update'></form>";
const char NW_UPGRADE_OK[] PROGMEM = "Se ha completado la actualización de firmware, el dispositivo arrancará de nuevo en menos de un minuto.<script>setTimeout(function(){ window.location.href='http://192.168.4.1';}, 6000);</script>";

const char INPUT_TYPE_TEXT[] PROGMEM = "text";
const char INPUT_TYPE_NUMBER[] PROGMEM = "number";
const char INPUT_TYPE_PASSWORD[] PROGMEM = "password";

const char permisos_0[] PROGMEM = "Leer config de Wifi remotamente";
const char permisos_1[] PROGMEM = "Actualizar config de wifi remotamente";
const char permisos_2[] PROGMEM = "Leer confir de WhatsBee remotamente";
const char permisos_3[] PROGMEM = "Actualizar config de WhatsBee remotamente";
const char permisos_4[] PROGMEM = "Leer config de ubicación remotamente";
const char permisos_5[] PROGMEM = "Actualizar config de ubicación remotamente";
const char permisos_6[] PROGMEM = "Leer config del sensor remotamente";
const char permisos_7[] PROGMEM = "Actualizar config del sensor remotamente";
const char permisos_8[] PROGMEM = "Leer password del portal remotamente";
const char permisos_9[] PROGMEM = "Actualizar password del portal remotamente";
const char permisos_10[] PROGMEM = "Leer config de log remotamente";
const char permisos_11[] PROGMEM = "Actualizar config de log remotamente";
const char permisos_12[] PROGMEM = "Leer datos endpoints remotamente";
const char permisos_13[] PROGMEM = "Actualizar datos endpoints remotamente";
const char permisos_14[] PROGMEM = "Ejecutar comandos remotamente";
const char permisos_15[] PROGMEM = "Actualizar firmware remotamente";

const char* const perm_table[] PROGMEM = {permisos_0, permisos_1, permisos_2, permisos_3, permisos_4, permisos_5, permisos_6, permisos_7, permisos_8, permisos_9, permisos_10, permisos_11, permisos_12, permisos_13, permisos_14, permisos_15};

boolean       connect;
boolean       endUpload = false;//arreglar
unsigned long timeout = PORTAL_TIMEOUT;
unsigned long start = 0;
String        contenido;
boolean       appMovil = false;

/*Inicio del config portal*/
boolean  startConfigPortal(char const *apName, char const *apPassword) {//Inicia el Config Portal warning: unused parameter 'apName' [-Wunused-parameter]
  portalOn=true;
//  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
  connect = false;
  ledBlink (0.1, 0.05);
  setupConfigPortal();
  start=millis();
  
  while (timeout == 0 || (millis() < (start + timeout))) {//Este es al bucle de la web
    tipoPulsacion();//Para capturar la pulsacion de la interrupción
#if CAPTIVE_PORTAL
    dnsServer.processNextRequest(); //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
#endif
    server.handleClient(); //HTTP
    //TODO:Revisar lo de abajo, no sirve para nada
/*    if (connect) { //connect es el flag de que tiene que intentar conectar a un AP, se activa después de enviar el form de config
      connect = false;
      delay(2000);
      addLog(LOG_LEVEL_INFO, "Portal: Connecting to new AP");
      // using user-provided  _ssid, _pass in place of system-stored ssid and pass
      if (autoConnect(sysCfg.WifiSSID1, sysCfg.WifiPassword1) != WL_CONNECTED) {
        addLog(LOG_LEVEL_INFO, "Portal: Failed to connect");
      }//TODO: Hacer algo en este punto para que no se quede aqui.
      else { //Se ha conectado con la nueva configuración acabada de guardar
        WiFi.mode(WIFI_STA);
        portalOn=true;
        //TODO: verificar en este punto si es más razonable que solo salve si se conecta
        break;
      }
    }//Fin del connect*/
    yield();
  }//Fin del bucle
  portalOn=false;
  ESP.reset();
  //server.reset(); //No se para que sirve esto
  return  WiFi.status() == WL_CONNECTED;
}
/*Setup del config portal*/
void setupConfigPortal() {
  char log[80];
  char ip[16];
  portalOn=true;

#if CAPTIVE_PORTAL
  //dnsServer.reset(new DNSServer());   //NOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
  //server.reset(new ESP8266WebServer(80));
#endif

  start = millis();

  sprintf_P(log, PSTR("\nPORT: Configuring Access point %s"), ApSsid);
  addLog(LOG_LEVEL_INFO, log);
  WiFi.softAP(ApSsid, ApPassword);
  delay(500); // Without delay I've seen the IP address blank

  strcpy (ip, toStringIp(WiFi.softAPIP()).c_str());
  sprintf_P(log, PSTR("PORT: AP IP Adress %s"), ip);
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
  server.on("/appsave", &handleAppSave);
  server.on("/r", &handleReset);
  server.on("/update", HTTP_GET, &handleUpdateGet);//OTA
  server.on("/update", HTTP_POST, &handleUpdatePost, &handleUpload);//OTA
  server.onNotFound (&handleNotFound);
  server.begin(); // Web server start

  sprintf_P(log, PSTR("PORT: HTTP server started"));
  addLog(LOG_LEVEL_INFO, log);
}
//Página web de configuración
void handleWifi() {
  char log[80];
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }
  timeout=timeout*5;                    //Alguien ha entrado en la web, se amplia el tiempo
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String head = FPSTR(NW_HEAD);
  head.replace("{v}", "Config WhatsBee");
  server.sendContent(head);
  server.sendContent_P(NW_SCRIPT);
  server.sendContent_P(NW_STYLE);
  server.sendContent_P(NW_HEAD_END);
  server.sendContent_P(NW_HEAD_TITLE1);

//Escanea las redes wifi al alcance

  server.sendContent_P(NW_BUSCANDO_WIFI);
  server.sendContent_P(NW_MODAL_WIFI_OPEN);

    int n = WiFi.scanNetworks();
    sprintf_P(log, PSTR("PORT: Wifi Scan done"));
    addLog(LOG_LEVEL_INFO, log);
    if (n == 0) {
      sprintf_P(log, PSTR("PORT: No networks found."));
      addLog(LOG_LEVEL_ERROR, log);
      server.sendContent("No networks found. Refresh to scan again.");
    }
    else {
      String contenido;
      char log [80];
      char nomSSID[32];
      server.sendContent("<table>");
      for (int i = 0; i < n; ++i){
        WiFi.SSID(i).toCharArray (nomSSID, WiFi.SSID(i).length() + 1);
        sprintf_P(log, PSTR("PORT: SSID-> %s %d dB"), nomSSID, WiFi.RSSI(i));
        addLog(LOG_LEVEL_INFO, log);
        //PRUEBA int quality = getRSSIasQuality(WiFi.RSSI(i));
        String item = FPSTR(NW_MODAL_WIFI_ITEM);
        //PRUEBA  String rssiQ;
        //  rssiQ += quality;
          item.replace("{n}", WiFi.SSID(i));
          item.replace("{s}", String(WiFi.RSSI(i))+ String (" dB"));
          if (WiFi.encryptionType(i) != ENC_TYPE_NONE) {
            item.replace("{i}", "");
          }
          else {
            item.replace("{i}", "OPEN");
          }
          //contenido += item;
          server.sendContent (item);
          delay(0);
      }
      server.sendContent("</table>");
   
      sprintf_P(log, PSTR("PORT: Send AP list"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
      //server.sendContent(contenido);
      server.sendContent("<br/>"); //TODO, es necesario????
      sprintf_P(log, PSTR("PORT: AP list sended"));
      addLog(LOG_LEVEL_DEBUG_MORE, log);
    }

  server.sendContent_P(NW_MODAL_WIFI_CLOSE);
    sprintf_P(log, PSTR("PORT: Send form init"));
    addLog(LOG_LEVEL_DEBUG_MORE, log);
//Lista la parte del modal de las wifis
  server.sendContent_P (NW_OCULTAR_BUSCANDO_WIFI);
  server.sendContent_P(NW_FORM_INIT);

//Seccion 1 Configuración de WiFi
  server.sendContent_P(NW_SECTION1);
  server.sendContent(webWifi (FPSTR(NW_INPUT_WIFI1), "1",String(sysCfg.WifiSSID1), passwordProtect(sysCfg.WifiPassword1)));
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), "wi-ad",""));
  server.sendContent(webWifi (FPSTR(NW_INPUT_WIFI1), "2",String(sysCfg.WifiSSID2), passwordProtect(sysCfg.WifiPassword2)));
  server.sendContent(webWifi (FPSTR(NW_INPUT_WIFI1), "3",String(sysCfg.WifiSSID3), passwordProtect(sysCfg.WifiPassword3)));
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), "wi-ad","1"));
  server.sendContent_P(NW_CIERRE_DIV);

//Seccion 2 Configuración de WhatsBee
  server.sendContent_P(NW_SECTION2);
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), "mq-ad",""));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("MqttServer"), FPSTR(INPUT_TYPE_TEXT), "", F("Servidor WhatsBee"), String(sysCfg.MqttServer)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("MqttPort"), FPSTR(INPUT_TYPE_TEXT), "", F("Puerto del servidor WhatsBee"), String(sysCfg.MqttPort)));
  server.sendContent_P(NW_CIERRE_DIV); //Cierre advanced
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("MqttUser"), FPSTR(INPUT_TYPE_TEXT), "", F("Nombre de usuario de WhatsBee"), String(sysCfg.MqttUser)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("MqttPassword"), FPSTR(INPUT_TYPE_PASSWORD), "", F("Password de WhatsBee"), String(passwordProtect(sysCfg.MqttPassword))));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("MqttTopic"), FPSTR(INPUT_TYPE_TEXT), "", F("Topic principal en WhatsBee"), String(sysCfg.MqttTopic)));
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), F("mq-ad"),"2"));
  server.sendContent_P(NW_CIERRE_DIV);
  
//Sección 3 Configuración de ubicación
  server.sendContent_P(NW_SECTION3);
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("NodeName"), FPSTR(INPUT_TYPE_TEXT), "", F("Nombre del nodo"), String(sysCfg.NodeName)));
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), F("no-ad"),""));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("NodeType"), FPSTR(INPUT_TYPE_TEXT), "", F("Tipo de nodo"), String(sysCfg.NodeType)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("NodeDescr"), FPSTR(INPUT_TYPE_TEXT), "", F("Descripción"), String(sysCfg.NodeDescr)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("AdminName"), FPSTR(INPUT_TYPE_TEXT), "", F("Nombre administrador"), String(sysCfg.AdminName)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("AdminMail"), FPSTR(INPUT_TYPE_TEXT), "", F("eMail de contacto"), String(sysCfg.AdminMail)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("AdminAddress"), FPSTR(INPUT_TYPE_TEXT), "", F("Ubicación"), String(sysCfg.AdminAddress)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("NodeLat"), FPSTR(INPUT_TYPE_TEXT), "", F("Coordenada latitud"), String(sysCfg.NodeLat)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("NodeLon"), FPSTR(INPUT_TYPE_TEXT), "", F("Coordenada Longitud"), String(sysCfg.NodeLon)));
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), "no-ad","3"));
  server.sendContent_P(NW_CIERRE_DIV);

//Sección 3 Configuración del sensor
  server.sendContent_P(NW_SECTION4);

//########################ESPECIFICO DEL NODO (INPUTS WEB - BASICOS)##################

//####################################################################################

  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("SendDataInterval"), FPSTR(INPUT_TYPE_NUMBER), F("min='1000'"), F("Intervalo de envio de datos (ms > 1000)"), String(sysCfg.SendDataInterval)));
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), F("da-ad"),""));
//########################ESPECIFICO DEL NODO (INPUTS WEB - AVANZADOS)##################

//######################################################################################
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("SendConfigInterval"), FPSTR(INPUT_TYPE_NUMBER), F("min='60000'"), F("Intervalo de envio de config (ms > 60000)"), String(sysCfg.SendConfigInterval)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("ReadSensorInterval"), FPSTR(INPUT_TYPE_NUMBER), F("min='1000'"), F("Intervalo de lectura del sensor (ms > 1000)"), String(sysCfg.ReadSensorInterval)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("SleepInterval"), FPSTR(INPUT_TYPE_NUMBER), F("min='0'"), F("Intervalo sleep (ms)"), String(sysCfg.SleepInterval)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("SendDataThreshold"), FPSTR(INPUT_TYPE_NUMBER), F("min='0' max='100'"), F("Umbral de datos (% 0 > 100)"), String(sysCfg.SendDataThreshold)));
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), F("da-ad"),"4"));
  server.sendContent_P(NW_CIERRE_DIV);

//Seccion 5 Configuracion avanzada y seguridad
  server.sendContent_P(NW_SECTION5);
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("APPassword"), FPSTR(INPUT_TYPE_PASSWORD), "", F("Password del portal"), passwordProtect(sysCfg.APPassword)));
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), F("se-ad"),""));
  server.sendContent ("<label>Permisos sobre el dispositivo</label>");
    for (int n=0; n<16; n++){
      char buffer[45];
      strcpy_P(buffer, (char*)pgm_read_dword(&(perm_table[n])));
      String checked;
      int ch=bitRead (sysCfg.Permissions, n);
      if (ch){checked="checked";}
      double va =pow (2, n);
      String value=String(va, 0);
      contenido= FPSTR(NW_PERMISSIONS);
      contenido.replace("{c}", checked);
      contenido.replace("{v}", value);
      contenido.replace("{t}", String(buffer));//permisos[n]);
      contenido.replace("{n}", String(n));
      
      //if (String(permisos[n])!=""){
        if (String(buffer)!=String("")){
        server.sendContent(contenido);
        }
  }
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM), F("SysLogHost"), FPSTR(INPUT_TYPE_TEXT), "", F("Syslog Host"), String(sysCfg.SysLogHost)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM_LOG), F("SysLogLevel"), FPSTR(INPUT_TYPE_TEXT), "", F("Syslog Level"), String(sysCfg.SysLogLevel)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM_LOG), F("SerialLogLevel"), FPSTR(INPUT_TYPE_TEXT), "", F("Serial Log level"), String(sysCfg.SerialLogLevel)));
  server.sendContent(webParam(FPSTR(NW_FORM_PARAM_LOG), F("MqttLogLevel"), FPSTR(INPUT_TYPE_TEXT), "", F("MQTT Log level"), String(sysCfg.MqttLogLevel)));
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), F("se-ad"),"5"));
  server.sendContent_P(NW_CIERRE_DIV);

//Seccion 5 Configuracion avanzada y seguridad
  server.sendContent_P(NW_SECTION6);
  contenido = FPSTR(NW_TABLE_INFO1);
  contenido.replace("{id}", getUniqueId());
  server.sendContent(contenido);
  server.sendContent(webAdv (FPSTR(NW_OPEN_DIV_ADV), "in-ad",""));
  String contenido = F("<label><table style=\"width:100%\"><tr><td>Flash ID</td><td>");
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
  contenido += F("</td></tr><tr><td colspan='2'>Motivo por el que se inicia el portal</td></tr><tr><td colspan='2'>");
  contenido += sysCfg.PortalReason;
  contenido +=F("</td></tr></table></label>");
  server.sendContent(contenido);
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent(webAdv (FPSTR(NW_BUTTON_ADV), F("in-ad"),"6"));
  server.sendContent_P(NW_CIERRE_DIV);

//Boton de salvar y cierre, etc.
  server.sendContent_P(NW_SAVE_BUTTON);
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent ("</form>");
  server.sendContent_P(NW_CIERRE_DIV);
  server.sendContent ("</body></html>");

  server.client().stop();
    sprintf_P(log, PSTR("PORT: End of page"));
    addLog(LOG_LEVEL_DEBUG_MORE, log);
}

void handleAppSave (){
  appMovil=true;
  handleWifiSave();
  }

/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  char log[80];
  String value;
  sprintf_P(log, PSTR("PORT:Start handleWifiSave"));
  addLog(LOG_LEVEL_DEBUG, log);

  //SAVE/connect here
  value = urldecode(server.arg("WifiSSID1").c_str());
  setGetCfg (sysCfg.WifiSSID1, value.substring(0, sizeof(sysCfg.WifiSSID1)), 0, PERM_ALL, String("WifiSSID1"), String("set"));

  value = urldecode(server.arg("WifiPassword1").c_str());
  if (value.substring(0, 20) != String(HIDDEN_PASSWORD)) { //TODO: Cortamos a 20 por si los espacios
    setGetCfg (sysCfg.WifiPassword1, value.substring(0, sizeof(sysCfg.WifiPassword1)), 0, PERM_ALL, String("WifiPassword1"), String("set"));
  }

  value = urldecode(server.arg("WifiSSID2").c_str());
  setGetCfg (sysCfg.WifiSSID2, value.substring(0, sizeof(sysCfg.WifiSSID2)), 0, PERM_ALL, String("WifiSSID2"), String("set"));

  value = urldecode(server.arg("WifiPassword2").c_str());
  if (value.substring(0, 20) != String(HIDDEN_PASSWORD)) { //TODO: Cortamos a 20 por si los espacios
    setGetCfg (sysCfg.WifiPassword2, value.substring(0, sizeof(sysCfg.WifiPassword2)), 0, PERM_ALL, String("WifiPassword2"), String("set"));
  }

  value = urldecode(server.arg("WifiSSID3").c_str());
  setGetCfg (sysCfg.WifiSSID3, value.substring(0, sizeof(sysCfg.WifiSSID3)), 0, PERM_ALL, String("WifiSSID3"), String("set"));

  value = urldecode(server.arg("WifiPassword3").c_str());
  if (value.substring(0, 20) != String(HIDDEN_PASSWORD)) { //TODO: Cortamos a 20 por si los espacios
    setGetCfg (sysCfg.WifiPassword3, value.substring(0, sizeof(sysCfg.WifiPassword3)), 0, PERM_ALL, String("WifiPassword3"), String("set"));
  }

  value = urldecode(server.arg("MqttServer").c_str());
  setGetCfg (sysCfg.MqttServer, value.substring(0, sizeof(sysCfg.MqttServer)), 0, PERM_ALL, String("MqttServer"), String("set"));

  value = urldecode(server.arg("MqttPort").c_str());
  setGetCfg (sysCfg.MqttPort, value.substring(0, sizeof(sysCfg.MqttPort)), 0, PERM_ALL, String("MqttPort"), String("set"));

  value = urldecode(server.arg("MqttUser").c_str());
  setGetCfg (sysCfg.MqttUser, value.substring(0, sizeof(sysCfg.MqttUser)), 0, PERM_ALL, String("MqttUser"), String("set"));

  value = urldecode(server.arg("MqttPassword").c_str());
    if (value.substring(0, 20) != String(HIDDEN_PASSWORD)) { //TODO: Cortamos a 20 por si los espacios
      setGetCfg (sysCfg.MqttPassword, value.substring(0, sizeof(sysCfg.MqttPassword)), 0, PERM_ALL, String("MqttPassword"), String("set"));
  }

  value = urldecode(server.arg("MqttTopic").c_str());
  setGetCfg (sysCfg.MqttTopic, value.substring(0, sizeof(sysCfg.MqttTopic)), 0, PERM_ALL, String("MqttTopic"), String("set"));
  
  value = urldecode(server.arg("NodeName").c_str());
  setGetCfg (sysCfg.NodeName, value.substring(0, sizeof(sysCfg.NodeName)), 0, PERM_ALL, String("NodeName"), String("set"));

  value = urldecode(server.arg("NodeType").c_str());
  setGetCfg (sysCfg.NodeType, value.substring(0, sizeof(sysCfg.NodeType)), 0, PERM_ALL, String("NodeType"), String("set"));

  value = urldecode(server.arg("AdminName").c_str());
  setGetCfg (sysCfg.AdminName, value.substring(0, sizeof(sysCfg.AdminName)), 0, PERM_ALL, String("AdminName"), String("set"));

  value = urldecode(server.arg("AdminAddress").c_str());
  setGetCfg (sysCfg.AdminAddress, value.substring(0, sizeof(sysCfg.AdminAddress)), 0, PERM_ALL, String("AdminAddress"), String("set"));

  value = urldecode(server.arg("AdminMail").c_str());
  setGetCfg (sysCfg.AdminMail, value.substring(0, sizeof(sysCfg.AdminMail)), 0, PERM_ALL, String("AdminMail"), String("set"));

  value = urldecode(server.arg("NodeDescr").c_str());
  setGetCfg (sysCfg.NodeDescr, value.substring(0, sizeof(sysCfg.NodeDescr)), 0, PERM_ALL, String("NodeDescr"), String("set"));
  
  value = urldecode(server.arg("NodeLat").c_str());
  setGetCfg (sysCfg.NodeLat, value.substring(0, sizeof(sysCfg.NodeLat)), 0, PERM_ALL, String("NodeLat"), String("set"));

  value = urldecode(server.arg("NodeLon").c_str());
  setGetCfg (sysCfg.NodeLon, value.substring(0, sizeof(sysCfg.NodeLon)), 0, PERM_ALL, String("NodeLon"), String("set"));

  value = urldecode(server.arg("SendConfigInterval").c_str());
  setGetCfg (sysCfg.SendConfigInterval, atof(value.c_str()), 0, PERM_ALL, String("SendConfigInterval"), String("set"));

  value = urldecode(server.arg("SendDataInterval").c_str());
  setGetCfg (sysCfg.SendDataInterval, atof(value.c_str()), 0, PERM_ALL, String("SendDataInterval"), String("set"));

  value = urldecode(server.arg("SendDataThreshold").c_str());
  setGetCfg (sysCfg.SendDataThreshold, atof(value.c_str()), 0, PERM_ALL, String("SendDataThreshold"), String("set"));

  value = urldecode(server.arg("SleepInterval").c_str());
  setGetCfg (sysCfg.SleepInterval, atof(value.c_str()), 0, PERM_ALL, String("SleepInterval"), String("set"));

  value = urldecode(server.arg("ReadSensorInterval").c_str());
  setGetCfg (sysCfg.ReadSensorInterval, atof(value.c_str()), 0, PERM_ALL, String("ReadSensorInterval"), String("set"));

//########################ESPECIFICO DEL NODO (INPUTS WEB - BAS AVAN)##################

  
//####################################################################################

  value = urldecode(server.arg("SysLogHost").c_str());
  setGetCfg (sysCfg.SysLogHost, value.substring(0, sizeof(sysCfg.SysLogHost)), 0, PERM_ALL, String("SysLogHost"), String("set"));

  value = urldecode(server.arg("SysLogLevel").c_str());
  setGetCfg (sysCfg.SysLogLevel, atoi(value.c_str()), 0, PERM_ALL, String("SysLogLevel"), String("set"));

  value = urldecode(server.arg("SerialLogLevel").c_str());
  setGetCfg (sysCfg.SerialLogLevel, atoi(value.c_str()), 0, PERM_ALL, String("SerialLogLevel"), String("set"));

  value = urldecode(server.arg("MqttLogLevel").c_str());
  setGetCfg (sysCfg.MqttLogLevel, atoi(value.c_str()), 0, PERM_ALL, String("MqttLogLevel"), String("set"));

  value = urldecode(server.arg("APPassword").c_str());
    if (value.substring(0, 20) != String(HIDDEN_PASSWORD)) { //TODO: Cortamos a 20 por si los espacios
      setGetCfg (sysCfg.APPassword, value.substring(0, sizeof(sysCfg.APPassword)), 0, PERM_ALL, String("APPassword"), String("set"));
    }

  //REC COMP  int valueInt;
  unsigned long valorSec=0;
  for (int n=0; n< 16; n++){
    String arg = String("sec")+String (n);
  value = urldecode(server.arg(arg).c_str());
  if (value!=String("")){
    valorSec=valorSec + atoi(value.c_str());
  }
 }
  sysCfg.Permissions =valorSec;

  sysCfg.NextStartInitPortal = 0;

  CFG_Save();
  
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  /* si el post se hace desde la app móvil no se devuelve el html, en su lugar se devuelve un OK*/
  if (appMovil){
  server.setContentLength(8);
  server.send(200, "text/html", "SAVED:OK");
  }
  else{
      server.setContentLength(CONTENT_LENGTH_UNKNOWN);
      server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  }
  String contenido = FPSTR(NW_HEAD);
  contenido.replace("{v}", "Credentials Saved");
  server.sendContent(contenido);
  server.sendContent_P(NW_SCRIPT);
  server.sendContent_P(NW_STYLE);
  server.sendContent_P(NW_HEAD_END);
  server.sendContent_P(NW_HEAD_TITLE2);
  server.sendContent_P(NW_SAVED );

  server.sendContent_P(NW_END);
  server.client().stop();
  sprintf_P(log, PSTR("PORT:End HandleWifiSave"));
  addLog(LOG_LEVEL_DEBUG_MORE, log);

  delay(3000);
  ESP.reset();
}
/** Handle the reset page */
void handleReset() {
  char log[80];

  String contenido = FPSTR(NW_HEAD);
  contenido.replace("{v}", "Info");
  contenido += FPSTR(NW_SCRIPT);
  contenido += FPSTR(NW_STYLE);
  contenido += FPSTR(NW_HEAD_END);
  contenido += F("Module will reset in a few seconds.");
  contenido += FPSTR(NW_END);
  server.send(200, "text/html", contenido);

  //DEBUG_WM(F("Sent reset page"));
  sprintf_P(log, PSTR("PORT: Sent reset page"));
  addLog (LOG_LEVEL_INFO, log);
  delay(5000);
  ESP.reset();
  delay(2000);
}
/*OTA*/
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

  String contenido = FPSTR(NW_HEAD);
  contenido.replace("{v}", "Actualizacion de firmware");
  server.sendContent(contenido);
  server.sendContent_P(NW_SCRIPT);
  server.sendContent_P(NW_STYLE);
  server.sendContent_P(NW_HEAD_END);
  server.sendContent_P(NW_HEAD_TITLE3);
  server.sendContent_P(NW_FORM_UPLOAD);
  server.sendContent_P(NW_END);
  server.client().stop();
  sprintf_P(log, PSTR("OTA: FIN Handle UpdateGet"));
  addLog(LOG_LEVEL_DEBUG, log);

}
/*OTA*/
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

  String contenido = FPSTR(NW_HEAD);
  contenido.replace("{v}", "Resultado de la actualización");
  server.sendContent(contenido);
  server.sendContent_P(NW_SCRIPT);
  server.sendContent_P(NW_STYLE);
  server.sendContent_P(NW_HEAD_END);
  server.sendContent_P(NW_HEAD_TITLE3);
  if (endUpload) {
    server.sendContent_P(NW_UPGRADE_OK);
  }

  server.sendContent_P(NW_END);
  server.client().stop();
  ESP.reset();

}
/*OTA*/
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
      if (sysCfg.SerialLogLevel!=0) Update.printError(Serial); //TODO: mirar que hacemos con esto del debug
    }
  }
  else if (upload.status == UPLOAD_FILE_WRITE) {
    if (sysCfg.SerialLogLevel!=0) Serial.printf(".");
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      if (sysCfg.SerialLogLevel!=0) Update.printError(Serial);

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
      if (sysCfg.SerialLogLevel!=0) Update.printError(Serial);
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
/*Manejador de página que no existe*/
void handleNotFound() {
  char log[80];
  if (captivePortal()) { // If captive portal redirect instead of displaying the error page.
    return;
  }

  addLog(LOG_LEVEL_ERROR, "PORT:Start handleNotFound");
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  sprintf_P(log, PSTR("PORT:Non existent resour"));
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
  //REC COMP  char log[80];
/*if (!isIp(server.hostHeader())) {
    sprintf_P(log, PSTR("PORT: Redirección al Captive portal"));
    addLog(LOG_LEVEL_DEBUG, log);
    Serial.print ("servidor al que redirige ");Serial.println (toStringIp(server.client().localIP()));
    server.sendHeader("Location", String("http://") + toStringIp(WiFi.softAPIP()), true);
    server.send (302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    sprintf_P(log, PSTR("PORT: salida del Captive portal"));
    addLog(LOG_LEVEL_DEBUG, log);

//server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "<html><head><meta http-equiv=\"Refresh\" content=\"0;url=http://192.168.4.1\"></head></html>");
  server.client().stop();*/
  // Empty content inhibits Content-length header so we have to close the socket ourselves.
/*  server.setContentLength(CONTENT_LENGTH_UNKNOWN);

  String head = FPSTR(NW_HEAD);
  head.replace("{v}", "Config ESP");
  server.sendContent(head);
    return true;
  }
  return false;
}*/
  if (!isIp(server.hostHeader())) {
    Serial.print("Request redirected to captive portal");
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send ( 302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    return true;
  }
  return false;
}
/* para hacer updates de firmware por http*/
void httpLoopOTA(String firmwareFile){
char log[80];
         t_httpUpdate_return ret = ESPhttpUpdate.update("www.whatsbee.net", 80, "/FW_UPDATES/" + String (HW_VER) + String ("/") + firmwareFile);
        switch(ret) {
            case HTTP_UPDATE_FAILED:
            sprintf_P(log, PSTR("OTA: HTTP_UPDATE_FAILD Error (%d): %s"), ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            addLog(LOG_LEVEL_ERROR, log);
            httpOTA = false;
                break;
            case HTTP_UPDATE_NO_UPDATES:
            sprintf_P(log, PSTR("OTA: HTTP_UPDATE_NO_UPDATES"));
            addLog(LOG_LEVEL_DEBUG, log);
            httpOTA = false;
                break;
            case HTTP_UPDATE_OK:
            sprintf_P(log, PSTR("OTA: HTTP_UPDATE_OK"));
            addLog(LOG_LEVEL_DEBUG, log);
                break;
        }
}
/* actualizacion de FW por http*/
int upgradeFW(String firmwareFile){  //TODO: warning: no return statement in function returning non-void [-Wreturn-type]
    char log[80];
//TODO:Hacer aqui las comprobaciones necesarias
    sprintf_P(log, PSTR("OTA: FW upgrade requ. From-> %s to File-> %s"), FW_VER, firmwareFile.c_str());
    addLog(LOG_LEVEL_INFO, log);
    while (httpOTA){
      httpLoopOTA(firmwareFile);
    }
}
/*decode url*/
String urldecode(const char *src){
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
      *src++;  //TODO: warning: value computed is not used [-Wunused-value]
    } else {
      decoded += *src;
      *src++;  //TODO  warning: value computed is not used [-Wunused-value]
    }
  }
  decoded += '\0';
  return decoded;
}
/*Averigua la calidad de la conexión wifi*/
/*int getRSSIasQuality(int RSSI) {
  int quality = 0;

  if (RSSI <= -100) {
    quality = 0;
  } else if (RSSI >= -50) {
    quality = 100;
  } else {
    quality = 2 * (RSSI + 100);
  }
  return quality;
}*/
/** Devuelve true si es una IP */
boolean isIp(String str) {
  for (unsigned int i = 0; i < str.length(); i++) { //TODO: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}
/** Convierte una IP en una String */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
//construye un parametro de la web
String webParam(String control, String id, String typeControl, String typeMore, String caption, String value){
String cont=control;
  cont = control; //Sleep
  cont.replace("{i}", id);
  cont.replace("{t}", typeControl);
  cont.replace("{r}", typeMore);
  cont.replace("{p}", caption);
  cont.replace("{v}", value);
  return cont; 
}
//construye un <div> de avanzado
String webAdv (String control, String section, String number){
  String cont=control;
  cont.replace("{id}", section);
  cont.replace("{n}", number);
  return cont;  
}
//construye un botón de avanzado
String webWifi (String control, String number, String ssid, String password){
  String cont = control;
  cont.replace("{n}", number);   
  cont.replace("{sv}", ssid);
  cont.replace("{pv}", password); 
  return cont;
}

