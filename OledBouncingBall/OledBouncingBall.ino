#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Propiedades de la pelota
int ballX = 64;
int ballY = 32;
int ballRadius = 5;

// Velocidad y dirección de la pelota
int ballSpeedX = 3;
int ballSpeedY = 2;

void setup() {
  Serial.begin(115200);

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Detener ejecución si falla
  }
}

void loop() {
  // Limpiar el buffer de la pantalla
  display.clearDisplay();

  // Dibujar la pelota (un círculo relleno)
  display.fillCircle(ballX, ballY, ballRadius, SSD1306_WHITE);
  
  // Mostrar el contenido dibujado en la pantalla
  display.display();

  // Actualizar la posición de la pelota para el siguiente fotograma
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Rebotar en los bordes horizontales (izquierdo y derecho)
  if (ballX - ballRadius <= 0 || ballX + ballRadius >= SCREEN_WIDTH) {
    ballSpeedX = -ballSpeedX;
  }
  
  // Rebotar en los bordes verticales (superior e inferior)
  if (ballY - ballRadius <= 0 || ballY + ballRadius >= SCREEN_HEIGHT) {
    ballSpeedY = -ballSpeedY;
  }

  // Pequeña pausa para controlar la velocidad de la animación
  delay(30);
}
