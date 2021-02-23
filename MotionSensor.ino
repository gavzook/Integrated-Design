/*
 * Connect Vcc to 5V, Trig to pin 3, Echo to pin 2, and GND to ground
 * For the sensor to work, the trigger pin needs a 10 us pulse to start
 * An 8 cycle burst at 40 kHz is then sent from the sensor
 * The echo pin then listens for the return of the signal
 */

int echoPin = 2; //pin to plug the echo into
int trigPin = 3; //pin to plug the trig into
unsigned long duration; 
float distanceCM; 
float distanceIN;

void setup() {
  pinMode(trigPin, OUTPUT); //sets trigPin as an output pin
  pinMode(echoPin, INPUT);  //sets echoPin as an input pin
  Serial.begin(9600); //Sets the baud rate for the serial output to 9600
}
void loop() {
  //The trigger pin needs to have a 10 us pulse applied to it to start the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW); //Turns off the pulse
  duration = pulseIn(echoPin, HIGH); //Resords the time it takes in us for echoPin to go from low to high
  distanceCM = duration * 0.0343 / 2; //Takes the time it took for the signal to return and multiplies it by the speed of sound in cm/us over 2
  //the division by 2 is because the sound has to go the distsnace to the object and then come back
  distanceIN = distanceCM*0.393701; //converts cm to in
  Serial.print("Distance: "); //Prints out Distance: to the serial
  Serial.print(distanceIN); //Prints out the distance of an object to the sensor in inches
  Serial.println(" in"); //Prints out the specified units
  delay(500); //slows down print out for readability
}
