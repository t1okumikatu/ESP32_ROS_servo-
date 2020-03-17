
#include "esp_system.h"

void setup() {
  Serial.begin(115200);
  ledcSetup(0,50,10);//0ch50hz10bit
  ledcAttachPin(15,0);//15pin0ch
  }

int mini=-10;//左端
int maxi=167;//右端
int n=mini;
void loop() {
  ledcWrite(0,n);
  n+=15;
  if (n>maxi) n=mini;
  delay(500);
  Serial.println(n);
}
