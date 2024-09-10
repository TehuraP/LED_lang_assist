/**
 * @led_vocab.ino
 *
 * Outputs German words with English translations in a 32x16 LED Matrix
 * @version 0.1
 * @date 20-08-2024
 * @author A. Saikia
 *
 */

#include "SPI.h"      
#include "DMD.h" 
#include "TimerOne.h"

// you can remove the fonts if unused
//#include "Adafruit5x7.h"
#include "SystemFont5x7.h"

/* change these values if you have more than one DMD connected */
#define DISPLAYS_ACROSS 1   
#define DISPLAYS_DOWN 1       

#define ARRAYSIZE 40

// English translations array 
const char *const eng[ARRAYSIZE] = { "airport", "why",  "noon", "difficult", "fruit", "other", "answer", "to travel", "to read", "funny",
         "assignment" , "Earth", "any", "condition", "solution","profession", "place" , "money", "beginning" , "yellow" ,
         "to get" , "to take", "train", "short", "airplane", "simple", "the same", "call" , "to be called", "tired", 
         "sad", "finally" , "quietly", "to give" , "maybe", "cheap", "expensive", "window", "still", "always"};

// German words array 
const char *const deu[ARRAYSIZE] = { "der Flughafen", "warum",  "Mittag", "schwierig", "das Obst", "andere", "die Antwort",  "reisen", "lesen" , "lustig",
         "die Aufgabe", "die Erde", "jeder", "der Zustand", "die L^sung", "der Beruf" , "der Ort" , "das Geld" , "der Anfang" , "gelb",
         "erhalten", "nehmen", "der Zug", "kurz" ,"das Flugzeug" , "einfach", "gleich", "der Anruf", "hei`en", "m_de", 
         "traurig", "endlich", "ruhig", "geben", "vielleicht", "billig", "teuer", "das Fenster", "noch" , "immer"};
DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN);

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

void setup()
{
  Serial.begin(9600);

  // Period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker
  Timer1.initialize( 5000 );  

  // Attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  Timer1.attachInterrupt( ScanDMD );

  // True is normal (all pixels off), false is negative (all pixels on)
  dmd.clearScreen( true );            
  
}

void loop(){
  int REPETITIONS = 2;
  int id = random(0, ARRAYSIZE - 1);
  for (int i = 0; i < REPETITIONS; i++){
    scrollText(deu[id], eng[id]);
  }
}
