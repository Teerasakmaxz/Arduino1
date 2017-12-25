#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


unsigned long timeout;
int sensorone = D1;
int sensortwo = D2;
int led1 =D3;
int led2 =D5;
bool toggle = false;
bool toggle1 = false;
int sensorState =  0;
int state1 =0;
int state2 =0;
int count = 0;

#define FIREBASE_HOST "datacontro.firebaseio.com"
#define FIREBASE_AUTH "T4Sj1NzCmvsoClqegpG3VnaT9DLw2FzNKgqXZ0IR"
#define WIFI_SSID "STAFF_WiFi_ByIT"
#define WIFI_PASSWORD ""

void setup() {

  pinMode(sensorone, INPUT);
  pinMode(sensortwo, INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }//loop while
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("room1/UserinRoom",0);
  Firebase.set("room1/toggle1", true);
}
void loop() {
    Firebase.set("room1/UserinRoom", count);
    Firebase.set("room1/toggle1", toggle1);
  
  if (digitalRead(sensorone) == LOW && toggle == false) {
    sensorState = 1 ;
    timeout = millis();
    toggle = true;
  } else if (digitalRead(sensortwo) == LOW && toggle == false) {
    sensorState = 2 ;
    timeout = millis();
    toggle = true;
  }
  Serial.println(sensorState);
  if (sensorState == 1 && digitalRead(sensortwo) == LOW) {
    count++;
    toggle = false;
    toggle1 = false;
    sensorState = 0;
  } else if (sensorState == 2 && digitalRead(sensorone) == LOW) {
    count--;
    toggle = false;
    toggle1 = true;
    sensorState = 0;
  }
  if (millis() - timeout > 500 && toggle == true) {
    toggle = false;
  }
  sensor();
}
void sensor(){

  state1 =Firebase.getInt("room1/state");
  state2 =Firebase.getInt("room1/state01");

  if(state1 == 1){
    digitalWrite(led1,HIGH);
  }else{
     digitalWrite(led1,LOW);
  }

  if(state2 == 1){
    digitalWrite(led2,HIGH);
  }else{
     digitalWrite(led2,LOW);
  }
  
}



