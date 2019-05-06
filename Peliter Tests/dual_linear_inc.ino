// Test 1 
// 5-5-2019
// For:
//	Peltier measurments for both wet and dry tests
//
//	Description: This test runs both peliters at a linearly increasing voltage
//		increasing their tempuratures as the same pace
//		Reads the corrisponding tempurature outputs

#include <Adafruit_MAX31855.h>
int maxDO = 5;
int maxCS = 6;
int maxCLK = 7;
int maxDO2 = 2;
int maxCS2 = 3;
int maxCLK2 = 4;

//create a max31855 reference and tell it what pin does what
Adafruit_MAX31855 thermoOne(maxCLK, maxCS, maxDO);
Adafruit_MAX31855 thermoTwo(maxCLK2, maxCS2, maxDO2);

int count = 0;
float arduinoV;

void setup() {
    Serial.begin(9600);
    // The MAX31855 needs a little time to stabilize
    delay(500);
}

void loop() {
    delay(2000);
	Serial.println("Start Test ");

    for (unsigned char V = 0; V < 256; V++) {  //loop that sets Arduino voltage on scale from 0 to 5 V and changes mossfet
        analogWrite(9, V);     //write the voltage to the first mosfet
		analogWrite(10, V);     //write to the second Mosfet

		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
        Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print(", ");

		Serial.print(V);
		Serial.println();
		count++;

        delay(5000);           //delay  5 sec 
	}


	// delay so it doesn't scroll too fast.
	delay(1000);
}