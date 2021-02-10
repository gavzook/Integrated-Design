/*Temperature sensor code
 * Put the sensor in series with a 10k resistor
 * 5V connected to thermistor and ground connected to resistor
 * Attach a wire to analog in pin 0 and connect the other end in-between the resistor and thermistor
 */
int ThermistorPin = 0; //Create variable for pin that will be used to measure the voltage inbetween the thermistor and the resistor
int Vo; //
float R1 = 10000; //resistnace of biasing resistor
float logR2, R2, T; //Var
float c1 = 1.115032760e-03, c2 = 2.365805377e-04, c3 = 0.7678884425e-07; //Steinhart-Hart coeffiecients

void setup() {
Serial.begin(9600);
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); 
  T = T - 273.15; //convert kelvins to celcius
  T = (T * 9.0)/ 5.0 + 32.0; //convert celcius to fahrenheit

  Serial.print("Temperature: "); //prints out Temperature: to serial
  Serial.print(T); //prints out calculated temperature(T) in fahrenheit to serial
  Serial.println(" F"); //prints out  F to serial

  delay(500);
}
