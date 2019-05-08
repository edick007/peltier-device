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

char hot_target = 25;   // target tempuratures set before running
char cold_target = 25;

//create a max31855 reference and tell it what pin does what
Adafruit_MAX31855 thermoOne(maxCLK, maxCS, maxDO);
Adafruit_MAX31855 thermoTwo(maxCLK2, maxCS2, maxDO2);

int count = 0;
char minV = 0;
char maxV = 255;
char flag = 0;
char test = 0;

//	curr_diff_hot 
//		calculates and returns the difference from the target tempurature and the current for hot side
double cur_diff_hot(double hot) {
	double hot_current;
	hot_current = thermoOne.readCelsius();

	return (hot - hot_current);
}

//	curr_diff_cold
//		calculates and returns the difference from the target tempurature and the current for cold side

double cur_diff_cold(double cold) {
	double cold_current;
	cold_current = thermoTwo.readCelsius();

	return (cold - cold_current);
}

//	get_to_target
//	makes peliters get to specified tempuratures
void get_to_target(double hot, double cold) {


	while ((cur_diff_hot(hot) > 0) || (cur_diff_cold(cold) > 0)) {
		if (cur_diff_hot(hot) > 0) {
			analogWrite(10, maxV);
		}
		else if (cur_diff_hot(hot) <= 0) {
			analogWrite(minV);
		}
		if (cur_diff_cold(cold) > 0) {
			analogWrite(9, maxV);
		}
		else if (cur_diff_cold(hot) <= 0) {
			analogWrite(9, minV);
		}
		else { Serial.println("error"); }

		//print out to the console 
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print(", ");
		Serial.print(cur_diff_cold(cold));
		Serial.print(", ");
		Serial.print(cur_diff_hot(hot));
		Serial.print("\n");

		if ((cur_diff_hot(hot) <= 0) && (cur_diff_cold(cold) <= 0)) {
			return;
		}

		//}
	}
}


void setup() {
	Serial.begin(9600);
	// The MAX31855 needs a little time to stabilize

	delay(500);
	hot_target = 25;
	cold_target = 25;

	get_to_target(hot_target, cold_target);

	for (int i; i < 10; i++) {
		if (cur_diff_cold(cold_target) > 0) {
			analogWrite(9, maxV);
		}
		else if (cur_diff_cold(cold_target) <= 0) {
			analogWrite(9, minV);
		}
		if (cur_diff_hot(hot_target) > 0) {
			analogWrite(10, maxV);
		}
		else if (cur_diff_cold(cold_target) < 0) {
			analogWrite(10, minV);
		}
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print("\n");
	}
	// do the same for over shooting
	//count++;
	//if (count > 400) {


	Serial.println("Start Test 1");
	test = 1;

}

void loop() {
	//delay(999);

	//test for hot inc and cool down

	/*while (test == 1) {

	if (flag == 0) {
		analogWrite(10, maxV);  //write to the second Mosfet hot
		analogWrite(9, minV);     //write the voltage to the first mosfet cold
	}
	else if (flag == 1) {
		analogWrite(10, minV);  //write to the second Mosfet hot
		analogWrite(9, minV);     //write the voltage to the first mosfet cold
	}

	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.println();

	if ((thermoOne.readCelsius() >= 90) && (thermoOne.readCelsius() < 90.5)) {
		flag = 1;
		Serial.println("Cool Down");
	}

	if ((thermoOne.readCelsius() <= 25) && (flag == 1)) {
		Serial.println(" END TEST 1");
		test = 2;
		Serial.println(" Start TEST 2");
		flag = 0;
	}
	delay(800);

	}


	while (test == 2) {

		if (flag == 0) {
			analogWrite(10, maxV);  //write to the second Mosfet hot
			analogWrite(9, maxV);     //write the voltage to the first mosfet cold
		}
		else if (flag == 1) {
			analogWrite(10, minV);  //write to the second Mosfet hot
			analogWrite(9, minV);     //write the voltage to the first mosfet cold
		}

		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.println();

		if ((thermoOne.readCelsius() >= 90) && (thermoOne.readCelsius() < 90.5)) {
			flag = 1;
			Serial.println("Cool Down");
		}

		if ((thermoOne.readCelsius() < 25) && (flag == 1)) {
			Serial.println(" END TEST 2");
			test = 3;

		}
		delay(800);


	}
	*/

	if (test == 3) {


	}
	unsigned char hot = 50;
	unsigned char cold = 25;
	get_to_target(hot, cold);

	while ((cur_diff_cold(cold) > 0) || (cur_diff_hot(hot) > 0)) {
		if (cur_diff_cold(cold) > 0) {
			analogWrite(9, maxV);
		}
		else if (cur_diff_cold(cold) <= 0) {
			analogWrite(9, minV);
		}
		if (cur_diff_hot(hot) > 0) {
			analogWrite(10, maxV);
		}
		else if (cur_diff_cold(cold) < 0) {
			analogWrite(10, minV);
		}
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print("\n");
		delay(800);
	}

	Serial.println("start test 3");
	hot_target = 50;
	cold_target = 90;
	get_to_target(hot_target, cold_target);


	Serial.println("Cool Down");

	while (test == 3) {
		analogWrite(9, minV);
		analogWrite(10, minV);

		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print("\n");

		if ((thermoOne.readCelsius() < 30) && thermoTwo.readCelsius() < 30) {
			Serial.println("End test 3");
			break;

		}

		delay(900);

	}




}

