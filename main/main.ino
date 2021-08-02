#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
/*Voice files needed:
successVoice  /track001.mp3
GameOverVoice  /track002.mp3
startUpVoice  /track003.mp3
SlideIt Voice  /track004.mp3
SpinItVoice    /track005.mp3
TouchITVoice   /track006.mp3

 * 
 * 
 * 
 */

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;





 
// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  -1      // VS1053 reset pin (output)
#define BREAKOUT_CS     -1     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  //Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

  
#define slidePin 2
#define spinPin A2 


int randNum;
boolean success;
int gameSpeed;
int score;



void setup() {

  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  

  
  // put your setup code here, to run once:
  randomSeed(analogRead(0)); //need to know empty analog pin

  //startUpUI();
  //startUpVoice();

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
    // list files
  //printDirectory(SD.open("/"), 0);
  //voice("filename");
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);








  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");




  pinMode(slidePin, INPUT);
  pinMode(spinPin, INPUT);
  
  //waitForStartbuttonPress();
  voice("/track003.mp3");
  gameSpeed=100;
  score=0;



  waitforStart();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  randNum=random(1,3);

  switch(randNum)
  {
    case 1:
      success=touchIt();
      break;
    case 2:
      success=spinIt();
      break;
    case 3:
      success=slideIt();
      break;        
  }
 //successvoice
  voice("/track001.mp3");
 if(success==false)
 {
  endGame();
 }
 gameSpeed--;

}



boolean touchIt()
{
  //touch it voice
  voice("/track006.mp3");
  Serial.write("touch It!!");
  for(int i=0;i<gameSpeed;i++)
  {
    currtouched = cap.touched();

    for (uint8_t i=0; i<12; i++) 
    {
      // it if *is* touched and *wasnt* touched before, alert!
      if ((currtouched & _BV(i))) {
        Serial.print(i); Serial.println(" touched");
        return true;
      }
    }
    delay(100);
  }
  return false;  
}

boolean spinIt()
{
  //spin it voice
    voice("/track005.mp3");
    Serial.write("spin It!!");
    
    int temp=analogRead(spinPin);
   //slideIt voice
    for(int i=0;i<gameSpeed;i++)
    {
      if(abs(temp-analogRead(spinPin))>300)
       {
        return true;
        score++;
       }
       delay(100);
    }
    
    return false;  
}

boolean slideIt()
{
  int temp=(int)digitalRead(slidePin);
  Serial.write("slide It!!");
  voice("/track004.mp3");
 //slideIt voice
 
  for(int i=0;i<gameSpeed;i++)
  {
    if(abs(temp-(int)digitalRead(slidePin))>=1)
     {
      return true;
      score++;
     }
     delay(100);
  }
  return false;
}

void voice(String fileName) //format: /track001.mp3
{
  const char *cstr = fileName.c_str();
  
  musicPlayer.playFullFile(cstr);
}
void endGame()
{
  //gameoverVoice
  //display final score
  voice("/track002.mp3");
  Serial.write("Game Over! score:"+ score);
  //wait for start button press
  waitforStart();
  score=0;
  gameSpeed=100;
  
}

void waitforStart()
{
    int temp=(int)digitalRead(slidePin);
  while(1)
  {
     if(abs(temp-(int)digitalRead(slidePin))>=1)
     {
        break;
     }
  }
}
