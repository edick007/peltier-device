// Test 4	Controlling tempurature dyanamicaly
// 5-5-2019
// For:
//	Peltier measurments for both wet and dry tests
//
//	Description: This test runs	both peltiers depending on the target tempurature.
//		User sets the target temurature through the terminal. The peltiers go to the 
//		target slowly. Once reached, if the target temp is higher than actaul then 
//		votage increasese. If the target tempurature is lower than actaul the voltage 
//		drops to 0 to cool down.
//		
//		Reads the corrisponding tempurature outputs of both hto and cold sides

#define maxV 255
#define minV 0

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

//	curr_diff_hot 
//		calculates and returns the difference from the target tempurature and the current for hot side
double cur_diff_hot(double hot_target) {
	double hot_current;
	hot_current = thermoTwo.readCelsius();

	return (hot_target - hot_current);
}

//	curr_diff_cold
//		calculates and returns the difference from the target tempurature and the current for cold side

double cur_diff_cold(double cold_target) {
	double cold_current;
	cold_current = thermoTwo.readCelsius();

	return (cold_target - cold_current);
}

void get_to_target(double cold, double hot) {
	while (cur_diff_hot() > 10) {
		analogWrite(10, maxV) //write to the second Mosfet 255
	}
	while (cur_diff_hot() > 2) {
		analogWrite(10, maxV / 2); //slow down temp increase
	}
	return 0;
}
void loop() {
	double tar_cold;
	double tar_hot;

	delay(2000);
	Serial.println("Start Test \n");

	Serial.println("Input target cold tempurature in C: ");
	//serial in tar_cold
	Serial.prinln("Input target Hot tempurature in C:");
	//serial in tar_hot

	for (unsigned char V = 0; V < 256; V++) {  //loop that sets Arduino voltage on scale from 0 to 5 V and changes mossfet
		//analogWrite(9, V);     //write the voltage to the first mosfet
		analogWrite(10, V);  //write to the second Mosfet

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