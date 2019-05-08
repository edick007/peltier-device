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
int maxDO2 = 11;
int maxCS2 = 12;
int maxCLK2 = 13;

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

//	function get_max
//	returns an appropriate voltage to get smoother tempurature consistancy
double get_maxV(double temp, double type) {
	if ((temp >= 20) && (temp < 25)) {
		return 25;
	}
	else if ((temp >= 25) && (temp < 30)) {
		return 77;
	}
	else if ((temp >= 30) && (temp < 35)) {
		return 50;
	}
	else if ((temp >= 35) && (temp < 40)) {
		if ((type == 1) && (thermoOne.readCelsius() < 30)) {		//if its hot type and not close to target go max voltage 255
			return 255;
		}
		else if ((type == 2) && (thermoTwo.readCelsius() < 30)) {
			return 255;
		}
		else { return 128; }
	}
	else if ((temp >= 40) && (temp < 45)) {
		if ((type == 1) && (thermoOne.readCelsius() < 36)) {		//if its hot type and not close to target go max voltage 255
			return 255;
		}
		else if ((type == 2) && (thermoTwo.readCelsius() < 36)) {
			return 255;
		}
		else { return 143; }
	}
	else if ((temp >= 45) && (temp < 50)) {
		if ((type == 1) && (thermoOne.readCelsius() < 42)) {		//if its hot type and not close to target go max voltage 255
			return 255;
		}
		else if ((type == 2) && (thermoTwo.readCelsius() < 42)) {
			return 255;
		}
		else { return 153; }
	}
	else if ((temp >= 50) && (temp <= 60)) {
		if ((type == 1) && (thermoOne.readCelsius() < 48)) {		//if its hot type and not close to target go max voltage 255
			return 255;
		}
		else if ((type == 2) && (thermoTwo.readCelsius() < 48)) {
			return 255;
		}
		else { return 191; }
	}
	else {
		return 255;
	}
}

//	get_to_target
//	makes peliters get to specified tempuratures
void get_to_target(double hot, double cold) {
	//Serial.println("before while");
	unsigned char hot_maxV = 0;
	unsigned char cold_maxV = 0;
	while ((cur_diff_hot(hot) > 0) || (cur_diff_cold(cold) > 0)) {
		//Serial.println("starting while");
		if (cur_diff_hot(hot) > 0) {
			hot_maxV = get_maxV(hot, 1);
			analogWrite(10, maxV);
			//Serial.println("HOT if not hot");
		}
		else if (cur_diff_hot(hot) <= 0) {
			analogWrite(10, minV);
			//Serial.println("HOT if too hot");
		}
		if (cur_diff_cold(cold) > 0) {
			cold_maxV = get_maxV(hot, 1);
			analogWrite(9, 5);
			//Serial.println("Cold if not hot");

		}
		else if (cur_diff_cold(hot) <= 0) {
			//analogWrite(9, minV);
			//Serial.println("cold if too hot");
		}
		else { Serial.println("error"); }

		//print out to the console 
		Serial.print(thermoOne.readCelsius()); //cold
		Serial.print(", ");
		//delay(100);
		Serial.print(thermoTwo.readCelsius()); //hot
		Serial.print(", ");
		Serial.print(cur_diff_hot(hot));
		Serial.print(", ");
		Serial.print(cur_diff_cold(cold));
		Serial.print(", ");
		Serial.print(hot_maxV); //hot
		Serial.print(", ");
		Serial.print(cold_maxV);
		Serial.print("\n");

		return;
	}

	if (cur_diff_hot(hot) <= 0) {
		analogWrite(10, minV);
		//Serial.println("HOT if too hot");
	}
	if (cur_diff_cold(cold) <= 0) {
		analogWrite(9, minV);
		//Serial.println("Cold if not hot");
	}


	Serial.println("return");
	return;

}


void setup() {
	Serial.begin(9600);
	// The MAX31855 needs a little time to stabilize

	delay(500);
	//hot_target = 25;
	//cold_target = 25;

	//get_to_target(hot_target, cold_target);


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
	/*
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

	*/
	unsigned char hot = 30;
	unsigned char cold = 30;

	get_to_target(hot, cold);
	//Serial.println("looped");
	Serial.print(thermoOne.readCelsius()); //cold
	Serial.print(", ");
	//delay(100);
	Serial.print(thermoTwo.readCelsius()); //hot
	Serial.print("\n");





}

