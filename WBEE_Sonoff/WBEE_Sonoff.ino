//TODO: si no responde el servidor MQTT no lo detecta.
//TODO:Cuando empiezas a editar el portal que se pare el contagdor de tiempo
//OJO, modificar en la librería el valor de #define MQTT_BUFFER_SIZE 512 de 128 a 512
//TODO: cuando se salven nuevas credenciales de wifi en la web hay que poner una marca para que no use las cacheadas.
//TODO: Despues de la configuración inicial no conecta si no se resetea


//V4.1 Se añade el comando para pedir al nodo que mande la config.
//V4.2 Se normalizan los comandos de configuración

ADC_MODE(ADC_VCC);

#define CON_SSL           true             //Compilar con TSL/SSL
#define HW_VER            "SONOFF"         //VERSION DEL HW
#define CAPTIVE_PORTAL    false            //Se instala el DNS para elportal cautivo

  #if CON_SSL
    #define FW_VER            "5.3 SSL"            //VERSION DEL FW
  #else
    #define FW_VER            "5.3"            //VERSION DEL FW
  #endif

#define LED               16               //El led que se va a utilizar para parpadear 13 sonoff, 16 amica
#define BUTTON            0                //El botón que se utiliza para entrar en la config
#define RELE              12               //El Relé
#define INIT_PORTAL_TIME  4000             //Tiempo mínimo (ms) que se tiene que pulsar el botón para que inicie el ConfigPortal
#define DUTTY_CYCLE_LED 10 //el dutty del LED
#define DEF_INTERVAL "60" //El intervalo por defecto para el envio de topics

#define LOG_LEVEL_NONE         0
#define LOG_LEVEL_ERROR        1
#define LOG_LEVEL_INFO         2
#define LOG_LEVEL_DEBUG        3
#define LOG_LEVEL_DEBUG_MORE   4
#define SYS_LOG_HOST           "192.168.29.134"
#define SYS_LOG_PORT           514
#define SYS_LOG_LEVEL          LOG_LEVEL_NONE
#define SERIAL_LOG_LEVEL       LOG_LEVEL_DEBUG
#define SERIAL_IO              true
#define UPD_WIFI_CFG_FROM_MQTT 1
#define UPD_MQTT_CFG_FROM_MQTT 1
#define CFG_HOLDER             0x20160314   // Change this value to load default configurations

#define MQTT_SERVER            "www.whatsbee.net"

  #if CON_SSL
    #define MQTT_PORT              "8883"
  #else
    #define MQTT_PORT              "1883"
  #endif

#define MQTT_CLIENT_ID         "SONOFF_%06X"  // Also fall back topic using Chip Id = last 6 characters of MAC address
#define MQTT_USER              ""
#define MQTT_PASSWORD          ""
#define MQTT_GRPTOPIC          "SONOFFs"   // Group topic
#define MQTT_TOPIC             "SONOFF"
#define MQTT_CONN_RETRYS 20       //Número máximo de intentos de conexión a MQTT

#define STA_SSID               "WhatsBee"
#define STA_PASS               "XXXX"
#define WIFI_HOSTNAME          "WhatsBee-%06x-%s"

#define NODE_NAME               "unconfigured"
#define NODE_TYPE               HW_VER

#define APP_TIMEZONE           1            // +1 hour (Amsterdam)
#define APP_POWER              0            // Saved power state Off
#define TIMEOUT                3000000          //Tiempo en milisegundos que está activo el portal

  #ifdef DEBUG_ESP_PORT
    #define DEBUG_MSG(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
  #else
    #define DEBUG_MSG(...)
  #endif

#define WIFI_BEGIN_TIMEOUT  8000      //Tiempo máximo (ms) para intentar conectarse con las credenciales almacenadas.
#define WIFI_BEGIN_CRED_TIMEOUT 20000 //Tiempo máximo (ms) para intentar conectarse con las credenciales almacenadas.
#define SEND_CONFIG_TIME 3600000     //Tiempo en el que envia los datos de config del nodo (ms)
#define SEND_DATA_TIME 60000         //Tiempo en el que envia los datos del topic
#define SEND_DATA_THRESHOLD 0        //Porcentajde de diferencia para enviar los datos o no
#define NODE_SLEEP 0                 //Indica si el nodo duerme

#if CAPTIVE_PORTAL
  #include <DNSServer.h>              //XXNOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
  #define DNS_PORT 53 //El puerto del DNS
#endif

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Ticker.h> //for LED status
#include <MQTTClient.h> //para la conexión a MQTT

Ticker enciendeLed;
Ticker apagaLed;
ESP8266WiFiMulti wifiMulti;     //Librería Wifi para permitir la conexión a una lista de APS
WiFiUDP portUDP;                //Necesarsio para el sysLog
  #if CAPTIVE_PORTAL
    DNSServer dnsServer;          //Servidor DNS si se utiliza el portal cautivo
  #endif

  #if CON_SSL
    WiFiClientSecure secureClient;//Cliente de wifi
  #else
    WiFiClient secureClient;      //Cliente de wifi
  #endif

ESP8266WebServer server (80);   //Cliente de wifi
MQTTClient mqttClient;          //Cliente MQTT

struct SYSCFG {                 //Almacena la configuración
  unsigned long cfg_holder;
  unsigned long saveFlag;
  byte          nodeSerialLogLevel;
  byte          nodeSysLogLevel ;
  char          nodeSyslogHost[32];
  char          WifiSSID1[32];
  char          WifiPassword[64];
  char          WifiSSID2[32];
  char          WifiPassword2[64];
  char          WifiSSID3[32];
  char          WifiPassword3[64];
  char          MQTTServer[32];
  char          MQTTPort[5];
  char          MQTTUser[32];
  char          MQTTPassword[32];
  char          MQTTTopic[32];
  char          nodeName[32];
  char          nodeType[32];
  int8_t        updWifiConfigFromMQTT;
  int8_t        updMqttConfigFromMQTT;
  int8_t        timezone;
  uint8_t       power;
  uint8_t       nextStartInitPortal;
  double        nodeSendConfigInterval;
  double        nodeSendDataInterval ;
  double        nodeSendDataThreshold;
  int           nodeSleepInterval;
} sysCfg;

char            Hostname[32];          //TODO:Comprobar si hay que borrarlo
boolean         estado = false;
char            autoSSID_name[20] = "Wastbee";
char            autoSSID_password[20] = "password";
//String          nodeMSG; //Mensaje a publicar en el log
//boolean         pendingNodeMSG = false; //indica si hay algún mensaje pendiente.
String          nodeValue;//Mensaje a publicar en el Topic
boolean         pendingNodeValue = false; //Indica si hay algún mensaje pendiente
long int        pulsado = 0; //Para medir el tiempo del bucle del botón
double          tApagado = 0.1; //el tiempo que el led que parpadea estará encendido.
unsigned long   lastMillis = 0; //para la prueba del MQTT
String          deviceTopic; //Contiene el topic a través del que se le pasan los valores de config
long            rebotMillis = 0;
boolean         rebote = false;
long            wifiStart;
double          lastConfigTime=0;
double          lastDataTime=0;

//**********PREDEFINICION DE FUNCIONES*************************
void        leerSensor();
void        ledBlink (double intervaloParpadeo, double tiempoEncendido);
void        setupSerial();
void        setupPins();
void        setupGadget();
void        setupPortal();
void        pulsadoBoton();
void        pulsaLarga();
void        onShortPush();
boolean     configTopic (String topic, String payload);
void        addLog(byte loglevel, const char *line);
void        addLog(byte loglevel, String& string);
void        CFG_Save();
void        CFG_Default();
void        CFG_Load();
void        CFG_Erase();
void        CFG_Print();
void        connectMQTT();
void        messageReceived(String topic, String payload, char * bytes, unsigned int length);
boolean     configTopic (String topic, String payload);
//void        setNodeMSG (String msg);
int         getInterval (String payload);
int         autoConnect (char const *apName, char const *apPassword);
boolean     startConfigPortal(char const *apName, char const *apPassword);
void        setupConfigPortal();
void        handleWifi();
void        handleWifiSave();
void        handleReset();
void        handleNotFound();
void        handleUpdatePost(); //OTA
void        handleUpload(); //OTA
void        handleUpdateGet(); //OTA
int         getRSSIasQuality(int RSSI);
boolean     isIp(String str);
String      toStringIp(IPAddress ip);
String      urldecode(const char *src);
//int         connectWifi(String ssid, String pass);
boolean     isIp(String str);
boolean     captivePortal();
void        sendConfigInfo();
void        onMQTTMsg (String topic, String payload, char * bytes, unsigned int length);
void        onShortPush();
void        sendConfigParam (String topic, String payload);
void        sendNodeLog (String msg);
void        sendNodeValue (String topic, String payload);
void        callbackEndPointLed (String payload);
void        callbackEndPointRele (String payload);
void        callbackEndPointButton (String payload);


//**********PREDEFINICION DE FUNCIONES*************************

//*******************CALLBACKS********************************
void onMQTTMsg (String topic, String payload, char * bytes, unsigned int length) {
  char log[80];
  sprintf_P(log, PSTR("MQTT: received \"%s\" = \"%s\""), topic.c_str(), payload.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
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

void onShortPush() {
  if (estado) {
    estado = false;
//    sendNodeValue (String(sysCfg.MQTTTopic), nodeValue);
    pendingNodeValue = true; //Se activa un semaforo para enviar el topic en el loop https://github.com/knolleary/pubsubclient/issues/99
    nodeValue = "off";
    digitalWrite(LED, HIGH);
  }
  else
  {
//    sendNodeValue (String(sysCfg.MQTTTopic), nodeValue);
    estado = true;
    pendingNodeValue = true; //Se activa un semaforo para enviar el topic en el loop https://github.com/knolleary/pubsubclient/issues/99
    nodeValue = "on";
    digitalWrite(LED, LOW);
  }
}
//Callback de los endPoints (es una simulación en remoto de que se utilizan los recursos locales
void callbackEndPointLed (String payload){
  
  }
void callbackEndPointRele (String payload){}
void callbackEndPointButton (String payload){
  //Payload=1 pulsa corte, Payload=2 pulsa larga
  if (payload==String("1")){
    onShortPush();}
  else   if (payload==String("2")){
    pulsaLarga();}
    
  }

//*******************CALLBACKS********************************

void setup() {
  setupSerial();            //Configuracion inicial del puerto serie
  setupPins();              //Configuracion inicial de los pins
  setupGadget();                //Configuracion inicial del sistema de ficheros y el Json
  setupPortal();            //Se conecta a la wifi o inicializa el portal

  if (mqttClient.begin(sysCfg.MQTTServer, atoi(sysCfg.MQTTPort), secureClient)) {
    ledBlink (2, 0.05); 
  }

  connectMQTT();
  sendConfigInfo();
}



void loop() {
  char log[80];
  mqttClient.loop();
  delay(10);                    // <- fixes some issues with WiFi stability
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  //Se ejecuta periodicamente cada act segundos
    if(millis() - lastConfigTime > sysCfg.nodeSendConfigInterval) {
      char log[80];
      lastConfigTime = millis();
      sprintf_P(log, PSTR("MQTT: Send configuration info"));
      addLog(LOG_LEVEL_INFO, log);
      sendConfigInfo();
      }

  //Se ejecuta periodicamente cada act segundos
    if(millis() - lastDataTime > sysCfg.nodeSendDataInterval ) {
      char log[80];
      lastDataTime = millis();
      sprintf_P(log, PSTR("MQTT: Send data topic"));
      addLog(LOG_LEVEL_INFO, log);
      // Aqui lo que sea que envie los datos
      }

  //Retrasa la activación de las interrupciones despues de pulsar el botón para evitar rebotes
  if ((millis() - rebotMillis > 500) && rebote) {
    rebote = false;
    //Serial.println("attachInt");
    attachInterrupt(BUTTON, pulsadoBoton, CHANGE);
  }


  //Escribe las actualizaciones pendientes de estado en el broker
  if (pendingNodeValue) {
    pendingNodeValue = false;
    sprintf_P(log, PSTR("MQTT: Published \"%s\" = \"%s\""), sysCfg.MQTTTopic, nodeValue.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    mqttClient.publish(sysCfg.MQTTTopic, nodeValue);
    mqttClient.loop();
    //Serial.println ("Publicado " + nodeValue);
  }

  //Escribe en el log de MQTT los mensajes pendientes
/*
  if (pendingNodeMSG) {
    String topic = deviceTopic + String("LOG/nodeMSG/");
    //  Serial.println ("Topic: " + topic +"; Mensaje: " + nodeMSG);
    sprintf_P(log, PSTR("MQTT: Published \"%s\" = %s"), topic.c_str(), nodeMSG.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
    mqttClient.publish(topic, nodeMSG); //Publica el error en el $DEV
    mqttClient.loop();
    pendingNodeMSG = false;
  }
*/
}


