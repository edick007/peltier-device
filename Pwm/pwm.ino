/*
 * Code For controlling a pwm utilizing the analog write function 
 * Purpose:
 *  create a meaurable range of tempuratures with a thermocouple
 *  dev: Ed
 *  
 *  Components:
 *  Board: Nano
 *  Peltier:
 *  Thermometer
 *  
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
char max = 10;
double outputValue[10] = {.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5};        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}
double actualinput(double data){
  double actual;
    actual = data/5*255;
    return actual;
}

void loop() {
   Serial.print("\n Input Voltages and Readings from Peltier: ");
  for(char i = 0; i < max;  i++){
    double data = actualinput(outputValue[i]); //pwm high to the peltier
    analogWrite(analogOutPin, data);
      Serial.print("\n Voltage (V) = ");
      Serial.print(outputValue[i]);
      Serial.print("        Temperature (C) = ");
      Serial.print("\n PWM input = ");
      Serial.print(data);
    delay(5000);
  }
 



  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
