// Global Solution 2026/2 - Cuidar de Perto
// Demonstracao local em Arduino Uno R3 no Tinkercad.
// A Serial exibe eventos; nao envia dados de rede para a API.

const int PIR = 2;
const int BOTAO_SOS = 3;
const int BOTAO_RECONHECER = 4;
const int LED_VERDE = 5;
const int LED_VERMELHO = 6;
const int BUZZER = 9;

const unsigned long TEMPO_INATIVIDADE = 20000;
const unsigned long TEMPO_SOS = 2000;

unsigned long ultimoMovimento = 0;
unsigned long inicioSOS = 0;

bool alerta = false;
bool alertaSOS = false;
bool sosDisparado = false;
bool botaoAnterior = false;
bool movimentoAnterior = false;

void ativarAlerta(const char* tipo, bool sos) {
  alerta = true;
  alertaSOS = sos;

  Serial.print("ALERTA: ");
  Serial.println(tipo);
}

void setup() {
  pinMode(PIR, INPUT);
  pinMode(BOTAO_SOS, INPUT_PULLUP);
  pinMode(BOTAO_RECONHECER, INPUT_PULLUP);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  ultimoMovimento = millis();

  Serial.println("CUIDAR DE PERTO INICIADO");
}

void loop() {
  unsigned long agora = millis();

  bool movimento = digitalRead(PIR) == HIGH;
  bool sos = digitalRead(BOTAO_SOS) == LOW;
  bool reconhecer = digitalRead(BOTAO_RECONHECER) == LOW;

  if (movimento) {
    ultimoMovimento = agora;

    if (!movimentoAnterior) {
      Serial.println("Movimento detectado");
    }

    if (alerta && !alertaSOS) {
      alerta = false;
      Serial.println("Inatividade encerrada");
    }
  }

  movimentoAnterior = movimento;

  if (sos) {
    if (inicioSOS == 0) {
      inicioSOS = agora;
    }

    if (!sosDisparado &&
        agora - inicioSOS >= TEMPO_SOS) {
      ativarAlerta("PEDIDO DE SOCORRO", true);
      sosDisparado = true;
    }
  } else {
    inicioSOS = 0;
    sosDisparado = false;
  }

  if (reconhecer && !botaoAnterior) {
    if (alerta) {
      alerta = false;
      alertaSOS = false;
      ultimoMovimento = agora;
      Serial.println("Alerta reconhecido");
    }
  }

  botaoAnterior = reconhecer;

  if (!alerta &&
      agora - ultimoMovimento >= TEMPO_INATIVIDADE) {
    ativarAlerta("INATIVIDADE", false);
  }

  digitalWrite(LED_VERDE, alerta ? LOW : HIGH);
  digitalWrite(LED_VERMELHO, alerta ? HIGH : LOW);

  if (alerta) {
    tone(BUZZER, 1000);
  } else {
    noTone(BUZZER);
  }
}
