# Sistema de Control de Bombas con Pantalla OLED y Sensor de Sonido

Este proyecto permite controlar hasta 3 bombas de agua mediante un ESP32, usando distintos modos de funcionamiento, una pantalla OLED para visualizar el estado actual y un sensor de sonido KY-038 para activar las bombas de manera reactiva.

## Características

- Control de 3 bombas de agua mediante puente H.
- Cambio de modos de operación mediante un botón físico.
- Visualización en pantalla OLED SSD1306 (128x64).
- Modo reactivo al sonido usando sensor KY-038.
- 7 modos de operación diferentes.

## Requisitos

- ESP32
- 3 Bombas de agua (o LEDs para pruebas)
- Puente H (L298N o similar)
- Pantalla OLED SSD1306 (I2C)
- Sensor de sonido KY-038
- 1 botón pulsador
- Cables y protoboard

## Conexiones

| Componente         | Pin ESP32         |
|--------------------|-------------------|
| OLED SDA           | 21                |
| OLED SCL           | 22                |
| Botón              | 4                 |
| Sensor KY-038 AO   | 34 (analógico)    |
| Sensor KY-038 DO   | 35 (digital)      |
| Bomba 1 IN1        | 14                |
| Bomba 1 IN2        | 27                |
| Bomba 1 ENA        | 18                |
| Bomba 2 IN1        | 26                |
| Bomba 2 IN2        | 25                |
| Bomba 2 ENB        | 17                |
| Bomba 3 IN1        | 32                |
| Bomba 3 IN2        | 33                |
| Bomba 3 ENA        | 16                |

## Modos de Funcionamiento

1. **Modo 0 - Detenido**: Todas las bombas apagadas.
2. **Modo 1 - Secuencial**: Las bombas se encienden una por una con retrasos.
3. **Modo 2 - Simultáneo**: Todas las bombas funcionan al mismo tiempo.
4. **Modo 3 - Alternado**: Una bomba a la vez en orden cíclico.
5. **Modo 4 - Personalizado**: Patrón con distintos tiempos de encendido.
6. **Modo 5 - Combinado**: Se ejecutan todos los modos en secuencia.
7. **Modo 6 - Reactivo al sonido**: Las bombas se activan según el volumen detectado por el KY-038.

## Instalación

1. Asegúrate de tener el entorno de Arduino IDE con la placa ESP32 instalada.
2. Instala las siguientes bibliotecas:
   - `Adafruit_GFX`
   - `Adafruit_SSD1306`
3. Carga el código al ESP32.
4. Conecta los componentes como se describe arriba.
5. Abre el monitor serial para ver los valores del sensor de sonido.

## Uso

- Presiona el botón para cambiar entre modos.
- Observa el modo actual en la pantalla OLED.
- En el modo 6, los sonidos activan bombas según la intensidad.

## Créditos

Desarrollado por [David Suarez](https://github.com/tioyisus1)

---

**¡Contribuciones y mejoras son bienvenidas!**
