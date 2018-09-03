// conditional debugging
#if DEBUG 
  #define beginDebug()    do { Serial.begin (115200); } while (0)
  #define Trace(x)        Serial.print    (x)
  #define Trace2(x,y)     Serial.print    (x,y)
  #define Traceln(x)      Serial.println    (x)
  #define Traceln2(x,y)   Serial.println    (x,y)
  #define Tracef(x)       Serial.printf     (x)
  #define Tracef2(x,y)    Serial.printf     (x,y)
  #define Tracef3(x,y,z)  Serial.printf     (x,y,z)
  #define TraceFunc()     do { Trace (F("In function: ")); Serial.println(__PRETTY_FUNCTION__); } while (0)
  
#else
  #define beginDebug()    ((void) 0)
  #define Trace(x)        ((void) 0)
  #define Trace2(x,y)     ((void) 0)
  #define Traceln(x)      ((void) 0)
  #define Traceln2(x,y)   ((void) 0)
  #define Tracef(x)       ((void) 0)
  #define Tracef2(x,y)    ((void) 0)
  #define Tracef3(x,y,z)  ((void) 0)
  #define TraceFunc()     ((void) 0)
#endif // DEBUG