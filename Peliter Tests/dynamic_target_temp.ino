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

#define hot_target  75    // target tempuratures set before running
#define cold_target 50

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

//	curr_diff_hot 
//		calculates and returns the difference from the target tempurature and the current for hot side
double cur_diff_hot() {
	double hot_current;
	hot_current = thermoOne.readCelsius();

	return (hot_target - hot_current);
}

//	curr_diff_cold
//		calculates and returns the difference from the target tempurature and the current for cold side

double cur_diff_cold() {
	double cold_current;
	cold_current = thermoTwo.readCelsius();

	return (cold_target - cold_current);
}

//	get_to_target
//		makes peliters get to specified tempuratures
void get_to_target() {
	int count = 0;
	while (cur_diff_hot() > 5) {

		analogWrite(10, maxV); //write to the second Mosfet 255
		if (cur_diff_cold() > 5) {
			analogWrite(9, maxV); //write to the second Mosfet 255
		}
		if (cur_diff_cold() <= 0) {
			analogWrite(9, minV);
		}
		//if (count > 1000) {
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print("C, ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print(" C, cur_diff_hot: ");
		Serial.print(cur_diff_hot());
		Serial.print(", cur_diff_cold: ");
		Serial.print(cur_diff_cold());
		Serial.print("\n");

		//}
	}

	while (cur_diff_hot() > 0) {

		analogWrite(10, maxV); //slow down temp increase
		if (cur_diff_cold() > 0) {
			analogWrite(9, maxV); //write to the second Mosfet 255
		}
		if (cur_diff_cold() <= 0) {
			analogWrite(9, minV);
		}
		//if (count > 1000) {
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(" C, ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print(" C, cur_diff_hot: ");
		Serial.print(cur_diff_hot());
		Serial.print(", cur_diff_cold: ");
		Serial.print(cur_diff_cold());
		Serial.print("\n");

		if (cur_diff_hot() <= 0) {
			return;
		}

		//}
	}
}

void setup() {
	Serial.begin(9600);
	// The MAX31855 needs a little time to stabilize
	delay(500);

	Serial.print("Input target Cold tempurature in C: ");
	Serial.println(cold_target);
	//serial in tar_cold
	Serial.print("Input target Hot tempurature in C:");
	Serial.println(hot_target);
	//serial in tar_hot
	delay(1000);

	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.print("\n");

	get_to_target();   //start getting to target tempurature

	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.print("\n");

	Serial.println("Start Test \n");
}


void loop() {
	//need to set up tempurature ranges and appropriate voltages to maintain the targets
	if (cur_diff_cold() > 0) {
		analogWrite(9, maxV);
	}
	else if (cur_diff_cold() <= 0) {
		analogWrite(9, minV);
	}
	if (cur_diff_hot() > 0) {
		analogWrite(10, maxV);
	}
	else if (cur_diff_cold() < 0) {
		analogWrite(10, minV);
	}
	// do the same for over shooting
	//count++;
	//if (count > 400) {
	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.print("\n");
	count = 0;
	//}



	// delay so it doesn't scroll too fast.
	//delay(10);
}