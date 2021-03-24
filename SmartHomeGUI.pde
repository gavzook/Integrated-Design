//import class to set up serial connection with wiring board
import processing.serial.*;
Serial port;
color currentcolor;
int lf = 10;    // Linefeed in ASCII
//string that will hold the temperature
String strTemp;
boolean locked = false;
//Buttons for appliances
Button AC_on_button;
Button AC_off_button;
Button Hum_on_button;
Button Hum_off_button;
Button Intruder_button;
int intruder;

void setup() {
   //set up window
   size(1000, 450);
   color baseColor = color(255, 255, 255);
   currentcolor = baseColor;
   // List all the available serial ports in the output pane.
   // You will need to choose the port that the Wiring board is
   // connected to from this list. The first port in the list is
   // port #0 and the third port in the list is port #2.
   println(Serial.list());
   // Open the port that the Wiring board is connected to (in this case 1
   // which is the second open port in the array)
   // Make sure to open the port at the same speed Wiring is using (9600bps)
   
   port = new Serial(this, Serial.list()[1], 9600);
   port.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  strTemp = port.readStringUntil(lf);
  strTemp = null;
  //allows for an easier to read temperature
   //frameRate(1);
   //set text size and color
   textSize(32);
   fill(0, 0, 0);
   //defines buttons
   AC_on_button = new Button("AC On", 600, 30, 300, 50);
   AC_off_button = new Button("AC Off", 600, 100, 300, 50);
   Hum_on_button = new Button("Humidifier On", 600, 170, 300, 50);
   Hum_off_button = new Button("Humidifier Off", 600, 240, 300, 50);
   Intruder_button = new Button("Accept", 100, 250, 200, 50);
   background(currentcolor);
   
}

void draw() {
   //background(currentcolor);
   //stroke(255);
   AC_on_button.Draw(218,141); //<>//
   AC_off_button.Draw(218,141);
   Hum_on_button.Draw(218,141);
   Hum_off_button.Draw(218,141);
   update();
   
}

 void update() {
   
   if(port.available()>0){
    //70 is the ascii for F
    strTemp = port.readStringUntil(70);
    intruder = port.read();
    if(intruder==73){
    fill(0);
    stroke(0);
    text("Intruder Alert!",200,200);
     //print("Intruder Alert!");
     Intruder_button.Draw(218,141);
    }
   if(strTemp != null){
     fill(255);
    stroke(255);
    rect(0, 0, 400, 80, 10);
    //background(currentcolor);
    fill(0);
    stroke(0);
    text(strTemp,200,40);
     //print(strTemp);
     } //<>//
    }
    if(mousePressed){
      if(AC_on_button.MouseIsOver()){
        port.write('A');
        AC_on_button.Draw(200,130);
      }if(AC_off_button.MouseIsOver()){
        port.write('B');
        AC_off_button.Draw(200,130);
      }if(Hum_on_button.MouseIsOver()){
        port.write('C');
        Hum_on_button.Draw(200,130);
      }if(Hum_off_button.MouseIsOver()){
        port.write('D');
        Hum_off_button.Draw(200,130);
      }if (Intruder_button.MouseIsOver()){
        fill(255);
        stroke(255);
        rect(90, 190, 400, 200, 10);
      }
    }
  }

class Button {
  String label;
  float x;    // top left corner x position
  float y;    // top left corner y position
  float w;    // width of button
  float h;    // height of button
  
  Button(String labelB, float xpos, float ypos, float widthB, float heightB) {
    label = labelB;
    x = xpos;
    y = ypos;
    w = widthB;
    h = heightB;
  }
  
  void Draw(int fillColor, int strokeColor) {
    fill(fillColor);
    stroke(strokeColor);
    rect(x, y, w, h, 10);
    textAlign(CENTER, CENTER);
    fill(0);
    text(label, x + (w / 2), y + (h / 2));
  }
  
  boolean MouseIsOver() {
    if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h)) {
      return true;
    }
    return false;
  }
  
  
}
