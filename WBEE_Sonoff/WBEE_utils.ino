//########################ESPECIFICO DEL NODO (FUNCIONES)##################

//##########################################################################

/*Decide si la lectura del sensor supera el threshold*/
int evalThreshold (double sensorValue){
  char log[80];
  double variation= abs(sensorValue/lastDoubleNodeValue);
  doubleNodeValue= sensorValue;
  if (variation>=sysCfg.SendDataThreshold && sysCfg.SendDataThreshold!=0){
    sprintf_P(log, PSTR("SENS:Threshold exceeded"));
    addLog(LOG_LEVEL_INFO, log);  
    onThresholdExceeded ();  
    return 1;
  }
 return 0;
}
/*Oculta el password*/
String hidePassword(String password){
int largo= password.length();
String cadenaInt;
cadenaInt= password.substring (0,1);
for (int n=2; n<largo; n++){
  cadenaInt = cadenaInt + String("*");
}
cadenaInt = cadenaInt + password.substring(largo-1, largo);
return cadenaInt;
}
/*Comprueba si tiene permiso para ejecutar un comando*/
int hasPermissions (unsigned long permission){
  if ((sysCfg.Permissions & permission) == permission){
    return 1;
  }
  else{
    return 0;
  }
}
//Camufla el valor de un password
String passwordProtect(char *pw){
if (String(pw)==""){
  return "";   
  }
  else{
    return HIDDEN_PASSWORD;
  }
}
  
String passwordProtect(String pw){
if (pw==""){
  return "";   
  }
  else{
    return HIDDEN_PASSWORD;
  }

  
}
//Obtiene el id único (la MAC sin los dos puntos)
String getUniqueId(){
  String macPuntos = String(WiFi.macAddress());
  macPuntos.replace(String(":"), String(""));
  return macPuntos;
  }
//Comprueba si un uuario tiene permisos para actualizar uan config, lo hace, guarda y logea
int setGetCfg (char* sysCfgVar, String value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb){
    char log[80];
    //REC COMP boolean error=false;
    String source="Whatsbee";
    if (portalOn){source="config portal";}
    if (verb=="set"){                     
      if (((sysCfg.Permissions & setPerm) !=0) || portalOn){
          value.toCharArray(sysCfgVar, value.length()+1);
          sprintf_P(log, PSTR("CFG: Configured %s from %s"), sysCfgName.c_str(), source.c_str());
          addLog(LOG_LEVEL_INFO, log);
          if (!portalOn){         //Si la función se ha llamado desde el portal no se envia el resultado ni se salva (se hace al final)
            getCfg (sysCfgName, String(value),getPerm); 
            //sendConfigParam(sysCfgName, String(value));
            CFG_Save();
            }
       return 1; 
      }
      else{          
        sprintf_P(log, PSTR("ERROR: No perms for exec %s%s from %s"),verb.c_str(), sysCfgName.c_str(), source.c_str());
        addLog(LOG_LEVEL_ERROR, log);
        return 0;
      }
    }
    else if (verb=="get"){
      return  (getCfg (sysCfgName, String(value),getPerm)); 
      }
    return 0;
  }

int setGetCfg (double &sysCfgVar, double value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb){
    char log[80];
    //REC TEMP  boolean error=false;
    String source="Whatsbee";
    if (portalOn){source="config portal";}
    if (verb=="set"){                     
      if ((sysCfg.Permissions & setPerm) !=0 || portalOn){
          sysCfgVar=value;
          sprintf_P(log, PSTR("CFG: Configured %s from %s"), sysCfgName.c_str(), source.c_str());
          addLog(LOG_LEVEL_INFO, log);
          if (!portalOn){         //Si la función se ha llamado desd eel portal no se envia el resultado ni se salva (se hace el final)
            getCfg (sysCfgName, String(value),getPerm); 
            //sendConfigParam(sysCfgName, String(value));
            CFG_Save();
            }
       return 1; 
      }
      else{          
        sprintf_P(log, PSTR("ERROR: No perms for exec %s%s from %s"),verb.c_str(), sysCfgName.c_str(), source.c_str());
        addLog(LOG_LEVEL_ERROR, log);
        return 0;
      }
    }
    else if (verb=="get"){
      return  (getCfg (sysCfgName, String(value),getPerm)); 
      }
    return 0;
  }
//Comprueba si un uuario tiene permisos para actualizar uan config, lo hace, guarda y logea (Sobrecarga de la anterior)
int setGetCfg (int8_t &sysCfgVar, int8_t value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb){
    char log[80];
    //REC COMP  boolean error=false;
    String source="Whatsbee";
    if (portalOn){source="config portal";}
    if (verb=="set"){                     
      if (((sysCfg.Permissions & setPerm) !=0) || portalOn){
          sysCfgVar=value;
          sprintf_P(log, PSTR("CFG: Configured %s from %s"), sysCfgName.c_str(), source.c_str());
          addLog(LOG_LEVEL_INFO, log);
          if (!portalOn){         //Si la función se ha llamado desd eel portal no se envia el resultado ni se salva (se hace el final)
            getCfg (sysCfgName, String(value),getPerm); 
            CFG_Save();
            }
       return 1; 
      }
      else{          
        sprintf_P(log, PSTR("ERROR: No perms for exec %s%s from %s"),verb.c_str(), sysCfgName.c_str(), source.c_str());
        addLog(LOG_LEVEL_ERROR, log);
        return 0;
      }
    }
    else if (verb=="get"){
      return  (getCfg (sysCfgName, String(value),getPerm)); 
      }
    return 0;
  }

//Comprueba si un uuario tiene permisos para actualizar uan config, lo hace, guarda y logea (Sobrecarga de la anterior)
int setGetCfg (unsigned long &sysCfgVar, unsigned long value, unsigned long getPerm, unsigned long setPerm, String sysCfgName, String verb){
    char log[80];
    //REC COMP  boolean error=false;
    String source="Whatsbee";
    if (portalOn){source="config portal";}
    if (verb=="set"){                     
      if (((sysCfg.Permissions & setPerm) !=0) || portalOn){
          sysCfgVar=value;
          sprintf_P(log, PSTR("SUCCESS: Configured %s from %s"), sysCfgName.c_str(), source.c_str());
          addLog(LOG_LEVEL_INFO, log);
          if (!portalOn){         //Si la función se ha llamado desd eel portal no se envia el resultado ni se salva (se hace el final)
            getCfg (sysCfgName, String(value),getPerm); 
            CFG_Save();
            }
       return 1; 
      }
      else{          
        sprintf_P(log, PSTR("ERROR: No perms for exec %s%s from %s"),verb.c_str(), sysCfgName.c_str(), source.c_str());
        addLog(LOG_LEVEL_ERROR, log);
        return 0;
      }
    }
    else if (verb=="get"){
      return  (getCfg (sysCfgName, String(value),getPerm)); 
      }
    return 0;
  }
//Envia un parámetro de config si tiene permisos 
int getCfg(String topic, String payload, unsigned long getPerm){
char log[80];
      if ((sysCfg.Permissions & getPerm) !=0){
        mqttClient.publish(deviceTopic + String("CFG/") + topic, payload);
        mqttClient.loop();
        return 1;
      }
      else{
          sprintf_P(log, PSTR("ERROR: No perms for exec get%s from Whatsbee"), topic.c_str());
          addLog(LOG_LEVEL_ERROR, log);
          return 0;
      }
  }
//Envia un parámetro de config si tiene permisos (sobrecarga)
int getCfg(String topic, int8_t payload, unsigned long getPerm){
  return getCfg(topic, String(payload), getPerm);
  }
//Envia un parámetro de config si tiene permisos (sobrecarga)
int getCfg(String topic, double payload, unsigned long getPerm){
  return getCfg(topic, String(payload), getPerm);
  }
//Envia un parámetro de config si tiene permisos (sobrecarga)
int getCfg(String topic, unsigned long payload, unsigned long getPerm){
  return getCfg(topic, String(payload), getPerm);
  }
int findText(String buscada, String cadena) {
  int foundpos = -1;
  for (unsigned int i = 0; i <= cadena.length() - buscada.length(); i++) { 
    if (cadena.substring(i,buscada.length()+i) == buscada) {
      foundpos = i;
    }
  }
  return foundpos;
}

void razonPortal (String razon){
    char log[80];
    razon.toCharArray(sysCfg.PortalReason, sizeof(sysCfg.PortalReason));
    CFG_Save();
    sprintf_P(log, PSTR("PORT: Razón inicio Portal: %s"), sysCfg.PortalReason);
    addLog(LOG_LEVEL_DEBUG, log);
}

