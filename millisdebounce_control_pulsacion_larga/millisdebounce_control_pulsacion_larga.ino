// Definición de pines para pulsadores
#define      CONT   2
#define      RESET  3
#define      BAUDRATE 9600
#define      LED    13

// Variables para el manejo de pulsadores
volatile unsigned long lasttime = 0;
volatile unsigned long debounceDelay = 10; // Tiempo de antirrebote
volatile bool resetRequested = false; // Bandera para indicar si se solicita reinicio

// Contador
volatile int contador = 0;

void setup() {
  // Configurar pines de entrada para pulsadores
  pinMode(CONT, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  // Configurar interrupciones para pulsadores
  attachInterrupt(digitalPinToInterrupt(CONT), Contador, RISING);
  attachInterrupt(digitalPinToInterrupt(RESET), reset, RISING);

  // Iniciar comunicación serial 
  Serial.begin(BAUDRATE);
}

void loop() {
  // Verificar si se solicita reinicio


  // Verificar si el pulsador 1 fue presionado
  digitalWrite(LED, 1);
  delay(200);
  digitalWrite(LED, 0);
  delay(200);
}

// Función de interrupción para el pulsador CONT
void Contador() {
  unsigned long currentTime = millis();
  
  if (currentTime - lasttime > debounceDelay) {
    if (digitalRead(CONT) == HIGH) { // Si el botón se soltó
      contador++;
      Serial.println(contador);
    } else { // Si el botón está presionado
      if (currentTime - lasttime >= 3000) { // Si se mantiene presionado más de 2 segundos
        contador=0;
        Serial.println("RESETEADO");
      }
    }
    lasttime = currentTime;
  }
}

// Función de interrupción para el pulsador RESET
void reset() {
  if (millis() - lasttime > debounceDelay) {
    contador -=1;
    lasttime = millis();
    Serial.println(contador);
  }
}
