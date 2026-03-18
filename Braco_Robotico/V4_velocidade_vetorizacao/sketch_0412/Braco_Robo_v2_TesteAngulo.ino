#include <VarSpeedServo.h>

VarSpeedServo meuServo;
const int servoPin = 3;

// Estrutura para encapsular os dados do motor
struct MotorData {
  int motorID;
  int motorAngle;
  int motorSpeed;
  bool isValid; // Indica se os valores são válidos
};

// Buffer para entrada serial
char receivedData[32]; // Buffer para armazenar toda a entrada recebida
int dataLength = 0;    // Comprimento dos dados recebidos

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial.println("Aguardando dados...");

  meuServo.attach(servoPin);

}

void loop() {
  // Verifica se há dados disponíveis antes de chamar a função
  if (Serial.available() > 0) {
    // Chama a função para processar a entrada e executar as ações
    MotorData motor = executarAcao();

    // Se os valores forem válidos, exibe os resultados
    if (motor.isValid) {
      Serial.print("Motor ID: ");
      Serial.println(motor.motorID);
      Serial.print("Motor Angle: ");
      Serial.println(motor.motorAngle);
      Serial.print("Motor Speed: ");
      Serial.println(motor.motorSpeed);
      Serial.println("");

      meuServo.write(motor.motorAngle);

    } else {
      Serial.println("Valores inválidos. Tente novamente.");
    }
  }
}

// Função que processa a entrada e retorna os dados do motor
MotorData executarAcao() {
  MotorData motor; // Estrutura para armazenar os valores
  motor.isValid = false; // Assume inválido por padrão

  // Lê todo o buffer serial para o vetor temporário
  dataLength = Serial.readBytesUntil('\n', receivedData, sizeof(receivedData) - 1);
  receivedData[dataLength] = '\0'; // Garante que a string termina com '\0'

  // Verifica se o comprimento dos dados recebidos é exatamente 5
  if (dataLength == 5) {
    // Converte os números recebidos
    motor.motorID = receivedData[0] - '0';                      // Primeiro número como inteiro
    motor.motorAngle = (receivedData[1] - '0') * 100 +          // Conversão para inteiro de 3 dígitos
                       (receivedData[2] - '0') * 10 +
                       (receivedData[3] - '0');
    motor.motorSpeed = receivedData[4] - '0';                   // Último número como inteiro

    // Validação dos números
    motor.isValid = true; // Assume válido até falhar em uma validação
    if (motor.motorID < 1 || motor.motorID > 3) {
      Serial.println("Erro: Motor ID deve ser 1, 2 ou 3.");
      motor.isValid = false;
    }
    if (motor.motorAngle < 0 || motor.motorAngle > 180) {
      Serial.println("Erro: Ângulo do motor deve estar entre 0 e 180.");
      motor.isValid = false;
    }
    if (motor.motorSpeed < 1 || motor.motorSpeed > 9) {
      Serial.println("Erro: Velocidade do motor deve estar entre 1 e 9.");
      motor.isValid = false;
    }
  } else {
    Serial.println("Erro: A entrada deve conter exatamente 5 números.");
  }

  limparBuffer(); // Limpa o buffer após processar ou verificar
  return motor;   // Retorna os dados processados
}

// Função para limpar o buffer e resetar os dados
void limparBuffer() {
  memset(receivedData, 0, sizeof(receivedData)); // Limpa o array
  while (Serial.available() > 0) {
    Serial.read(); // Esvazia o buffer serial
  }
}
