#include <VarSpeedServo.h>

const int numServos = 3; // Número de servos
VarSpeedServo servos[numServos]; // Vetor de objetos servo
const int servoPins[numServos] = {3, 5, 6}; // Pinos dos servos

void setup() {
  Serial.begin(9600);
  
  // Inicializa os servos e associa os pinos
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
  }

  Serial.println("Digite no formato: [Número do motor (1-3)] [Ângulo (0-180)] [Velocidade (1-9)]");
  Serial.println("Exemplo: 1 90 5 (Mover motor 1 para 90 graus com velocidade 5)");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Lê a entrada
    input.trim(); // Remove espaços extras

    // Divide a entrada em partes
    int motorID = input.substring(0, input.indexOf(' ')).toInt(); // Primeiro número
    input = input.substring(input.indexOf(' ') + 1);
    int angulo = input.substring(0, input.indexOf(' ')).toInt(); // Segundo número
    int velocidade = input.substring(input.indexOf(' ') + 1).toInt(); // Terceiro número

    // Valida a entrada e move o servo
    if (motorID >= 1 && motorID <= numServos &&
        angulo >= 0 && angulo <= 180 &&
        velocidade >= 1 && velocidade <= 9) {
      
      moverServo(motorID - 1, angulo, map(velocidade, 1, 9, 10, 100)); // Chama a função para mover o servo
    } else {
      Serial.println("Entrada inválida! Certifique-se de usar o formato correto e valores válidos.");
    }
  }
}

// Função para mover o servo
void moverServo(int servoIndex, int angulo, int velocidade) {
  Serial.print("Movendo o Servo ");
  Serial.print(servoIndex + 1);
  Serial.print(" para ");
  Serial.print(angulo);
  Serial.print(" graus com velocidade ");
  Serial.print(velocidade);
  Serial.println("...");

  servos[servoIndex].write(angulo, velocidade);
  delay(100); // Pequeno atraso para evitar sobrecarga de comandos
}

