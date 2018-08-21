//#####  Sensor central
int dist = 0;  //distancia
#define nl 11
int ifred[nl]; //leitura
int bruta[nl];

void setup() {
  //#####  Comunicacao serial
  Serial.begin(115200);

  //#####  Definir a porta de leitura
  pinMode(A2, INPUT);

  delay(2000);
}



void loop() {

  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < nl; j++) {
      bruta[j] = analogRead(A2);

      if (bruta[j] == 1023) {
        j = j - 1;
      } else {
        if (bruta[j] < 80) {
          ifred[j] = 80;
        } else if (bruta[j] > 450) {
          ifred[j] = 450;
        } else {
          ifred[j] = bruta[j];
        }

        ifred[j] = pow(3027.4 / ifred[j], 1.2134);
        bruta[j] = pow(3027.4 / bruta[j], 1.2134);
      }

      delay(3);
    }

    dist = mediana(ifred);
    for (int j = 0; j < nl; j++) {
      //Serial.print(i * nl + j);
      //Serial.print(",");
      Serial.print(bruta[j]);
      Serial.print(",");
      Serial.println(dist);
    }
    delay(200);
  }
  delay(5000);
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
