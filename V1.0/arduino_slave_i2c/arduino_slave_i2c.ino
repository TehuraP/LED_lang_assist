#include <Wire.h>
#include "SPI.h"      
#include "DMD.h" 
#include "TimerOne.h"
#include "SystemFont5x7.h"

// Change these values if you have more than one DMD connected
#define DISPLAYS_ACROSS 1   
#define DISPLAYS_DOWN 1
  
#define I2C_SLAVE_ADDR 8

char receivedData[32];  // Buffer to store received data

DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN);

String string1;
String string2;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void scrollText(String dispString, String dispString1) 
{
  dmd.clearScreen( true );
  dmd.selectFont(SystemFont5x7);
  char newString[256];
  char newString1[256];
  int sLength = dispString.length();
  int sLength1 = dispString1.length();
  dispString.toCharArray( newString, sLength+1 );
  dispString1.toCharArray( newString1, sLength1+1 );
  
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  int scroll_length = 5*max(sLength, sLength1);
  
  int j = 0;
  while(j <= scroll_length ){
    if ( ( timer+20 ) < millis() ) {
      dmd.drawMarquee(newString,sLength, 16 - j , 0 );
      dmd.drawMarquee(newString1,sLength1,16 - j , 9 );
      j++;
      timer=millis();
      delay(70);
    }
  }
}

void setup() {
  Wire.begin(I2C_SLAVE_ADDR);  // Join I2C bus as a slave
  Wire.onReceive(receiveEvent);  // Register event handler
  Serial.begin(9600);  // Start serial communication for debugging

  // Period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.initialize(5000);  

  // Attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  Timer1.attachInterrupt(ScanDMD);  
  
  // True is normal (all pixels off), false is negative (all pixels on)
  dmd.clearScreen(true);            
}

void loop() {
  String eng = string1;
  String deu = string2;
  int REPETITIONS = 3;
  for (int i = 0; i < REPETITIONS; i++){
    scrollText(deu, eng);
  }
}

void receiveEvent(int howMany) {
int i = 0;
  while (Wire.available() && i < sizeof(receivedData) - 1) {
    receivedData[i++] = Wire.read();  // Read byte by byte from I2C
  }
  receivedData[i] = '\0';  // Null-terminate the string

  // Convert received data to a String object
  String receivedString = String(receivedData);

  // Split the string at the delimiter (comma in this case)
  int delimiterIndex = receivedString.indexOf(',');
  string1 = receivedString.substring(0, delimiterIndex);  // First string
  string2 = receivedString.substring(delimiterIndex + 1);  // Second string

  // Print the two strings to Serial
  Serial.println("Received String 1: " + string1);
  Serial.println("Received String 2: " + string2);

}