#include <VarSpeedServo.h>

VarSpeedServo meuServo;
const int servoPin = 3;

void setup() {
  meuServo.attach(servoPin); 

  Serial.begin(9600);
  Serial.println("Digite um ângulo entre 0 e 180 graus para mover o servo:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); 
    int angulo = input.toInt();

    delay(100); 
   
    if (angulo >= 0 && angulo <= 180) {
      int velocidade = 50; 

      meuServo.write(angulo, velocidade); 
      Serial.print("Servo movido para ");
      Serial.print(angulo);
      Serial.print(" graus, com velocidade de ");
      Serial.println(velocidade);
    } else {
      Serial.println("Por favor, insira um ângulo entre 0 e 180 graus.");
    }
  }
  delay(100); 
  meuServo.write(180);
  delay(100);
  meuServo.write(0); 
  delay(100);
  meuServo.write(90); 
  delay(100);
}
