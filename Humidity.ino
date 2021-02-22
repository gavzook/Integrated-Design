/*
 * Idea: Fully charge the capacitor and resistor circuit to 5RC
 * Then discharge the capacitor through the humidity sensor and measure the amount of time that takes
 * The discharge time can be used in t=RC to find the resistance of the humidity sensor
 * Then fully discharge the capacitor through the resistor(this might be screwing stuff up)
 * Then charge capacitor through negative end
 * Then discharge through humidity sensor
 * Then fully discharge the capacitor through the resistor(this might be screwing stuff up)
 * Restart proccess
 * 
 * Circuit: capacitor and resistor in series, with posPin at end of resistor and negPin at end of capacitor
 * Humidity sensor with one wire at same node as resistor and capacitor and another on its own connected to humidity Pin
 *  posPin --------------resistor----+-------------+
 *                                   |             |
 *                                capacitor      Humidity sensor
 *                                   |             |
 * negPin ---------------------------+             |
 *                                                 |
 * humidityPin ------------------------------------+
 */
int posPin = 2;
int negPin = 4;
int humidityPin = 7;
float chargeTime = 0.5; //5RC seconds
unsigned long dischargeTime=0;
unsigned long previousMillis=0;
float humidity;
float humidityResistance;
float capacitor = 0.000001;

void setup() {
Serial.begin(9600);

}

void loop(){
//charge up capacitor  
pinMode(posPin,OUTPUT);
pinMode(negPin,OUTPUT);
pinMode(humidityPin,INPUT);
digitalWrite(posPin,HIGH);
digitalWrite(negPin,LOW);
delay(chargeTime);

//discharge capacitor through humidity sensor
pinMode(posPin,INPUT);
pinMode(humidityPin,OUTPUT);
digitalWrite(humidityPin,LOW);
unsigned long currentMillis = millis();

//measure discharge time
while (digitalRead(posPin)!=LOW){}
dischargeTime=(currentMillis-previousMillis);
previousMillis = currentMillis;
Serial.println(dischargeTime); //test to see if working
//(discharge time)/5 =RC
humidityResistance = ((((float)dischargeTime)/5)/capacitor);
Serial.println(humidityResistance);

//fully discharge capacitor
pinMode(posPin,OUTPUT);
digitalWrite(posPin,LOW);
pinMode(humidityPin,INPUT);
delay(chargeTime);

//charge the capacitor negative
digitalWrite(negPin,HIGH);
delay(chargeTime);

//negative discahrge through humidity sensor
pinMode(posPin,INPUT);
pinMode(humidityPin,OUTPUT);
digitalWrite(humidityPin,HIGH);
delay(dischargeTime); //if dischargeTime, capacitor doesn't seem to fully discharge, if chargeTime, kinda works

//fully discharge capacitor
pinMode(posPin,OUTPUT);
pinMode(humidityPin,INPUT);
digitalWrite(posPin,HIGH);
delay(chargeTime);

}
