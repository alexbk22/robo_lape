//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/12V_DC_Motor_146rpm_w/Encoder(SKU:FIT0277)
//Codigo adaptado de https://www.dfrobot.com/wiki/index.php/DFRduino_Romeo-All_in_one_Controller_V1.1(SKU:DFR0004)
//Utilizou-se o Codigo01_Encoders
/*
  Pay attention to the interrupt pin,please check which microcontroller you use.
  http://arduino.cc/en/Reference/AttachInterrupt
*/

//##################################  BIBLIOTECAS  ##################################
#include <Servo.h>        // inclui biblioteca de manipulação de servos motores.


//##################################  MENOR DISTANCIA OBSTACULOS  ##################################
#define dist_obst 40  //40 cm


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

//#####  Setar velocidade dos motores
int vel_max = 130;                        //velocidade maxima para ambos os motores
int vel_min = vel_max / 2;               //velocidade minima para o motor esquerdo
int velocidadeE = vel_max - vel_max / 4; //questao de rotacao dos motores, o direito esta girando mais lento
int velocidadeD = vel_max;


//#####  Numero de (passos do encoder) para giro
float ppr = 663;                  //pulsos por volta
float diam = 13.5 / 100.0;      //diametro das rodas em m
float er = 2.1 / 100.0;         //espessura das rodas em m
float base = 30.0 / 100.0 - er; //distancia entre os centros das rodas em m
float circum = PI * diam;       //circunferencia das rodas em m
float g_ppr = 360 / ppr;        //graus decimais por pulso
float circum_base = PI * base;

float ang_giro = 90;
//double ppr_g = (((circum_base * (ang_giro / 10.0)) / 18.0) / (circum / ppr)) / 2;
double ppr_g = 17;
//double ppr_g = ang_giro / 10 * ppr / 18.0; //(ang_giro*ppr/360.0)/2.0
int enc_D = 0;                  //para armazenar o numero de passos dos encoders e calcular os giros
int enc_E = 0;


//#####  Delay de freio
int delay_freio = 100;  //em milisegundos

//##################################  SENSORES INFRAVERMELHO  ##################################

//#####  Sensores (portas analogicas), distancia
int ifred[4][2] = {{0, 0}, {2, 0}, {4, 0}, {6, 0}}; //esquerda para a direita posicao dos sensores
int menorDist = 5000;                               //inicialmente com valor alto para entrar no while
int nl = 11;                                         //numero de leituras dos ifred, DEVE SER N IMPAR
bool caminho = true;                                   //true para a direita e false para a esquerda

//##################################  SENSORES de COLISAO (BUMPERS)  ##################################

//#####  Bumpers esquerda para a direita
int bump[3] = {13, 12, 11}; // {porta digital}


//##################################  STRING DE SAIDA (RESULTADOS A SEREM PROCESSADOS)  ##################################
String data;


//##################################  SERVO  ##################################
Servo servo;



//###############################################################################
//##################################  SETUP()  ##################################

void setup() {

  //#####  Pinos dos motores
  for (int i = 4; i <= 7; i++)
    pinMode(i, OUTPUT);

  //#####  Configurar a comunicao serial
  Serial.begin(115200);   // Initialize the serial port

  //#####  Inicializar os encoders
  EncoderInit();          // Initialize the module

  //#####  Definir as portas de entrada dos sensores ifred
  pinMode(A0, INPUT);  //Sensor esquerdo 5
  pinMode(A2, INPUT);  //Sensor central 3
  pinMode(A4, INPUT);  //Sensor direito 1
  pinMode(A6, INPUT);  //Sensor Servo


  //#####  Definir as portas de entrada dos bumpers
  for (int i = 0; i < 3; i++) {
    pinMode(bump[i], INPUT_PULLUP);
  }

  //#####  Chamar funcao de coleta das distancias iniciais
  ler_dist_ifred(true);

  //#####  Servo
  servo.attach(10);

  //#####  Delay de 3 segundos
  delay (3000);

  /*Serial.println(ppr_g);*/
}






//##############################################################################
//##################################  LOOP()  ##################################

void loop() {

  //##### Posicionar o servo com angulo 90 graus
  servo.write(90);

  //############################################################################
  //#####  IR PARA FRENTE  #####
  while (menorDist > dist_obst) {

    //#####  Chamar funcao de coleta das distancias  #####
    menorDist = ler_dist_ifred(true);  //1 eh para usar todos os ifred
    //Serial.println(menorDist);

    //#####  acionar os motores
    ir_frente(velocidadeD, velocidadeE);

    //#####  ajuste de velocidade frente
    ajust_vel_f(velocidadeE, durationD, durationE);

    //#####  Dados
    outData(durationE, durationD);

    //#####  identificar colisoes
    if (ler_bump(bump)) {
      stop();
      outData(durationE, durationD);
      delay(3000);
      break;
    }

    //#####  setando os encoders
    durationD = 0;
    durationE = 0;
  }

  //#####  parar rotacao dos motores
  stop();
  delay(delay_freio);
  ir_tras(velocidadeD, velocidadeE);
  delay(50);
  stop();

  //#####  Delay de 1 segundo
  for (int i = 0; i < 5; i++) {
    outData(durationE, durationD);
    delay(200);
    //#####  setando os encoders
    durationD = 0;
    durationE = 0;
  }
  
  stop();
  delay(delay_freio);
  ir_tras(velocidadeD, velocidadeE);
  delay(200);
  stop();

  //##### Escolher direcao a seguir
  caminho = esc_dir_servo();
  /*Serial.print("Caminho: ");
    Serial.println(caminho);*/


  //############################################################################
  //#####  GIRAR PARA A DIREITA  #####

  if (caminho) {
    //#####  zerar o contador dos encoders
    enc_D = 0;
    enc_E = 0;
    //#####  setando os encoders
    durationD = 0;
    durationE = 0;

    while (enc_D < ppr_g || enc_E < ppr_g) {
      if (enc_D < ppr_g && enc_E < ppr_g) {
        ir_dir(velocidadeD, velocidadeE);
      } else if (enc_D > ppr_g && enc_E < ppr_g) {
        ir_dir(0, velocidadeE);
      } else if (enc_D < ppr_g && enc_E > ppr_g) {
        ir_dir(velocidadeD, 0);
      } else {
        break;
      }

      enc_D += durationD;
      enc_E += durationE;

      //#####  Dados
      outData(durationE, durationD);
      /*Serial.print("direita ");
        Serial.print("enc_D: ");
        Serial.print(enc_D);
        Serial.print(" enc_E: ");
        Serial.println(enc_E);*/


      if (ler_bump(bump)) {
        //#####  parar rotacao dos motores
        stop();
        delay(30);
        ir_tras(velocidadeD, velocidadeE);
        delay(200);
        stop();
        break;
      }

      //#####  setando os encoders
      durationD = 0;
      durationE = 0;
    }

  }

  //############################################################################
  //#####  GIRAR PARA A ESQUERDA  #####
  else {
    //#####  zerar o contador dos encoders
    enc_D = 0;
    enc_E = 0;
    //#####  setando os encoders
    durationD = 0;
    durationE = 0;

    while (enc_D > -ppr_g || enc_E > -ppr_g) {
      if (enc_D > -ppr_g && enc_E > -ppr_g) {
        ir_esq(velocidadeD, velocidadeE);
      } else if (enc_D < -ppr_g && enc_E > -ppr_g) {
        ir_esq(0, velocidadeE);
      } else if (enc_D > -ppr_g && enc_E < -ppr_g) {
        ir_esq(velocidadeD, 0);
      } else {
        break;
      }

      enc_D += durationD;
      enc_E += durationE;

      //#####  Dados
      outData(durationE, durationD);
      /*Serial.print("esquerda ");
        Serial.print("enc_D: ");
        Serial.print(enc_D);
        Serial.print(" enc_E: ");
        Serial.println(enc_E);*/

      if (ler_bump(bump)) {
        //#####  parar rotacao dos motores
        stop();
        delay(3);
        ir_tras(velocidadeD, velocidadeE);
        delay(200);
        stop();
        break;
      }

      //#####  setando os encoders
      durationD = 0;
      durationE = 0;

    }

  }


  velocidadeE = vel_max - vel_max / 4;
  velocidadeD = vel_max;

  //#####  parar rotacao dos motores
  stop();
  delay(delay_freio);
  ir_tras(velocidadeD, velocidadeE);
  delay(10);
  stop();

  menorDist = 5000;

  delay(500);
}






//#############################################################################
//################################## FUNCOES ##################################

//################# dados de saida
void outData(int durationE, int durationD)
{

  Serial.println(String(durationE) + "," + String(-durationD) + "," + String(micros()));
}



//################# ajustar velocidade ir para frente
void ajust_vel_f(int& velocidadeE, int& durationD, int& durationE) {
  int dif = durationD + durationE;
  if (dif < -1)
    velocidadeE += -dif;// / 2;
  else if (dif > 1)
    velocidadeE += -dif;// / 2;

  if (velocidadeE > vel_max)
    velocidadeE = vel_max;
  else if (velocidadeE < vel_min)
    velocidadeE = vel_min;

  //String data = String(velocidadeE) + "," + String(durationE) + "," + String(-durationD);// + "," + String(micros());
  //Serial.println(data);
}


//#################  Ler Bumpers  #################
//####### IMPORTANTE: O VALOR LIDO SERA 1 QUANDO NAO PRESSIONADO (NAO BATER), E SERA 0 QUANDO BATER
bool ler_bump (int bump[3]) {
  bool a = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(bump[i]) == 0) {
      a = 1;
      break;
    }
  }
  return a;
}




//#################  Distancia IFRED  #################
int ler_dist_ifred (bool sens) {
  int menor = 100;
  int leitura[nl]; //ira armazenar as leituras para o calculo da mediana

  if (sens) {      //para ler todos os ifred
    for (int i = 0; i < 4; i++) {
      //Serial.println(analogRead(ifred[i][0]));
      for (int j = 0; j < nl; j++) {
        leitura[j] = analogRead(ifred[i][0]);
        if (leitura[j] == 1023) {
          j = j - 1;
        } else {
          if (leitura[j] < 80) {
            leitura[j] = 80;
          } else if (leitura[j] > 450) {
            leitura[j] = 80;
          }
          leitura[j] = pow(3027.4 / leitura[j], 1.2134);
        }
        delay(2);
      }

      //##### chamar a funcao da mediana #####
      ifred[i][1] = mediana(leitura);
      if (ifred[i][1] < menor) {
        menor = ifred[i][1];
      }
      /*Serial.print("Ifred: ");
        Serial.print(ifred[i][0]);
        Serial.print("  ");
        Serial.println(ifred[i][1]);*/
    }

    return menor;

  } else {     //ler somento o ifred do servo
    for (int j = 0; j < nl; j++) {
      leitura[j] = analogRead(ifred[3][0]);
      if (leitura[j] == 1023) {
        j = j - 1;
      } else {
        if (leitura[j] < 80) {
          leitura[j] = 80;
        } else if (leitura[j] > 450) {
          leitura[j] = 80;
        }
        leitura[j] = pow(3027.4 / leitura[j], 1.2134);
      }
      delay(2);
    }
    return mediana(leitura);
  }
  /*Serial.print(ifred[0][1]);
    Serial.print(" ");
    Serial.print(ifred[1][1]);
    Serial.print(" ");
    Serial.print(ifred[2][1]);
    Serial.print(" ");
    Serial.print(ifred[3][1]);
    Serial.print(" ");
    Serial.println(ifred[4][1]);*/
}



//#################  Filtro Mediana  #################
int mediana (int vet[]) {

  int mn = 0; // armazenar o menor valor lido
  int pos = 0; // armazenar a posicao do menor valor
  int n = ceil(nl / 2); // armazenar a posicao
  int m = ceil(nl / 4); // melhorar as leituras

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

  return vet[n + m];
}


//#################  Controlar o servo  #################
//#####  Escolher entre direita e esquerda para seguir
bool esc_dir_servo() {
  int ang = 30;
  int md = 5000; //menor distancia
  int dist = 0;
  for (int i = 20;  i <= 160; i += 20) {
    servo.write(i);
    delay(400);
    dist = ler_dist_ifred (0);
    if (dist < md) {
      md = dist;
      ang = i;
    }
  }

  if (ang < 90)
    return false;
  else if (ang > 90)
    servo.write(90);
  return true;

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

//#####  TRAS
void ir_tras (char a, char b)
{
  analogWrite (E1, a);     //PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//#####  FRENTE
void ir_frente (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}

//####  ESQUERDA
void ir_esq (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//#####  DIREITA
void ir_dir (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}
