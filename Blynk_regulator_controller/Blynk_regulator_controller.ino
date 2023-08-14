#define BLYNK_PRINT Serial

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "sgcjjjNdWdInUnXifXADYM_LiCGDaqV6";
char ssid[] = "Project";
char pass[] = "noturwifi";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin
  
 }
  
void loop()
{
  
  Blynk.run();
  
}

BLYNK_WRITE(V2)
{
  servo.write(180);
  Serial.print("Regulator off                             ");
  delay(750);
}
BLYNK_WRITE(V3)
{
  servo.write(0);
  Serial.print("Regulator on                              ");
  delay(750);
}
