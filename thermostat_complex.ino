#include <LiquidCrystal_I2C.h>
#include <dht.h>

#define tempPin A0
int tup = 7; //Temp up button
int tdown = 9; //Temp down button
boolean lightMe; //Light up LED
float temp; //Raw temp value
float settemp; //Desired temp
int defC = 19; //Default Cel.
int upstate = 0; //Temp up button state
int downstate = 0; //Temp down button state 
int ledPin = 13; //LED's pin

LiquidCrystal_I2C lcd(0x27,  16, 2);
dht DHT;

void setup() {
  Serial.begin (9600); 
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("hello, world!"); 
  pinMode(tup, INPUT); 
  pinMode(tdown, INPUT); 
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  upstate = digitalRead(tup); //Read state of temp up
  downstate = digitalRead(tdown); //Read state of temp down

	int readData = DHT.read11(tempPin);
  Serial.print(readData);
  float t = DHT.temperature;        // Read temperature
  temp = t; //Calculate temp in C


  if (upstate == LOW) { //if up button is pressed,
    defC = defC + 1; //Raise desired C by 1
  }
  if (downstate == LOW) { //if down button is pressed
    defC = defC - 1; //lower desired C by 1
  }

  lcd.setCursor(0, 0);
  lcd.print("Now: ");
  lcd.print (t);  // Print the current temp in f
  lcd.print (" degC");
  delay(255);

  lcd.setCursor (0, 1); // set the cursor to 0,1
  lcd.print ("Desired: "); // Print set to and your ideal temperature in f
  lcd.print (defC);
  lcd.print (" degC");

  lightUp(temp, defC); //run custom light up command
  
  if (lightMe == true) { //if light up is true
    // Serial.print("Lighted led!");
    digitalWrite(ledPin, HIGH); //turn on LED
  } else if (lightMe == false) { //otherwise
    Serial.print("Optimal temperature!");
    digitalWrite(ledPin, LOW); //turn off LED
  }

} 

boolean lightUp(float act, int desC) { //Decides if LED should light up, imports current temp, desired C
  // Serial.print(act);
  // Serial.print(desC);
  if (act < desC) { //if the actual is less than the desired C value
    lightMe = true; //Turn on the LED
  } else { //otherwise
    lightMe = false; //Turn the LED off
  }
  return lightMe; //return that value
}