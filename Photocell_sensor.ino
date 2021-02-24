
int light = 0; // store the current light value
int humidity = 0; // store the current humidity value


void setup() {
  
    Serial.begin(9600); //configure serial to talk to computer
    pinMode(13, OUTPUT); // configure digital pin 13 as an output
    pinMode(12, OUTPUT); // configure digital pin 12 as an output

}

void loop() {

    light = analogRead(A0); // read and save value from Photocell
    /*humidity = analogRead(A2);*/ // read and save value from HS
    
    Serial.println(light); // prints the voltage after photocell
    /*Serial.println(humidity);*/ //print current humity value

      digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
    if(light > 500) //32000+ lux
    { 
        Serial.println("Bright"); //prints threshold value on screen
        digitalWrite(13,LOW); //turn red LED off
        digitalWrite(12,LOW); // turn yellow LED off
    }
    else if(light > 11 && light < 300) // Dim light: 5-32000 lux
    { 
       Serial.println("Dim Light!"); //50-32000 lux
       digitalWrite(13, HIGH); // turn red LED on
       digitalWrite(12,LOW);  // turn yellow LED off
    }
    else if(light < 11)// 5 lux
    {
        Serial.println("Dark Room"); //Dark room under 5 lux
        digitalWrite(13,HIGH); // Turn red LED on
        digitalWrite(12,HIGH); // Turn yellow LED on
    }
    

}
