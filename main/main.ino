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



#define buzzer A1
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


  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");




  pinMode(slidePin, INPUT);
  pinMode(spinPin, INPUT);
  pinMode(buzzer, OUTPUT);
  //waitForStartbuttonPress();

  
 piezoStart();
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
  piezoRight();
 if(success==false)
 {
  endGame();
 }
 gameSpeed--;

}



boolean touchIt()
{
  //touch it voice
  piezoTouch();
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
    piezoSpin();
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
  piezoSlide();
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

void piezoRight(void) //format: /track001.mp3
{

  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void piezoSlide() //format: /track001.mp3
{

  tone(buzzer, 466); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void piezoSpin() //format: /track001.mp3
{

  tone(buzzer, 499); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void piezoTouch() //format: /track001.mp3
{

  tone(buzzer, 523); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void piezoStart() //format: /track001.mp3
{

  tone(buzzer, 2000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void piezoEnd() //format: /track001.mp3
{

  tone(buzzer, 146); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

}
void endGame()
{
  //gameoverVoice
  //display final score
  piezoEnd();
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
