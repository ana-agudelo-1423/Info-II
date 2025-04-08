/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int denominaciones[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
int cantidad[10] = {0};
const int botonPin = 8; // Pin del botón
int monto = 0;
unsigned long ultimoPulsado = 0;
bool yaMostro = false;
void setup() {
  // set up the LCD's number of columns and rows:
 pinMode(botonPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Monto: ");
  lcd.setCursor(0, 1);
  lcd.print(monto);
}

void loop() {
  int estadoBoton = digitalRead(botonPin);

  if (estadoBoton == HIGH) {
    monto += 1000; // Suma de a 1000
    lcd.clear();
    lcd.print("Monto: ");
    lcd.setCursor(0, 1);
    lcd.print(monto);
    ultimoPulsado = millis();
    yaMostro = false;
    delay(300); // Antirrebote y espera
  }

  // Si pasaron más de 5 segundos sin pulsar, muestra el desglose
  if ((millis() - ultimoPulsado > 5000) && monto > 0 && !yaMostro) {
    mostrarDesglose(monto);
    yaMostro = true;
    monto = 0; // Reinicia para nuevo monto
    delay(5000); // Espera antes de limpiar
    lcd.clear();
    lcd.print("Monto: ");
    lcd.setCursor(0, 1);
    lcd.print(monto);
  }
}
void mostrarDesglose(int valor) {
  int resto = valor;

  for (int i = 0; i < 10; i++) {
    cantidad[i] = resto / denominaciones[i];
    resto = resto % denominaciones[i];
  }

  for (int i = 0; i < 10; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Den: ");
    lcd.print(denominaciones[i]);
    lcd.setCursor(0, 1);
    lcd.print("Cant: ");
    lcd.print(cantidad[i]);
    delay(2000);
  }

  if (resto > 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Faltante:");
    lcd.setCursor(0, 1);
    lcd.print(resto);
    delay(3000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Todo exacto :)");
    delay(3000);
  }
}