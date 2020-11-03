#include "HX711.h"

#define DOUT 3
#define CLK 2

HX711 loadCell;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  loadCell.begin(DOUT, CLK);
  loadCell.set_scale();
  loadCell.tare();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    Serial.println(loadCell.get_units(10));
  }
}
