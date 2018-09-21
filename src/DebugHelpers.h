// conditional debugging
#if DEBUG 
  #define beginDebug()    do { Serial.begin (115200); } while (0)
  #define Trace(x)        Serial.print      (x)
  #define Trace2(x,y)     Serial.print      (x,y)
  #define Traceln(x)      Serial.println    (x)
  #define Traceln2(x,y)   Serial.println    (x,y)
  #define Tracef(...)     Serial.printf     (__VA_ARGS__)
  #define TraceFunc()     do { Trace (F("In function: ")); Serial.println(__PRETTY_FUNCTION__); } while (0)
  
#else
  #define beginDebug()    ((void) 0)
  #define Trace(x)        ((void) 0)
  #define Trace2(x,y)     ((void) 0)
  #define Traceln(x)      ((void) 0)
  #define Traceln2(x,y)   ((void) 0)
  #define Tracef(...)     ((void) 0)
  #define TraceFunc()     ((void) 0)
#endif // DEBUG

#ifndef DEBUG_h
#define DEBUG_h

void chipInformation() {
  Traceln();
  Trace( F("Heap: ") ); Traceln(system_get_free_heap_size());
  Trace( F("Boot Vers: ") ); Traceln(system_get_boot_version());
  Trace( F("CPU: ") ); Traceln(system_get_cpu_freq());
  Trace( F("SDK: ") ); Traceln(system_get_sdk_version());
  Trace( F("Chip ID: ") ); Traceln(system_get_chip_id());
  Trace( F("Flash ID: ") ); Traceln(spi_flash_get_id());
  Trace( F("Flash Size: ") ); Traceln(ESP.getFlashChipRealSize());
  Trace( F("Vcc: ") ); Traceln(ESP.getVcc());
  Traceln();  
}


#endif 