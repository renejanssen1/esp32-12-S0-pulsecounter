#include <WiFi.h>
#include <Time.h>
#include <MySQL_Generic.h>

char ssid[] = "";
char pass[] = "";
char server[] = "";
uint16_t server_port = 3306;
char user[]         = "";
char password[]     = "";
char database[] = "";
char table[]    = "";
long pulsetime = 0;
int interruptCounter = 0;
char tijd[9];
char datum[11];
int u = 0;
int m = 0;
int s = 0;
int y = 0;
int mo = 0;
int d = 0;
int timestamp = 0;
//#define LED 2
#define INT_PIN1 16
#define INT_PIN2 18
#define INT_PIN3 19
#define INT_PIN4 21
#define INT_PIN5 22
#define INT_PIN6 23
#define INT_PIN7 13
#define INT_PIN8 12
#define INT_PIN9 14
#define INT_PIN10 27
#define INT_PIN11 26
#define INT_PIN12 25
int t1 = 0;
int t2 = 0;
int t3 = 0;
int t4 = 0;
int t5 = 0;
int t6 = 0;
int t7 = 0;
int t8 = 0;
int t9 = 0;
int t10 = 0;
int t11 = 0;
int t12 = 0;

#define MY_NTP_SERVER "pool.ntp.org"           
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"   
time_t now;                         // this are the seconds since Epoch (1970) - UTC
tm tm;                              // the structure tm holds time information in a more convenient way
uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000 () {
  return 60000UL; // 60s
}
// MySQL Debug Level from 0 to 4
#define _MYSQL_LOGLEVEL_      1
#define MYSQL_DEBUG_PORT      Serial

// MySQL something
MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

void ICACHE_RAM_ATTR interruptRoutine1() {
  static unsigned long lasttime1 = 0;
  unsigned long intertime1 = millis();
  if (intertime1 - lasttime1 > 100){
    t1++;
  }
  lasttime1 = intertime1;
}
void ICACHE_RAM_ATTR interruptRoutine2() {
  static unsigned long lasttime2 = 0;
  unsigned long intertime2 = millis();
  if (intertime2 - lasttime2 > 100){
    t2++;
  }
  lasttime2 = intertime2;
}
void ICACHE_RAM_ATTR interruptRoutine3() {
  static unsigned long lasttime3 = 0;
  unsigned long intertime3 = millis();
  if (intertime3 - lasttime3 > 100){
    t3++;
  }
  lasttime3 = intertime3;
}
void ICACHE_RAM_ATTR interruptRoutine4() {
  static unsigned long lasttime4 = 0;
  unsigned long intertime4 = millis();
  if (intertime4 - lasttime4 > 100){
    t4++;
  }
  lasttime4 = intertime4;
}
void ICACHE_RAM_ATTR interruptRoutine5() {
  static unsigned long lasttime5 = 0;
  unsigned long intertime5 = millis();
  if (intertime5 - lasttime5 > 100){
    t5++;
  }
  lasttime5 = intertime5;
}
void ICACHE_RAM_ATTR interruptRoutine6() {
  static unsigned long lasttime6 = 0;
  unsigned long intertime6 = millis();
  if (intertime6 - lasttime6 > 100){
    t6++;
  }
  lasttime6 = intertime6;
}
void ICACHE_RAM_ATTR interruptRoutine7() {
  static unsigned long lasttime7 = 0;
  unsigned long intertime7 = millis();
  if (intertime7 - lasttime7 > 100){
    t7++;
  }
  lasttime7 = intertime7;
}
void ICACHE_RAM_ATTR interruptRoutine8() {
  static unsigned long lasttime8 = 0;
  unsigned long intertime8 = millis();
  if (intertime8 - lasttime8 > 100){
    t8++;
  }
  lasttime8 = intertime8;
}
void ICACHE_RAM_ATTR interruptRoutine9() {
  static unsigned long lasttime9 = 0;
  unsigned long intertime9 = millis();
  if (intertime9 - lasttime9 > 100){
    t9++;
  }
  lasttime9 = intertime9;
}
void ICACHE_RAM_ATTR interruptRoutine10() {
  static unsigned long lasttime10 = 0;
  unsigned long intertime10 = millis();
  if (intertime10 - lasttime10 > 100){
    t10++;
  }
  lasttime10 = intertime10;
}
void ICACHE_RAM_ATTR interruptRoutine11() {
  static unsigned long lasttime11 = 0;
  unsigned long intertime11 = millis();
  if (intertime11 - lasttime11 > 100){
    t11++;
  }
  lasttime11 = intertime11;
}
void ICACHE_RAM_ATTR interruptRoutine12() {
  static unsigned long lasttime12 = 0;
  unsigned long intertime12 = millis();
  if (intertime12 - lasttime12 > 100){
    t12++;
  }
  lasttime12 = intertime12;
}

void setup(){
//  pinMode(LED, OUTPUT);
  pinMode(INT_PIN1, INPUT_PULLUP);
  pinMode(INT_PIN2, INPUT_PULLUP);
  pinMode(INT_PIN3, INPUT_PULLUP);
  pinMode(INT_PIN4, INPUT_PULLUP);
  pinMode(INT_PIN5, INPUT_PULLUP);
  pinMode(INT_PIN6, INPUT_PULLUP);
  pinMode(INT_PIN7, INPUT_PULLUP);
  pinMode(INT_PIN8, INPUT_PULLUP);
  pinMode(INT_PIN9, INPUT_PULLUP);
  pinMode(INT_PIN10, INPUT_PULLUP);
  pinMode(INT_PIN11, INPUT_PULLUP);
  pinMode(INT_PIN12, INPUT_PULLUP);
  Serial.begin(115200);
  configTime(0, 0, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
  setenv("TZ", MY_TZ, 1);
  tzset();
  WiFi.hostname("ESPboard-counter");
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
//    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
//     digitalWrite(LED_BUILTIN, HIGH);
    delay(500);     
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  // Test MySQL connection
  Serial.print("Connecting to SQL Server @ ");
  Serial.print(server);
  Serial.println(String(", Port = ") + server_port);
  Serial.println(String("User = ") + user + String(", PW = ") + password + String(", DB = ") + database);

  Serial.println("");
  attachInterrupt(INT_PIN1, interruptRoutine1, FALLING);
  attachInterrupt(INT_PIN2, interruptRoutine2, FALLING);
  attachInterrupt(INT_PIN3, interruptRoutine3, FALLING);
  attachInterrupt(INT_PIN4, interruptRoutine4, FALLING);  
  attachInterrupt(INT_PIN5, interruptRoutine5, FALLING);
  attachInterrupt(INT_PIN6, interruptRoutine6, FALLING);
  attachInterrupt(INT_PIN7, interruptRoutine7, FALLING);
  attachInterrupt(INT_PIN8, interruptRoutine8, FALLING);
  attachInterrupt(INT_PIN9, interruptRoutine9, FALLING);
  attachInterrupt(INT_PIN10, interruptRoutine10, FALLING);  
  attachInterrupt(INT_PIN11, interruptRoutine11, FALLING);
  attachInterrupt(INT_PIN12, interruptRoutine12, FALLING);
}
 
void postData() {
  String INSERT_SQL = String("INSERT INTO ") + database + "." + table + " (datum, tijd, timestamp, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12) VALUES (" + datum + "," + tijd + "," + timestamp + "," + t1 + "," + t2 + "," + t3 + "," + t4 + "," + t5 + "," + t6 + "," + t7 + "," + t8 + "," + t9 + "," + t10 + "," + t11 + "," + t12 + ")";
  Serial.println("Connecting to MySQL...");
  Serial.println();
  if (conn.connectNonBlocking(server, server_port, user, password) != RESULT_FAIL)  {
    delay(500);
    MySQL_Query query_mem = MySQL_Query(&conn);
    if (conn.connected()){
      Serial.println(INSERT_SQL);
      if ( !query_mem.execute(INSERT_SQL.c_str()) )
        Serial.println("Insert error");
      else
        Serial.println("Data Inserted.");
          t1 = 0;
          t2 = 0;
          t3 = 0; 
          t4 = 0;
          t5 = 0; 
          t6 = 0;       
          t7 = 0;
          t8 = 0;
          t9 = 0; 
          t10 = 0;
          t11 = 0; 
          t12 = 0; 
    }else{
      Serial.println("Disconnected from Server. Can't insert.");
    }
    conn.close();
  } else{
    Serial.println("\nConnect failed. Trying again on next iteration.");
  }
//  digitalWrite(LED_BUILTIN, HIGH);
}
 
void loop() {
  time(&now);                       // read the current time
  localtime_r(&now, &tm);           // update the structure tm with the current time
  Serial.print("Timestamp: ");
  Serial.println(now);
  timestamp = now;
  u = tm.tm_hour;
  m = tm.tm_min;
  s = tm.tm_sec;
  y = tm.tm_year + 1900;
  mo = tm.tm_mon + 1;
  d = tm.tm_mday;
  Serial.print("Tijd: "); 
  snprintf(tijd, 9, "%02d%02d%02d", u, m, s);
  Serial.println(tijd);
  Serial.print("Datum: ");
  snprintf(datum, 11, "%04d%02d%02d", y, mo, d);
  Serial.println(datum);
  if (tm.tm_isdst == 1)             // Daylight Saving Time flag
    Serial.print("Zomertijd");
  else
    Serial.print("Wintertijd");
  Serial.println();
  if (m==0 || m==5 || m==10 || m==15 || m==20 || m==25 || m==30 || m==35 || m==40 || m==45 || m==50 || m==55){
    if (s==0){
      postData();
    }
  }
  char sValue[255];
  sprintf(sValue, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d", t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
  Serial.print("waardes zijn: ");
  Serial.println(sValue);
  delay(1000);
}
