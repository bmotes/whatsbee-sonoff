//TODO: The keepalive interval is set to 15 seconds by default. This is configurable via MQTT_KEEPALIVE in PubSubClient.h.
//TODO:he client uses MQTT 3.1.1 by default. It can be changed to use MQTT 3.1 by changing value of MQTT_VERSION in PubSubClient.h.
//OJO, modificar en la librería el valor de #define MQTT_BUFFER_SIZE 512 de 128 a 512
//V06.41 se introducen los end points en el loop (no pueden ir con interrupciones
//V6.0 Se introduce comando para leer el sensor, también para que envie los end points
//V5.6 Se resuelve problema de desconexión del rele
//V5.5 Se introducen los end points y se resuelve problema con OTA
//V4.1 Se añade el comando para pedir al nodo que mande la config.
//V4.2 Se normalizan los comandos de configuración

ADC_MODE(ADC_VCC);

#define CON_SSL                     true              //Compilar con TSL/SSL
#define HW_VER                      "SMTSW"           //VERSION DEL HW
#define CAPTIVE_PORTAL              false             //Se instala el DNS para elportal cautivo

#if CON_SSL
  #define FW_VER                    "06.90 SSL"       //VERSION DEL FW Si está activado el SSL
  #define MQTT_PORT                 "8883"            //El puerto si está activado el SSL
#else
  #define FW_VER                    "06.90"           //VERSION DEL FW Si no está activado el SSL
  #define MQTT_PORT                 "1883"            //EL puerto si está desactivado el SSL
#endif

#define LED                         13                //El led que se va a utilizar para parpadear 13 sonoff, 16 amica
#define BUTTON                      0                 //El botón que se utiliza para entrar en la config
#define RELE                        12                //El Relé

#define PUSH_TIME_FOR_START_PORTAL  4000              //Tiempo mínimo (ms) que se tiene que pulsar el botón para que inicie el ConfigPortal
#define PUSH_TIME_FOR_RESET_ALL     20000             //Tiempo de pulsación del botón para que se cargue la configuración por defecto
#define PORTAL_TIMEOUT              60000             //Tiempo en milisegundos que está activo el portal
#define WIFI_CONNECT_CACHE_TIME     4000              //Tiempo máximo (ms) para intentar conectarse con las credenciales en Caché.
#define WIFI_CONNECT_STORED_TIME    20000             //Tiempo máximo (ms) para intentar conectarse con las credenciales almacenadas.
#define DUTTY_CYCLE_LED             10                //el dutty del LED
#define CHECK_CONECTION_TIME        550000            //Tiempo para comprobar si está conectado y resetear.

#define LOG_LEVEL_NONE              0
#define LOG_LEVEL_ERROR             1
#define LOG_LEVEL_INFO              2
#define LOG_LEVEL_DEBUG             3
#define LOG_LEVEL_DEBUG_MORE        4
#define SERIAL_IO                   true
#define UPD_WIFI_CFG_FROM_MQTT      1
#define UPD_MQTT_CFG_FROM_MQTT      1
#define CFG_HOLDER                  0x20161017        // Change this value to load default configurations
#define HIDDEN_PASSWORD             "Hidden_Password" //Cadena que utiliza para ocultar el password
#define MQTT_CONN_RETRYS            20                //Número máximo de intentos de conexión a MQTT
#define MQTT_CLIENT_ID              "WHATSBEE_%06X"   // Also fall back topic using Chip Id = last 6 characters of MAC address

#define DEFAULT_STA_SSID1           ""                //Nombre de SSID1 por defecto
#define DEFAULT_STA_PASS1           ""                //Password de la primera wifi por defecto
#define DEFAULT_STA_SSID2           ""                //Nombre de SSID2 por defecto
#define DEFAULT_STA_PASS2           ""                //Password de la segunda wifi por defecto
#define DEFAULT_STA_SSID3           ""                //Nombre de SSID3 por defecto
#define DEFAULT_STA_PASS3           ""                //Password de la tercera wifi por defecto
#define DEFAULT_MQTT_SERVER         "www.whatsbee.net"
#define DEFAULT_MQTT_USER           ""
#define DEFAULT_MQTT_PASSWORD       ""
#define DEFAULT_MQTT_TOPIC          ""
#define DEFAULT_AP_PASSWORD         "password"        //Password por defecto para cuando se resetea completamente la config
#define DEFAULT_NODE_NAME           "unconfigured"    //Nombre del nodo en la config por defecto
#define DEFAULT_NODE_TYPE           HW_VER            //Tipo de nodo en la config por defecto
#define DEFAULT_PERMISSIONS         65535             //TODO: Cambiar esto a cero para la versione n producción
#define DEFAULT_ADMIN_NAME          ""
#define DEFAULT_ADMIN_ADDRESS       ""
#define DEFAULT_ADMIN_MAIL          ""
#define DEFAULT_NODE_DESCR          ""
#define DEFAULT_NODE_LAT            "0.00000"
#define DEFAULT_NODE_LON            "0.00000"
#define DEFAULT_SYSLOG_HOST         "192.168.29.134"
#define DEFAULT_SYSLOG_PORT         514
#define DEFAULT_SYSLOG_LEVEL        LOG_LEVEL_NONE
#define DEFAULT_SERIAL_LOG_LEVEL    LOG_LEVEL_DEBUG
#define DEFAULT_MQTT_LOG_LEVEL      LOG_LEVEL_INFO
#define DEFAULT_APP_TIMEZONE        1                  // +1 hour (Amsterdam)
#define DEFAULT_APP_POWER           0                  // Saved power state Off
#define DEFAULT_CONFIG_TIME         3600000            //Tiempo en el que envia los datos de config del nodo (ms)
#define DEFAULT_DATA_INTERVAL       60000              //Tiempo en el que envia los datos del topic
#define DEFAULT_DATA_THRESHOLD      0                  //Porcentajde de diferencia para enviar los datos o no
#define DEFAULT_SENSOR_INTERVAL     6000               //Tiempo en el que lee el sensor
#define DEFAULT_SLEEP_TIME          0                  //Indica si el nodo duerme
#define DEFAULT_PORTAL_REASON       "New device or reset all"

#ifdef DEBUG_ESP_PORT
  #define DEBUG_MSG(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#else
  #define DEBUG_MSG(...)
#endif

#define PERM_GET_WIFI               1
#define PERM_SET_WIFI               2
#define PERM_GET_MQTT               4
#define PERM_SET_MQTT               8
#define PERM_GET_DEVICE             16
#define PERM_SET_DEVICE             32
#define PERM_GET_SENSOR             64
#define PERM_SET_SENSOR             128
#define PERM_GET_APPW               256
#define PERM_SET_APPW               512
#define PERM_GET_LOG                1024
#define PERM_SET_LOG                2048
#define PERM_GET_ENDPOINTS          4096
#define PERM_SET_ENDPOINTS          8192
#define PERM_EXEC_CMD               16384
#define PERM_UPGR_FW                32768
#define PERM_ALL                    65535 //B1111111111111111     

//########################ESPECIFICO DEL NODO (DIRECTIVAS PREPROCESSOR)##################

//########################################################################################

//########################ESPECIFICO DEL NODO (INCLUDE LIBRERÍAS)#########################

//########################################################################################
//#include <GDBStub.h>                          //DEBUG
#include <ESP8266WiFi.h>                        //https://github.com/esp8266/Arduino
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Ticker.h>                             //for LED status
#include <MQTTClient.h>                         //para la conexión a MQTT
#include <ESP8266HTTPClient.h>                  //HTTP OTA
#include <ESP8266httpUpdate.h>                  //HTTP OTA
//MDNS #include <ESP8266mDNS.h>

#if CAPTIVE_PORTAL
  #include <DNSServer.h>                        //XXNOTA: hay numerosos problemas para que funcione el portal cautivo, por lo que se elimina la opción del DNS Server
  #define DNS_PORT 53                           //El puerto del DNS
  DNSServer dnsServer;                          //Servidor DNS si se utiliza el portal cautivo
#endif

//########################ESPECIFICO DEL NODO (INICIALIZACION OBJETOS)#########################

//#############################################################################################

Ticker initBlinkLedOn;                          //Controla el parpadeo del led
Ticker initBlinkLedOff;                         //Controla el parpadeo del led
ESP8266WiFiMulti wifiMulti;                     //Librería Wifi para permitir la conexión a una lista de APS
WiFiUDP portUDP;                                //Necesarsio para el sysLog

#if CON_SSL
  WiFiClientSecure secureClient;                //Cliente de wifi
#else
  WiFiClient secureClient;                      //Cliente de wifi
#endif

ESP8266WebServer server (80);                   //Servidor Http
MQTTClient mqttClient;                          //Cliente MQTT

struct SYSCFG {                                 //Almacena la configuración
  unsigned long CfgHolder;
  unsigned long SaveFlag;
  int8_t        SerialLogLevel;
  int8_t        SysLogLevel ;
  char          SysLogHost[32];
  char          WifiSSID1[32];
  char          WifiPassword1[64];
  char          WifiSSID2[32];
  char          WifiPassword2[64];
  char          WifiSSID3[32];
  char          WifiPassword3[64];
  char          APPassword[64];
  char          MqttServer[32];
  char          MqttPort[5];
  char          MqttUser[32];
  char          MqttPassword[32];
  char          MqttTopic[32];
  char          NodeName[32];
  char          NodeType[32];
  int8_t        updWifiConfigFromMQTT;
  int8_t        updMqttConfigFromMQTT;
  int8_t        TimeZone;
  int8_t        Power;
  int8_t        NextStartInitPortal;
  double        SendConfigInterval;
  double        SendDataInterval;
  double        SendDataThreshold;
  double        SleepInterval;
  double        ReadSensorInterval;
  int8_t        CachedWifi;
  unsigned long Permissions;
  char          AdminName[32];
  char          AdminAddress[64];
  char          AdminMail[64];
  char          NodeDescr[64];
  char          NodeLat[20];
  char          NodeLon[20];
  int8_t        MqttLogLevel;
  char          PortalReason[80];
//########################ESPECIFICO DEL NODO (PARAMETROS SYSCONFIG)###########################

//#############################################################################################
} sysCfg;

char            Hostname[16];                       //Sirve para identificar el nodo en el LOG
boolean         ledInvertido = false;               //Invierte el parpadeo del led (normalmente encendido)
char            ApSsid[30] = "Wastbee";
char            ApPassword[30] = "password";
String          nodeValue;                          //Mensaje a publicar en el Topic
double          doubleNodeValue=0;                   //Si el sensor principal es numérico contiene en valor, si no 0
double          lastDoubleNodeValue=0;               //Ultimo valor enviado
boolean         pendingNodeValue = false;           //Indica si hay algún mensaje pendiente
boolean         pendingNodeLog = false;
String          nodeLog="";
unsigned long   pulsado = 0;                        //Para medir el tiempo del bucle del botón
double          tApagado = 0.1;                     //el tiempo que el led que parpadea estará encendido.
double          tRepeatSensor = 3;                  //Cuando falla el sensor hace un nuevo intento en...
unsigned long   lastMillis = 0;                     //para la prueba del MQTT
String          deviceTopic;                        //Contiene el topic a través del que se le pasan los valores de config
long            rebotMillis = 0;
boolean         rebote = false;
unsigned long   wifiStart;
double          lastConfigTime=0;
double          lastDataTime=0;
double          lastCheckWifiTime=0;
double          lastSensorTime=0;
String          endPointRele="off";                 //Define las variables de los end points
String          endPointLed="off";                  //Define las variables de los end points
boolean         endPointReleLoop=false;
boolean         endPointLedLoop=false;
boolean         conMQTT=false;
boolean         portalOn=false;
boolean         isInterrupt=false;                  //Flag para saber si estamos en medio de una interrupción (no se pueden enviar mensajes MQTT)
boolean         httpOTA = false;                    //Se pone a true para hacer una actualización de FW a traves de http
double          sensorErrorInterval=2000;
unsigned long   tiempoPulsacion=0;
boolean         estado;

//########################ESPECIFICO DEL NODO (VARIABLES GLOBALES)#############################


//#############################################################################################

//**********PREDEFINICION DE FUNCIONES*************************
void        leerSensor();
void        ledBlink (double intervaloParpadeo, double tiempoEncendido);
void        setupSerial();
void        setupPins();
void        setupGadget();
void        setupPortal();
void        pulsadoBoton();
void        pulsaLarga();
void        pulsaReset();
void        onButtonPush();
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
boolean     isIp(String str);
String      toStringIp(IPAddress ip);
String      urldecode(const char *src);
//int         connectWifi(String ssid, String pass);
boolean     isIp(String str);
boolean     captivePortal();
void        sendConfigInfo();
void        sendConfigParam (String topic, String payload);
void        sendNodeLog (String msg);
void        sendNodeValue (String topic, String payload);
int         wifiConnectCache();
int         wifiConnectStored();
int         evalThreshold (double sensorValue);
String      hidePassword(String password);
int         hasPermissions (unsigned long permission);
/*Callbacks*/
void        onIniSetup();
void        onFinSetup();
void        onReadSensorInterval();
void        onSendDataInterval();
void        onSendConfigInterval();
void        onMQTTMsg (String topic, String payload, char * bytes, unsigned int length);
void        onButtonPush();
void        onReleChange();
void        onLedChange();
void        onModeChange();
void        onThresholdExceeded();
void        ledOn();
void        ledOff();
void        releOn();
void        releOff();
void        releToogle();
void        setupMDNS();                  //MDNS
void        httpLoopOTA(String firmwareFile);    //HTTP_OTA UPDATE
int         upgradeFW(String firmwareFile);       //HTTP_OTA UPDATE
String      passwordProtect(char *pw);
String      passwordProtect(String pw);
String      getUniqueId();
String      webParam(String control, String id, String typeControl, String typeMore, String caption, String value);
String      webAdv (String control, String section, String number);
String      webWifi (String control, String number, String ssid, String password);
int         setGetCfg (char* sysCfgVar, String value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb);
int         setGetCfg (double &sysCfgVar, double value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb);
int         setGetCfg (int8_t &sysCfgVar, int8_t value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb);
int         setGetCfg (unsigned long &sysCfgVar, unsigned long value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb);
int         getCfg(String topic, String payload, unsigned long getPerm);
int         getCfg(String topic, int8_t payload, unsigned long getPerm);
int         getCfg(String topic, double payload, unsigned long getPerm);
int         getCfg(String topic, unsigned long payload, unsigned long getPerm);
boolean     handleConfigTopic(String topic, String payload);
boolean     handleEndPointTopic(String topic, String payload);
boolean     handleCommandTopic(String topic, String payload);
int         findText(String buscada, String cadena);
void        razonPortal (String razon);

/******CALLBACKS********/
/*callback de recepción de mensaje (no incluidos los de config*/
void onMQTTMsg (String topic, String payload, char * bytes, unsigned int length) {
  char log[80];
  sprintf_P(log, PSTR("MQTT: received \"%s\" = \"%s\""), topic.c_str(), payload.c_str());
  addLog(LOG_LEVEL_DEBUG, log);
    if (payload == "on") { //TODO: verificar que es el topic correcto
      estado = true;
      ledOn();
      releOn();
    }
    else {
      estado = false;
      ledOff();
      releOff();
    }
  }
/*Callback del principio del setup*/  
void onIniSetup(){
/*Callback del fin del setup*/  
}
void onEndSetup(){
}
/*Callback de la pulsación del botón (solo pulsación corta*/
void onButtonPush() {
  char log[80];
    if (estado) {
    estado = false;
    sendNodeValue (String(sysCfg.MqttTopic), nodeValue);
    nodeValue = "off";
    ledOff();
    releOff();
  }
  else
  {
    sendNodeValue (String(sysCfg.MqttTopic), nodeValue);
    estado = true;
    nodeValue = "on";
    ledOn();
    releOn();
  }

}
/*Callback de la pulsación remotadel botón (solo pulsación corta*/
void onRemoteButtonPush() {
  onButtonPush();                                       //simula la pulsación local del botón
}
/*Callback de cambio del Relé*/
void onReleChange(){
  endPointReleLoop=true;
}
/*Callback del cambio de Led*/
void onLedChange(){
  endPointLedLoop=true;
}

/*Callback de lectura del sensor*/
void onReadSensorInterval(){
  //no hay sensor
  //evalThreshold (0); //Aqui no va cero, va la lectura del sensor, en double.
}
/*Callback de envio de datos del topic principal*/
void onSendDataInterval(){
  char log[80];
//    lastDoubleNodeValue=doubleNodeValue;
    mqttClient.publish(sysCfg.MqttTopic, nodeValue);
    mqttClient.loop();
    sprintf_P(log, PSTR("MQTT: Pub \"%s\"->\"%s\""), sysCfg.MqttTopic, nodeValue.c_str());
    addLog(LOG_LEVEL_DEBUG, log);
}
/*Callback de envio de datos de configuración*/
void onSendConfigInterval(){
  sendConfigInfo();
}
/*Callback de threshod superado*/
void onThresholdExceeded (){
  onSendDataInterval();
}
//########################ESPECIFICO DEL NODO (CALLBACKS)######################################

//#############################################################################################

