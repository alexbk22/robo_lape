
//#####  Sensores (portas analogicas), distancia  #####
int ifred[5][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}; // esquerda para a direita posicao dos sensores
int menorDist = 5000;
int nl = 5; //numero de leituras dos ifred, DEVE SER N IMPAR

//##################################  SETUP()  ##################################
void setup() {

  //#####  Comunicacao serial  #####
  Serial.begin(9600);//Initialize the serial port
  Serial.println("Run keyboard control");

  //#####  Definir as portas de entrada dos sensores  #####
  for (int i = 0; i < 5; i++) {
    pinMode(ifred[i][0], INPUT_PULLUP);
    Serial.print("Porta analogica ");
    Serial.print(ifred[i][0]);
    Serial.println(" definida como entrada.");
  }
}



//##################################  LOOP()  ##################################

void loop() {
  //#####  Chamar funcao de coleta das distancias  #####
  dist_ifred();
  Serial.println(" Proxima leitura.... ");
  delay(3000);

}



//################################## FUNCOES ##################################

//#################  Distancia IFRED  #################
void dist_ifred () {

  int leitura[nl]; //ira armazenar as leituras para o calculo da mediana

  for (int i = 0; i < 5; i++) {
    /*for (int j = 0; j < nl; j++) {
      leitura[j] = analogRead(ifred[i][0]);
      if (leitura[j] == 1023) {
        j = j - 1;
      } else {
        leitura[j] = (6762 / (leitura[j] - 9)) - 4;
      }
      }*/
    for (int j = 0; j < nl; j++) {
      leitura[j] = analogRead(ifred[i][0]);
      Serial.print("Leitura: ");
      Serial.println(leitura[j]);
      if (leitura[j] == 1023) {
        j = j - 1;
      } else {
        if (leitura[j] < 80) {
          leitura[j] = 80;
        } else if (leitura[j] > 450) {
          leitura[j] = 450;
        }
        leitura[j] = pow(3027.4 / leitura[j], 1.2134);
      }
    }

    //##### chamar a funcao da mediana #####
    ifred[i][1] = mediana(leitura);

    Serial.print("Valor lido para o sensor ");
    Serial.print(ifred[i][0]);
    Serial.print(" eh: ");
    Serial.print(ifred[i][1]);
    Serial.println(" cm.");
    delay(5);
  }
}


/*//########## TESTE IFRED CENTRAL

  void dist_ifred () {

  int leitura[nl]; //ira armazenar as leituras para o calculo da mediana

  for (int j = 0; j < nl; j++) {
    leitura[j] = analogRead(ifred[2][0]);
    Serial.print("Leitura: ");
    Serial.println(leitura[j]);
    if (leitura[j] == 1023) {
      j = j - 1;
    } else {
      if(leitura[j]<80){
        leitura[j]=80;
      }else if(leitura[j]>450){
        leitura[j]=450;
      }
      leitura[j]=pow(3027.4/leitura[j], 1.2134);
    }
  }

  //##### chamar a funcao da mediana #####
  ifred[2][1] = mediana(leitura);

  Serial.print("####### Valor lido para o sensor ");
  Serial.print(ifred[2][0]);
  Serial.print(" eh: ");
  Serial.print(ifred[2][1]);
  Serial.println(" cm.");
  //delay(5);

  }*/

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
