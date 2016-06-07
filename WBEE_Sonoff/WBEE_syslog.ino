/*********************************************************************************************\
   Syslog
  \*********************************************************************************************/
void syslog(const char *message)
{
  char mess[168], str[200];
  portUDP.beginPacket(sysCfg.nodeSyslogHost, SYS_LOG_PORT);
  strncpy(mess, message, 167);
  mess[168] = 0;
  sprintf_P(str, PSTR("%s %s"), Hostname, mess);
  portUDP.write(str);
  portUDP.endPacket();
}

void addLog(byte loglevel, const char *line)
{
  DEBUG_MSG("DebugMsg %s\n", line);
#ifdef SERIAL_IO
  if (loglevel <= sysCfg.nodeSerialLogLevel) Serial.println(line);
#endif
  if ((WiFi.status() == WL_CONNECTED) && (loglevel <= sysCfg.nodeSysLogLevel )) syslog(line);
}

void addLog(byte loglevel, String& string)
{
  addLog(loglevel, string.c_str());
}

/********************************************************************************************/

