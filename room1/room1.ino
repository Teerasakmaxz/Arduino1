#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

int buttonAir1 = D1;
int buttonAir2 = D2;
int led1 = D3;
int led2 = D4;
int led3 = D5;
int Air1 = D6;
int Air2 = D7;

int buttonStateA1 = 0;
int buttonStateA2 = 0;
int air = 0;
int air1 = 0;
int state = 0;
int state1 = 0;
boolean toggle1 = false;


#define FIREBASE_HOST "datacontro.firebaseio.com"
#define FIREBASE_AUTH "T4Sj1NzCmvsoClqegpG3VnaT9DLw2FzNKgqXZ0IR"

#define WIFI_SSID "STAFF_WiFi_ByIT"
#define WIFI_PASSWORD ""

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonAir1, INPUT);
  pinMode(buttonAir2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(Air1, OUTPUT);
  pinMode(Air2, OUTPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(Air1, HIGH);
  digitalWrite(Air2, HIGH);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.println("connecting....");
  while (WiFi.status() != WL_CONNECTED) {
     Serial.println(".");
    delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("room1/button2", 0);
  Firebase.set("room1/button", 0);
  Firebase.set("room1/state01", 0);
  Firebase.set("room1/state", 0);
  Firebase.set("room1/air1" , 0);
  Firebase.set("room1/air" , 0);

}

void loop() {

  buttonStateA1  = Firebase.getInt("room1/button");
  air =  Firebase.getInt("room1/air");
  state = Firebase.getInt("room1/state");
  if (digitalRead(buttonAir1) == HIGH && buttonStateA1 == 0 ) {
    if (buttonStateA1 == 0 && air == 0 && state == 0) {
      buttonStateA1 = 1;
    } else if (buttonStateA1 == 1 && air == 1 && state == 1) {
      buttonStateA1 = 0;
    }
  } else if (digitalRead(buttonAir1) == HIGH && buttonStateA1 == 1 ) {
    if (buttonStateA1 == 0 && air == 0 && state == 0) {
      buttonStateA1 = 1;
    } else if (buttonStateA1 == 1 && air == 1 && state == 1) {
      buttonStateA1 = 0;
    }
  }
 Firebase.set("room1/button", buttonStateA1);
  air1 = Firebase.getInt("room1/air1");
  state1 = Firebase.getInt("room1/state01");
  buttonStateA2  = Firebase.getInt("room1/button2");
  if (digitalRead(buttonAir2) == HIGH && buttonStateA2 == 0 ) {
    if (buttonStateA2 == 0 && air1 == 0 && state1 == 0) {
      buttonStateA2 = 2;
     
    } else if (buttonStateA2 == 2 && air1 == 2 && state1 == 1) {
      buttonStateA2 = 0;
    }
  } else if (digitalRead(buttonAir2) == HIGH && buttonStateA2 == 2 ) {
    if (buttonStateA2 == 0 && air1 == 0 && state1 == 0) {
      buttonStateA2 = 2;
    } else if (buttonStateA2 == 2 && air1 == 2 && state1 == 1) {
      buttonStateA2 = 0;
    }
  }
  Firebase.set("room1/button2", buttonStateA2);
  people();
  airopen();
  sensor();
}

void people() {
 int count = Firebase.getInt("room1/UserinRoom");
  if (count == 1) {
    digitalWrite(led1, LOW);
  } else if (count == 5 ) {
    digitalWrite(led2, LOW);

  } else if (count == 10) {
    digitalWrite(led3, LOW);
  } else if (count == 0) {
    Firebase.set("room1/air", 0);
    Firebase.set("room1/air1", 0);
  }
}

void airopen() {
  int sum = Firebase.getInt("room1/air");
  int sum1 = Firebase.getInt("room1/air1");
  if (sum == 1 ) {
    digitalWrite(Air1, LOW);
    Firebase.set("room1/state1", 0);
  } if (sum1 == 2) {
    digitalWrite(Air2, LOW);
    Firebase.set("room1/state2", 0);
  } if (sum == 0 ) {
    digitalWrite(Air1, HIGH);
    Firebase.set("room1/state1", 1);

  } if (sum1 == 0 ) {
    digitalWrite(Air2, HIGH);
    Firebase.set("room1/state2", 2);
  }
}
void sensor() {
   int  count1 =Firebase.getInt("room1/UserinRoom");
  toggle1 = Firebase.getBool("room1/toggle1");
  if (count1 == 0 && toggle1 == true) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else if (count1 == 4 && toggle1 == true) {
    digitalWrite(led2, HIGH);
  } else if (count1 == 9 && toggle1 == true) {
    digitalWrite(led3, HIGH);
  }
}


