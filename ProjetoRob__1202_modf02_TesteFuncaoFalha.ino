#include <VarSpeedServo.h>

const int numServos = 3; 
VarSpeedServo servos[numServos]; 
const int servoPins[numServos] = {3, 5, 6}; 

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
  }

  Serial.println("Digite: [Motor (1-3)] [Ângulo (0-180)] [Velocidade (1-9)]");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    input.trim();

    int motorID = input.substring(0, input.indexOf(' ')).toInt();
    input = input.substring(input.indexOf(' ') + 1);
    int angulo = input.substring(0, input.indexOf(' ')).toInt();
    int velocidade = input.substring(input.indexOf(' ') + 1).toInt();
    int resultado = moverServo(motorID, angulo, velocidade);
    Serial.print("Código de retorno: ");
    Serial.println(resultado);
  }
}

int moverServo(int motorID, int angulo, int velocidade) {

  int velocidadeMapeada = map(velocidade, 1, 9, 10, 100);
  servos[motorID - 1].write(angulo, velocidadeMapeada);

  Serial.print("Servo ");
  Serial.print(motorID);
  Serial.print(" movido para ");
  Serial.print(angulo);
  Serial.print(" graus com velocidade ");
  Serial.println(velocidadeMapeada);

  return motorID * 100 + angulo;
}
