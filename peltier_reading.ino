#include <Adafruit_MAX31855.h>
#include <SPI.h>

int maxDO =  3;
int maxCS = 4;
int maxCLK = 5;
//Create a MAX31855 reference and tell it what pin does what
Adafruit_MAX31855 kTC(maxCLK, maxCS, maxDO);


void setup() {
  Serial.begin(9600);
  // The MAX31855 needs a little time to stabilize
  delay(500);
}

void loop() {   
  analogWrite(9, 51);
  Serial.print("C = "); 
  Serial.println(kTC.readCelsius());
  // delay so it doesn't scroll too fast.
  delay(1000);
}
