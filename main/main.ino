
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

  
 if(success==false)
 {
  endGame();
 }
 gameSpeed--;

}



boolean touchIt()
{

  return true;  
}

boolean spinIt()
{

  return true;  
}

boolean slideIt()
{


  return true;
}

void voice(String fileName)
{
  
}
void endGame()
{

  
}
