#define BLYNK_TEMPLATE_ID           "TMPLMoAkCYWy"
#define BLYNK_DEVICE_NAME "Buu"
#define BLYNK_AUTH_TOKEN "6t5RyhrFcaurR `NKSQbXsFfmNUC52TE0d"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "6t5RyhrFcaurRNKSQbXsFfmNUC52TE0d";
char ssid[] = "Phi Ho";
char pass[] = "thanhthao123456";

WidgetLED led_connect(V0);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V1) // chạy Auto
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("1");}
  else
  {Serial.write("5");}
}

BLYNK_WRITE(V2) //Bật tắt đèn UV
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("2");}
  else
  {Serial.write("3");}
}

BLYNK_WRITE(V4) //Tiến tới
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("4");}
  else
  {Serial.write("5");}
}

BLYNK_WRITE(V5) //Đi lùi
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("6");}
  else
  {Serial.write("5");}
}

BLYNK_WRITE(V6) //Rẽ phải
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("7");}
  else
  {Serial.write("5");}
}

BLYNK_WRITE(V7) //Rẽ trái
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("8");}
  else
  {Serial.write("5");}
}

BLYNK_WRITE(V8) //Tăng tốc độ
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("+");}
}

BLYNK_WRITE(V9) //Giảm tốc độ
{
  int pinValue = param.asInt();
  if(pinValue == 1) 
  {Serial.write("-");}
}

void loop() {
  int PIN = random(0, 80);
  Blynk.virtualWrite(V3, PIN);
  Blynk.run();  
}
