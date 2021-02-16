/*Temperature sensor code
 * Put the sensor in series with a 10k resistor
 * 5V connected to thermistor and ground connected to resistor
 * Attach a wire to analog in pin 0 and connect the other end in-between the resistor and thermistor
 */
int ThermistorPin = 0; //Create variable for pin that will be used to measure the voltage inbetween the thermistor and the resistor
int Vo; //Variable to hold value read from the analog in
float R1 = 10000; //resistnace of biasing resistor
float logR2, R2, T; //Variables to be defined later
float c1 = 1.191883375e-03, c2 = 2.246315931e-04, c3 = 1.192853594e-07; //Steinhart-Hart coeffiecients

void setup() {
Serial.begin(9600); //Sets data rate in bits per second for serial data transmission to 9600
}

void loop() {

  Vo = analogRead(ThermistorPin); //Arduino will read the voltage at this point on a scale of 0(0V) to 1023(5V)
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //Voltage divider formula, finds the resistance of the thermistor
  logR2 = log(R2); //Finds the nataural log of R2 to be used in Steinhart-hart equation
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart equation
  T = T - 273.15; //convert kelvins to celcius
  T = (T * 9.0)/ 5.0 + 32.0; //convert celcius to fahrenheit

  Serial.print("Temperature: "); //prints out Temperature: to serial
  Serial.print(T); //prints out calculated temperature(T) in fahrenheit to serial
  Serial.println(" F"); //prints out  F to serial

  delay(500); //delay .5 seconds before loop starts again
}
