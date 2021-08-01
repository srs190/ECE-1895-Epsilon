#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
/*Voice files needed:
successVoice
GameOverVoice
startUpVoice
SlideIt Voice
SpinItVoice
TouchITVoice

 * 
 * 
 * 
 */


 
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
#define slidePin -1
#define spinPin -1  


int randNum;
boolean success;
int gameSpeed;
void setup() {
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
  printDirectory(SD.open("/"), 0);
  voice("filename")
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);


  
  //waitForStartbuttonPress();
  //gameStartVoice();
  //SetupGameSpeed;
  gameSpeed=100;

  
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
  
 if(success==false)
 {
  endGame();
 }
 gameSpeed--;

}



boolean touchIt()
{
  //touch it voice
  for(int i=0;i<gamespeed;i++)
  {
    
  }
  return true;  
}

boolean spinIt()
{
  //spin it voice

  for(int i=0;i<gamespeed;i++)
  {
    
  }
  return true;  
}

boolean slideIt()
{

 //slideIt voice
  for(int i=0;i<gamespeed;i++)
  {
    
  }
  return true;
}

void voice(String fileName)
{
  
}
void endGame()
{
  //gameoverVoice
  //display final score
  
}
