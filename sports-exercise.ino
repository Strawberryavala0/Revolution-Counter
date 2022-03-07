int potPin = A7;
const int numReadings = 20;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int spins = 0;                  //# of revolutions
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//neopixels are connected to digital 3, which is pin 2 on the ATtiny IC
#define PIN 5
#define NUM_LEDS 4 //number of leds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(potPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  
  Serial.println(average);

if (920 < average){
  Serial.println("COUNT");
  strip.setPixelColor(spins, 150, 0, 150); //set to purple, takes RGB vals 0-255
  strip.show();
  delay(1000);
  if (3 > spins){
    spins++;
  }
}

if (average < 700){
  Serial.println("START OVER");
     //turn off all at the same
     //for(uint16_t i=strip.numPixels(); i<0; i--) {
        strip.setPixelColor(0, 0, 0, 0); //set to purple, takes RGB vals 0-255  
        strip.setPixelColor(1, 0, 0, 0); //set to purple, takes RGB vals 0-255  
        strip.setPixelColor(2, 0, 0, 0); //set to purple, takes RGB vals 0-255  
        strip.setPixelColor(3, 0, 0, 0); //set to purple, takes RGB vals 0-255  
     //}
     strip.show();
     spins = 0;
}



}
