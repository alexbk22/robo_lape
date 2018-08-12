//#####  Sensor central
int dist = 0;  //distancia
#define nl 11
int ifred[nl]; //leitura

void setup() {
  //#####  Comunicacao serial
  Serial.begin(115200);

  //#####  Definir a porta de leitura
  pinMode(A2, INPUT);

  delay(2000);
}



void loop() {

  for (int j = 0; j < nl; j++) {
    ifred[j] = analogRead(A2);
    if (ifred[j] == 1023) {
        j = j - 1;
      } else {
        if (ifred[j] < 80) {
          ifred[j] = 80;
        } else if (ifred[j] > 450) {
          ifred[j] = 450;
        }
        ifred[j] = pow(3027.4 / ifred[j], 1.2134);
      }

    delay(3);
  }
  dist = mediana(ifred);
  Serial.println(dist);
  delay(10);
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
