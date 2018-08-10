//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/12V_DC_Motor_146rpm_w/Encoder(SKU:FIT0277)
//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/DFRduino_Romeo-All_in_one_Controller_V1.1(SKU:DFR0004)
//Utilizou-se o Codigo01_Encoders
/*
  Pay attention to the interrupt pin,please check which microcontroller you use.
  http://arduino.cc/en/Reference/AttachInterrupt
*/



//##################################  ENCODERS  ##################################

//#####  Motor Direito
const byte encoderDpinA = 2; //A pin -> the interrupt pin 2
const byte encoderDpinB = 8; //B pin -> the digital pin 8
byte encoderDPinALast;
int durationD;               //the number of the pulses
boolean DirectionD;          //the rotation direction

//#####  Motor Esquerdo
const byte encoderEpinA = 3; //A pin -> the interrupt pin 3
const byte encoderEpinB = 9; //B pin -> the digital pin 9
byte encoderEPinALast;
int durationE;               //the number of the pulses
boolean DirectionE;          //the rotation direction


//##################################  PWM CONTROL MODE  ##################################

//#####  Standard PWM DC control
int E1 = 5;  //M1 Speed Control
int E2 = 6;  //M2 Speed Control
int M1 = 4;  //M1 Direction Control
int M2 = 7;  //M2 Direction Control



//###############################################################################
//##################################  SETUP()  ##################################

void setup() {

}




//##############################################################################
//##################################  LOOP()  ##################################

void loop() {

  //############################################################################
  //#####  PARAR MOTOR  #####
  stop();
  delay(100000);
}




//#############################################################################
//################################## FUNCOES ##################################

//#################  Encoders  #################
void EncoderInit()
{
  //Motor D
  DirectionD = true;//default -> Forward
  pinMode(encoderDpinB, INPUT);
  attachInterrupt(0, wheelSpeedD, CHANGE);//int.0
  //Motor E
  DirectionE = true;//default -> Forward
  pinMode(encoderEpinB, INPUT);
  attachInterrupt(1, wheelSpeedE, CHANGE);//int.1
}

//#####  Velocidade encoder roda DIREITA
//Motor D
void wheelSpeedD()
{
  int Lstate = digitalRead(encoderDpinA);
  if ((encoderDPinALast == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(encoderDpinB);
    if (val == LOW && DirectionD)
    {
      DirectionD = false; //Reverse
    }
    else if (val == HIGH && !DirectionD)
    {
      DirectionD = true;  //Forward
    }
  }
  encoderDPinALast = Lstate;

  if (!DirectionD)  durationD++;
  else  durationD--;
}

//#####  Velocidade encoder roda ESQUERDA
//Motor E
void wheelSpeedE()
{
  int Lstate = digitalRead(encoderEpinA);
  if ((encoderEPinALast == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(encoderEpinB);
    if (val == LOW && DirectionE)
    {
      DirectionE = false; //Reverse
    }
    else if (val == HIGH && !DirectionE)
    {
      DirectionE = true;  //Forward
    }
  }
  encoderEPinALast = Lstate;

  if (!DirectionE)  durationE++;
  else  durationE--;
}



//#################  FUNCOES DE MOVIMENTO  #################

//#####  PARAR
void stop(void)
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}




