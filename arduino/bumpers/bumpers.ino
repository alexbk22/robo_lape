
//#####  Bumpers esquerda para a direita  #####
int bump[3][2] = {{13,0},  {12,0}, {11,0}};

//##################################  SETUP()  ##################################

void setup() {

  //#####  Comunicacao serial  #####
  Serial.begin(9600);//Initialize the serial port

  //#####  Definir as portas de entrada dos bumpers  #####
  for (int i = 0; i < 3; i++) {
    pinMode(bump[i][0], INPUT_PULLUP);
    Serial.print("Porta analogica ");
    Serial.print(bump[i][0]);
    Serial.println(" definida como entrada.");
  }
  delay(1000);

}

//##################################  LOOP()  ##################################

void loop() {
  for (int i = 0; i < 3; i++) {
    bump[i][1]=digitalRead(bump[i][0]);
    Serial.print("Leitura bumper ");
    Serial.print(bump[i][0]);
    Serial.print(" : ");
    Serial.println(bump[i][1]);
  }
  delay (1000);
}
