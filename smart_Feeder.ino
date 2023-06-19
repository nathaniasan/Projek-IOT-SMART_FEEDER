#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "CTBot.h" //Pendeklarasian Library
#define BLYNK_PRINT Serial
#define TriggerPin D2
#define EchoPin D1
#define servoPin D3

#define BLYNK_TEMPLATE_ID "TMPL6ozOFd_Hg"
#define BLYNK_TEMPLATE_NAME "UAS"
#define BLYNK_AUTH_TOKEN "8TQB6rgI5Rjhpe4YzbIv-a-aBUPXyJGQ"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi";
char pass[] = "rahasia123";
long durasi, jarak, volume;


CTBot myBot;
TBMessage msg;

String token = 6148950817:AAEhqF345fBFHDafdPbbEbEeMLILsuJoy34;
const int id = 5992592419;      //id telegram kalian

Servo gate;
BlynkTimer timer;

BLYNK_WRITE(V2){

  if (param.asInt()){
    gate.write(180);
  }else{
    gate.write(0);
  }

}

void sendToBlynk(){
  
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(TriggerPin, LOW);
  durasi = pulseIn(EchoPin, HIGH);
  jarak = (durasi/2)/ 29.1;
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak >= 8){
    volume = 0;
  }else if (jarak == 7){
    volume = 15;
  }else if (jarak == 6){
    volume = 25;
  }else if (jarak == 5){
    volume=50;
  }else if(jarak == 4){
    volume = 75;
  }else{
    volume = 100;
  }

  Blynk.virtualWrite(V1, volume);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  gate.attach(servoPin);
  gate.write(0);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendToBlynk);
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
  jarak = (durasi/2)/ 29.1;

  if (jarak >= 8){
    volume = 0;
    myBot.sendMessage(msg.sender.id, (String)"Pemberi tahuan Makanan sudah habis");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  

  Blynk.run();
  timer.run();

}
