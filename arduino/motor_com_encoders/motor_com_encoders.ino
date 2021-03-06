//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/12V_DC_Motor_146rpm_w/Encoder(SKU:FIT0277)
//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/DFRduino_Romeo-All_in_one_Controller_V1.1(SKU:DFR0004)
//Utilizou-se o Codigo01_Encoders
/*
  Pay attention to the interrupt pin,please check which microcontroller you use.
  http://arduino.cc/en/Reference/AttachInterrupt
*/



//##################################  ENCODERS  ##################################

//#####  Motor Direito
const byte encoderDpinA = 2;//A pin -> the interrupt pin 2
const byte encoderDpinB = 8;//B pin -> the digital pin 8
byte encoderDPinALast;
int durationD;//the number of the pulses
boolean DirectionD;//the rotation direction

//#####  Motor Esquerdo
const byte encoderEpinA = 3;//A pin -> the interrupt pin 3
const byte encoderEpinB = 9;//B pin -> the digital pin 9
byte encoderEPinALast;
int durationE;//the number of the pulses
boolean DirectionE;//the rotation direction


//##################################  PWM CONTROL MODE  ##################################

//####  Standard PWM DC control
int E1 = 5;  //M1 Speed Control
int E2 = 6;  //M2 Speed Control
int M1 = 4;  //M1 Direction Control
int M2 = 7;  //M2 Direction Control

//####  Setar velocidade dos motores
char velocidadeE = 107;
char velocidadeD = 255;

//Vetor de caminhos
float cam[2] = {0, 0}; // {0, 0} parar {1,1} frente {-1,-1} tras
int pulsosD = 0;     //Armazenar a soma dos pulsos de cada roda
int pulsosE = 0;
int distpulsos = 500;

//#####  Sensores (portas analogicas), distancia  #####
int ifred[5][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}; // esquerda para a direita posicao dos sensores
int menorDist = 5000; //inicialmente com valor alto para entrar no while
int nl = 5; //numero de leituras dos ifred, DEVE SER N IMPAR



//##################################  SETUP()  ##################################

void setup() {

  //#####  Pinos dos motores  #####
  for (int i = 4; i <= 7; i++)
    pinMode(i, OUTPUT);

  Serial.begin(9600);//Initialize the serial port
  Serial.println("Run keyboard control");
  EncoderInit();//Initialize the module

  //#####  Definir as portas de entrada dos sensores  #####
  for (int i = 0; i < 5; i++) {
    pinMode(ifred[i][0], INPUT_PULLUP);
    Serial.print("Porta analogica ");
    Serial.print(ifred[i][0]);
    Serial.println(" definida como entrada.");
  }

  //#####  Chamar funcao de coleta das distancias iniciais #####
  dist_ifred();

  delay (1000);
}



//##################################  LOOP()  ##################################

void loop() {
  while (menorDist > 11) {
    //back_off (velocidadeD, velocidadeE);  //move back in max speed
    turn_L(velocidadeD, velocidadeE);
    //advance (velocidadeD, velocidadeE);  //move back in max speed
    //#####  Chamar funcao de coleta das distancias  #####
    menorDist = dist_ifred();
    //Serial.println(" Proxima leitura.... ");
    Serial.print("PulseD:");
    Serial.print(durationD*-1);
    Serial.print("   PulseE:");
    Serial.println(durationE);
    durationD = 0;
    durationE = 0;
  }
  stop();
  Serial.print("caiu aqui");
  menorDist = 5000;

  delay(4000);
}


//################################## FUNCOES ##################################

//#################  Distancia IFRED  #################
int dist_ifred () {
  int menor = 100;
  int leitura[nl]; //ira armazenar as leituras para o calculo da mediana

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < nl; j++) {
      leitura[j] = analogRead(ifred[i][0]);
      if (leitura[j] == 1023) {
        j = j - 1;
      } else {
        if (leitura[j] < 80) {
          leitura[j] = 80;
        } else if (leitura[j] > 450) {
          leitura[j] = 450;
        }
        leitura[j] = pow(3027.4 / leitura[j], 1.2134);
        delay(0.5);
      }
    }

    //##### chamar a funcao da mediana #####
    ifred[i][1] = mediana(leitura);
    if (ifred[i][1] < menor) {
      menor = ifred[i][1];
    }

    /*Serial.print("Valor lido para o sensor ");
    Serial.print(ifred[i][0]);
    Serial.print(" eh: ");
    Serial.print(ifred[i][1]);
    Serial.println(" cm.");*/
  }

  return menor;
}

//#################  Filtro Mediana  #################
int mediana (int vet[]) {

  int mn = 0; // armazenar o menor valor lido
  int pos = 0; // armazenar a posicao do menor valor
  int n = ceil(nl / 2); // armazenar a posicao e depois o valor da mediana

  for (int i = 0; i < nl; i++) {
    mn = vet[i];
    pos = i;
    for (int j = i; j < nl; j++) {
      if (vet[j] < mn) {
        pos = j;
        mn = vet[j];
      }
    }
    vet[pos] = vet[i];
    vet[i] = mn;
  }

  n = vet[n];
  return n;
}

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

//  STOP
void stop(void)
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}

//  Move forward
void advance(char a, char b)
{
  analogWrite (E1, a);     //PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//   Move backward
void back_off (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}

//   Turn Left
void turn_L (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//   Turn Right
void turn_R (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}

