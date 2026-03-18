#include <VarSpeedServo.h>

VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
const int servoPin1 = 3;
const int servoPin2 = 5;
const int servoPin3 = 6;

int vetorAngulo[5] = {0,5,45,90,180};

void setup() {
  
  Serial.begin(9600);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

    int tamVetor;
    Serial.print("Tamanho do vetor: ");
    tamVetor = sizeof(vetorAngulo)/sizeof(vetorAngulo[0]);
    Serial.println(tamVetor);   

    for (int cont=0; cont <= tamVetor-1 ; cont ++) {
      Serial.print("Posição do Vetor ");
      Serial.print(cont);
      Serial.print(" : ");
      Serial.println(vetorAngulo[cont]);
    }
}



void loop() {

  if (Serial.available () > 0) {
    
    String input = Serial.readStringUntil('\n');
    input.trim(); 
    
    int angulo[] = input.toInt();

    Serial.print(angulo[0]);

    if (angulo >= 0 && angulo <= 180) {
      int velocidade = 60; 
            
      Serial.println("Movendo o Servo 1...");
      servo1.write(angulo, velocidade);
      delay(100); 
     
      Serial.println("Movendo o Servo 2...");
      servo2.write(angulo, velocidade);
      delay(100); 

      Serial.println("Movendo o Servo 3...");
      servo3.write(angulo, velocidade);
      delay(100);

      Serial.print("Todos os servos foram movidos para ");
      Serial.print(angulo);
      Serial.println(" graus.");
    } 
    else {
 
      Serial.println("Por favor, insira um ângulo entre 0 e 180 graus!");
    }
  }
}
