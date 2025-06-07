#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir dimensiones de la pantalla OLED
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED

// Crear objeto display OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Definir los pines para las bombas controladas con el puente H, el botón y el sensor de sonido
#define PUMP1_IN1 14
#define PUMP1_IN2 27
#define PUMP1_ENA 18 // Para control de velocidad (opcional)

#define PUMP2_IN1 26
#define PUMP2_IN2 25
#define PUMP2_ENB 17 // Para control de velocidad (opcional)

#define PUMP3_IN1 32
#define PUMP3_IN2 33
#define PUMP3_ENA 16 // Para control de velocidad (opcional)

#define BUTTON_PIN 4
#define SOUND_SENSOR_AO_PIN 34 // Pin analógico conectado al AO del KY-038
#define SOUND_SENSOR_DO_PIN 35 // Pin digital conectado al DO del KY-038
#define OLED_SDA 21 // Cambia si estás usando otros pines
#define OLED_SCL 22 // Cambia si estás usando otros pines

// Variables para almacenar valores analógicos y digitales
int digitalVal;
int analogVal;
int prevAnalogVal = 0; // Valor anterior para comparación

// Variables para controlar los modos
int currentMode = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
#define NUM_MODES 7 // Ahora hay 6 modos

void setup() {
  Serial.begin(9600);
  Wire.begin(OLED_SDA, OLED_SCL); // Inicializar el bus I2C con los pines personalizados
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar la pantalla SSD1306"));
    for (;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);             // Tamaño del texto
  display.setTextColor(SSD1306_WHITE);// Color del texto
  display.display();

  // Configurar los pines de las bombas como salidas
  pinMode(PUMP1_IN1, OUTPUT);
  pinMode(PUMP1_IN2, OUTPUT);
  pinMode(PUMP1_ENA, OUTPUT);
  
  pinMode(PUMP2_IN1, OUTPUT);
  pinMode(PUMP2_IN2, OUTPUT);
  pinMode(PUMP2_ENB, OUTPUT);
  
  pinMode(PUMP3_IN1, OUTPUT);
  pinMode(PUMP3_IN2, OUTPUT);
  pinMode(PUMP3_ENA, OUTPUT);

  // Configurar el pin del botón como entrada con resistencia pull-up interna
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configurar los pines del sensor de sonido
  pinMode(SOUND_SENSOR_AO_PIN, INPUT); // Entrada analógica
  pinMode(SOUND_SENSOR_DO_PIN, INPUT); // Entrada digital

  // Apagar todas las bombas al inicio
  turnOffAllPumps();
  updateDisplay();
}

void loop() {

    // Leer la salida digital y analógica del sensor KY-038
  digitalVal = digitalRead(SOUND_SENSOR_DO_PIN);
  analogVal = analogRead(SOUND_SENSOR_AO_PIN);

  // Mostrar valor analógico en el monitor serial
  Serial.println(analogVal);

  // Leer el estado del botón
  int buttonState = digitalRead(BUTTON_PIN);

  // Actualizar la condición para cambiar los modos
  if (buttonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    currentMode = (currentMode + 1) % NUM_MODES; // Cambiar entre 6 modos
    updateDisplay(); // Actualizar pantalla OLED
    delay(200);
  }

  // Ejecutar la configuración de las bombas según el modo actual
  switch (currentMode) {
    case 0:
      turnOffAllPumps();
      break;
    case 1:
      modeSequential();
      break;
    case 2:
      modeAllSimultaneous();
      break;
    case 3:
      modeAlternate();
      break;
    case 4:
      modeCustomPattern();
      break;
    case 5:
      modeCombined();
      break;
    case 6:
      modeSoundReactive();
      break;
  }
}

// Función para apagar todas las bombas
void turnOffAllPumps() {
  digitalWrite(PUMP1_IN1, LOW);
  digitalWrite(PUMP1_IN2, LOW);
  digitalWrite(PUMP2_IN1, LOW);
  digitalWrite(PUMP2_IN2, LOW);
  digitalWrite(PUMP3_IN1, LOW);
  digitalWrite(PUMP3_IN2, LOW);
}

// Modo 0: Bombas funcionan en secuencia
void modeSequential() {
  turnOffAllPumps();
  digitalWrite(PUMP1_IN1, HIGH);
  delay(1000);
  turnOffAllPumps();
  
  digitalWrite(PUMP2_IN1, HIGH);
  delay(1000);
  turnOffAllPumps();
  
  digitalWrite(PUMP3_IN1, HIGH);
  delay(1000);
  turnOffAllPumps();
}

// Modo 1: Todas las bombas funcionan simultáneamente
void modeAllSimultaneous() {
  digitalWrite(PUMP1_IN1, HIGH);
  digitalWrite(PUMP2_IN1, HIGH);
  digitalWrite(PUMP3_IN1, HIGH);
  delay(2000);
  turnOffAllPumps();
}

// Modo 2: Alternar una bomba a la vez
void modeAlternate() {
  turnOffAllPumps();
  static int pumpIndex = 0;

  switch (pumpIndex) {
    case 0:
      digitalWrite(PUMP1_IN1, HIGH);
      break;
    case 1:
      digitalWrite(PUMP2_IN1, HIGH);
      break;
    case 2:
      digitalWrite(PUMP3_IN1, HIGH);
      break;
  }

  pumpIndex = (pumpIndex + 1) % 3;
  delay(1000);
  turnOffAllPumps();
}

// Modo 3: Patrón personalizado de las bombas
void modeCustomPattern() {
  digitalWrite(PUMP1_IN1, HIGH);
  delay(500);
  digitalWrite(PUMP2_IN1, HIGH);
  delay(1000);
  digitalWrite(PUMP3_IN1, HIGH);
  delay(1500);
  turnOffAllPumps();
  delay(500);
}

// Modo 4: Ejecuta todos los modos uno tras otro con 1 segundo de diferencia
void modeCombined() {
  modeSequential();        // Ejecutar Modo Secuencial
  delay(1000);             // Esperar 1 segundo

  modeAllSimultaneous();   // Ejecutar Modo Simultáneo
  delay(1000);             // Esperar 1 segundo

  modeAlternate();         // Ejecutar Modo Alternado
  delay(1000);             // Esperar 1 segundo

  modeCustomPattern();     // Ejecutar Modo Personalizado
  delay(1000);             // Esperar 1 segundo
}

// Modo 5: Activar bombas aleatoriamente según el sonido
void modeSoundReactive() {
  // Leer la salida digital y analógica del sensor KY-038
  digitalVal = digitalRead(SOUND_SENSOR_DO_PIN);
  analogVal = analogRead(SOUND_SENSOR_AO_PIN);

  // Mostrar valor analógico en el monitor serial
  Serial.println(analogVal);

  

  // Comparar el valor actual del sensor analógico con el anterior
  if (analogVal > prevAnalogVal + 10) {
    // Si el cambio es mayor a 10, encender la bomba correspondiente
    if (analogVal > 300) {
      digitalWrite(PUMP1_IN1, HIGH); // Bomba 1 para un cambio moderado
      digitalWrite(PUMP2_IN2, HIGH); // Bomba 2 para un cambio moderado
      digitalWrite(PUMP3_IN2, HIGH); // Bomba 3 para un cambio grande
    } else if (analogVal > 270) {
      digitalWrite(PUMP1_IN1, HIGH); // Bomba 1 para un cambio moderado
      digitalWrite(PUMP2_IN2, HIGH); // Bomba 2 para un cambio moderado
    } else if (analogVal > 230) {
      digitalWrite(PUMP1_IN1, HIGH); // Bomba 1 para un cambio pequeño
    }
    delay(200); // Mantener encendida la bomba
    turnOffAllPumps(); // Apagar todas las bombas
  }

  // Actualizar el valor anterior
  prevAnalogVal = analogVal;

  // Pequeña demora para estabilidad
  delay(100);
}


// Función para actualizar la pantalla OLED con el modo actual
void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0); // Poner el cursor en la primera línea

  switch (currentMode) {
    case 0:
      display.print("Modo: Detenido");
      display.print("Presione para iniciar");
      break;
    case 1:
      display.print("Modo: Secuencial");
      break;
    case 2:
      display.print("Modo: Simultaneo");
      break;
    case 3:
      display.print("Modo: Alternado");
      break;
    case 4:
      display.print("Modo: Personalizado");
      break;
    case 5:
      display.print("Modo: Combinado");
      break;
    case 6:
      display.print("Modo: Reactivo Sonido");
      break;
  }
  display.display(); // Actualizar el contenido de la pantalla
}