/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This is the calibration sketch. Use it to determine the calibration_factor that the main example uses. It also
 outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.

 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Use this calibration_factor on the example sketch

 This example assumes pounds (lbs). If you prefer kilograms, change the Serial.print(" lbs"); line to kg. The
 calibration factor will be significantly different but it will be linearly related to lbs (1 lbs = 0.453592 kg).

 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND

 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/

#include "HX711.h"
#include <LiquidCrystal.h>// include the library code

#define DOUT  3
#define CLK  2
#define BTN 53

HX711 scale;
LiquidCrystal lcd(51,49,47,45,43,41);

int tim = 2000;
int pushed = 0;
void setup() {
  Serial.begin(9600);

  scale.begin(DOUT, CLK);
  scale.set_scale(1029);
  scale.tare(); //Reset the scale to 0
  
  //setup the LCD
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 

  Serial.println("Readings:");

  pinMode(BTN, INPUT);
}

void loop() 
{
  pushed = digitalRead(BTN);
  if(pushed == HIGH)
  {
    scale.tare();
  }
  lcd.setCursor(0,0);
  lcd.print("Weight: ");
  lcd.print(scale.get_units(3),5);
  lcd.setCursor(0,1);
  lcd.print("grams");
  delay(tim);
  lcd.clear();

  Serial.print("Reading: ");
  Serial.print(scale.get_units(1), 1);
  Serial.print(" grams");
  Serial.println();
}
