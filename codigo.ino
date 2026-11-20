// --- C++ ---
  
#include <Servo.h>

// --- PINOS ---
const int trigPin = 2;
const int echoPin = 4;
const int servoPin = 3;
const int buzzerPin = 8;
const int buttonPin = 7;
const int potPin = A0;

const int ledRed = 9;
const int ledGreen = 10;
const int ledBlue = 11;

Servo cancelaServo;

// --- TEMPOS ---
const unsigned long tempoEsperaFechamento = 3000;
const unsigned long debounceDelay = 50;

// Estado automático
unsigned long tempoUltimaDeteccao = 0;
unsigned long ultimaImpressao = 0;

// Estado 1: LED verde
unsigned long tempoUltimoPiscarEstado1 = 0;
bool estadoVerdePiscando = false;

// Estado 2: LED azul
unsigned long tempoUltimoPiscarAzulEstado2 = 0;
bool estadoAzulPiscandoEstado2 = false;

// Estado 2: LED vermelho
unsigned long tempoUltimoPiscarVermelhoEstado2 = 0;
bool estadoVermelhoPiscandoEstado2 = false;

// Espera do Estado 2
unsigned long tempoInicioEsperaBotao = 0;
bool contagemFechamentoBotaoAtiva = false;
bool cancelaEstavaAbertaAoEntrarEstado2 = false;

// Estado da cancela
bool jaDetectou = false;
bool cancelaAberta = false;

int estadoSistema = 0;

// --- BOTAO ---
int ultimaLeituraBotao = HIGH;
int estadoBotaoEstavel = HIGH;
unsigned long ultimoDebounce = 0;

// =================================
// CONFIGURACAO INICIAL
// =================================

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  cancelaServo.attach(servoPin);
  cancelaServo.write(0);

  // Inicia com a cancela fechada
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);

  noTone(buzzerPin);

  Serial.println("Sistema iniciado!");
}

// =================================
// PROGRAMA PRINCIPAL
// =================================

void loop() {
  // ---------------------------------
  // 1. LEITURA DO BOTAO
  // ---------------------------------
  int leituraAtual = digitalRead(buttonPin);

  // Identifica mudanças no botão
  if (leituraAtual != ultimaLeituraBotao) {
    ultimoDebounce = millis();
  }

  // Aguarda a estabilização do botão
  if (millis() - ultimoDebounce > debounceDelay) {
    if (leituraAtual != estadoBotaoEstavel) {
      estadoBotaoEstavel = leituraAtual;

      // Avança para o próximo estado
      if (estadoBotaoEstavel == LOW) {
        int estadoAntigo = estadoSistema;

        estadoSistema = (estadoSistema + 1) % 3;

        // Inicia a espera ao entrar no Estado 2
        if (estadoSistema == 2 && estadoAntigo != 2) {
          tempoInicioEsperaBotao = millis();
          contagemFechamentoBotaoAtiva = true;

          // Guarda a posição da cancela ao entrar no Estado 2
          cancelaEstavaAbertaAoEntrarEstado2 = cancelaAberta;
        }

        Serial.print("Estado do sistema: ");
        Serial.println(estadoSistema);
      }
    }
  }

  ultimaLeituraBotao = leituraAtual;

  // =================================
  // 2. ESTADO 1: MANUAL ABERTO
  // =================================
  if (estadoSistema == 1) {
    // Cancela permanece aberta
    cancelaServo.write(90);

    // Toca o buzzer somente ao abrir
    if (!cancelaAberta) {
      tone(buzzerPin, 1500, 700);
      cancelaAberta = true;
    }

    // Pisca o LED verde a cada 500ms
    if (millis() - tempoUltimoPiscarEstado1 >= 500) {
      tempoUltimoPiscarEstado1 = millis();
      estadoVerdePiscando = !estadoVerdePiscando;
    }

    digitalWrite(ledGreen, estadoVerdePiscando);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, LOW);

    // Cancela qualquer espera anterior
    contagemFechamentoBotaoAtiva = false;
  }

  // =================================
  // 3. ESTADO 2: MANUAL FECHADO
  // =================================
  else if (estadoSistema == 2) {
    // Verifica se os 3 segundos já passaram
    if (contagemFechamentoBotaoAtiva &&
        millis() - tempoInicioEsperaBotao < tempoEsperaFechamento) {
      // Mantém a posição em que a cancela estava
      if (cancelaEstavaAbertaAoEntrarEstado2) {
        cancelaServo.write(90);
      } else {
        cancelaServo.write(0);
      }

      // Pisca o LED azul durante a espera
      if (millis() - tempoUltimoPiscarAzulEstado2 >= 500) {
        tempoUltimoPiscarAzulEstado2 = millis();
        estadoAzulPiscandoEstado2 = !estadoAzulPiscandoEstado2;
      }

      digitalWrite(ledBlue, estadoAzulPiscandoEstado2);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
    }

    // Após os 3 segundos, fecha a cancela
    else {
      if (contagemFechamentoBotaoAtiva) {
        // Fecha e toca o buzzer se estava aberta
        if (cancelaAberta) {
          cancelaServo.write(0);
          tone(buzzerPin, 1500, 700);

          cancelaAberta = false;
        } else {
          cancelaServo.write(0);
        }

        contagemFechamentoBotaoAtiva = false;
      }

      // Pisca o LED vermelho após a espera
      if (millis() - tempoUltimoPiscarVermelhoEstado2 >= 500) {
        tempoUltimoPiscarVermelhoEstado2 = millis();
        estadoVermelhoPiscandoEstado2 = !estadoVermelhoPiscandoEstado2;
      }

      digitalWrite(ledRed, estadoVermelhoPiscandoEstado2);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
    }
  }

  // =================================
  // 4. ESTADO 0: AUTOMATICO
  // =================================
  else {
    // Cancela a espera do modo manual
    contagemFechamentoBotaoAtiva = false;

    // Lê o potenciômetro e define o limite
    int valorPot = analogRead(potPin);

    int distanciaLimite = map(valorPot, 0, 1023, 10, 50);

    // Envia o pulso para o sensor ultrassônico
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    // Mede o tempo de retorno do sinal
    long duracao = pulseIn(echoPin, HIGH, 30000UL);

    float distanciaCm = 0;

    if (duracao > 0) {
      distanciaCm = duracao * 0.034 / 2;
    }

    // Exibe as informações a cada 500ms
    if (millis() - ultimaImpressao >= 500) {
      Serial.print("Distancia: ");

      if (duracao > 0) {
        Serial.print(distanciaCm);
        Serial.println(" cm");
      } else {
        Serial.println("Sem leitura");
      }

      Serial.print("Limite configurado: ");
      Serial.print(distanciaLimite);
      Serial.println(" cm");

      ultimaImpressao = millis();
    }

    // Verifica se existe um objeto dentro do limite
    if (duracao > 0 && distanciaCm <= distanciaLimite) {
      // Atualiza o instante da última detecção
      tempoUltimaDeteccao = millis();
      jaDetectou = true;

      // Abre a cancela
      if (!cancelaAberta) {
        cancelaServo.write(90);
        tone(buzzerPin, 1500, 700);

        cancelaAberta = true;
      } else {
        cancelaServo.write(90);
      }

      // LED verde fixo durante a detecção
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledBlue, LOW);
    }

    // Objeto não está dentro do limite
    else {
      // Verifica se os 3 segundos já passaram
      if (jaDetectou &&
          millis() - tempoUltimaDeteccao >= tempoEsperaFechamento) {
        // Fecha a cancela
        if (cancelaAberta) {
          cancelaServo.write(0);
          tone(buzzerPin, 1500, 700);

          cancelaAberta = false;
        } else {
          cancelaServo.write(0);
        }

        // LED vermelho fixo após o fechamento
        digitalWrite(ledRed, HIGH);
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledBlue, LOW);
      }

      // Aguarda 3 segundos antes de fechar
      else if (jaDetectou) {
        cancelaServo.write(90);

        // LED azul fixo durante a espera
        digitalWrite(ledBlue, HIGH);
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, LOW);
      }

      // Aguarda a primeira detecção
      else {
        cancelaServo.write(0);

        digitalWrite(ledRed, HIGH);
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledBlue, LOW);
      }
    }
  }

  delay(50);
}
