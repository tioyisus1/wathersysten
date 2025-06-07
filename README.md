# Sistema de Control de Bombas con ESP32 y Sensor de Sonido

Este proyecto implementa un sistema de control de tres bombas de agua utilizando un ESP32, una pantalla OLED y un sensor de sonido KY-038. El sistema permite cambiar entre distintos modos de operación usando un botón físico, y visualizar el modo activo en la pantalla OLED.

## 🚀 Características

- Control de 3 bombas de agua mediante puente H.
- 7 modos de funcionamiento:
  1. **Detenido** (todas las bombas apagadas).
  2. **Secuencial** (una bomba a la vez).
  3. **Simultáneo** (todas encendidas a la vez).
  4. **Alternado** (una bomba distinta en cada ciclo).
  5. **Patrón personalizado**.
  6. **Combinado** (ejecuta varios modos uno tras otro).
  7. **Reactivo al sonido** (responde al ruido ambiente).
- Interfaz de usuario por pantalla OLED SSD1306.
- Cambio de modo con un solo botón físico.

## 🧰 Componentes necesarios

- ESP32
- Pantalla OLED 128x64 (I2C)
- Sensor de sonido KY-038 (salida analógica y digital)
- 3 Bombas de agua
- Puente H (control de las bombas)
- 1 Botón pulsador
- Resistencias, cables y fuente de alimentación adecuada

## ⚙️ Conexiones

### Pantalla OLED (I2C)
| Pin OLED | Pin ESP32 |
|----------|-----------|
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

### Sensor de Sonido KY-038
| Pin Sensor | Pin ESP32       |
|------------|-----------------|
| AO         | GPIO 34         |
| DO         | GPIO 35         |
| VCC        | 3.3V / 5V       |
| GND        | GND             |

### Bombas (controladas con puente H)
| Bomba | IN1 | IN2 | ENA / ENB |
|-------|-----|-----|-----------|
| 1     | 14  | 27  | 18        |
| 2     | 26  | 25  | 17        |
| 3     | 32  | 33  | 16        |

### Botón
- Pin de señal conectado a **GPIO 4**
- Configurado con **resistencia pull-up interna**

## 🖥️ Visualización

El estado actual del sistema se muestra en la pantalla OLED, indicando qué modo está en ejecución. Cuando está en "Detenido", muestra un mensaje solicitando presionar el botón para iniciar.

## 🧠 Lógica de funcionamiento

- Se utiliza un botón para cambiar de modo de forma cíclica.
- Cada modo tiene un patrón específico de encendido de bombas.
- El modo reactivo usa la variación en el valor analógico del KY-038 para activar bombas de forma dinámica.

## 🛠️ Librerías utilizadas

Asegúrate de instalar las siguientes librerías en el **Arduino IDE**:

- [`Adafruit_GFX`](https://github.com/adafruit/Adafruit-GFX-Library)
- [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)

## 📦 Instalación

1. Clona este repositorio:
   ```bash
   git clone https://github.com/tuusuario/control-bombas-sonido-oled.git
