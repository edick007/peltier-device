// Test 2
// 5-5-2019
// For:
//	Peltier measurments for both wet and dry tests
//
//	Description: This test runs the hot peltier at a linearly increasing voltage
//		increasing hot peliters tempurature while the cold peliter has no voltage
//		Reads the corrisponding tempurature outputs of both hto and cold sides

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
char minV = 0;
char maxV = 255;

void setup() {
	Serial.begin(9600);
	// The MAX31855 needs a little time to stabilize
	unsigned char flag = 0;
	delay(500);
}

void loop() {
	//delay(999);
	Serial.println("Start Test ");

	analogWrite(10, maxV);  //write to the second Mosfet hot
	analogWrite(9, minV);     //write the voltage to the first mosfet cold
	

	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.println();

	if (thermoOne.readCelsius() > 26) {
		flag = 1;
	}

	if ((thermoOne.readCelsius() < 25) && flag) {
		Serial.println(" END TEST ");
	}
	delay(999);




}


// delay so it doesn't scroll too fast.
//delay(1000);
}