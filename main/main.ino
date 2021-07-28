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


int randNum;
boolean success;
int gameSpeed
void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0)); //need to know empty analog pin

  //startUpUI();
  //startUpVoice();
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
  
}
