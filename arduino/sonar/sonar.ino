
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define trigPin A6
#define echoPin A5

long duracao;
long distancia_cm = 50;
int minimumRange = 5; //tempo de resposta do sensor
int maximumRange = 200;

//Inicializa o sensor nos pinos definidos acima
//Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); //define o pino TRIG como saída
  pinMode(echoPin, INPUT);  //define o pino ECHO como entrada
  Serial.println("Lendo dados do sensor...");
}

void loop()
{
  int leituraDoSonar = lerSonar();  // Ler sensor de distância
  Serial.println(leituraDoSonar);
  delay(100);
}

// Função para ler e calcular a distância do sensor ultrassônico
int lerSonar() {
  digitalWrite(trigPin, LOW); //não envia som
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //envia som
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //não envia o som e espera o retorno do som enviado
  duracao = pulseIn(echoPin, HIGH); //Captura a duração em tempo do retorno do som.
  distancia_cm = duracao / 56; //Calcula a distância
  delay(30);
  return distancia_cm;             // Retorna a distância
}
