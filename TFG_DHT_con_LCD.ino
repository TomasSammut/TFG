#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7 // Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11 // Definimos tipo de sensor

DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11
LiquidCrystal_I2C lcd(0x27, 16, 2); //Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas

const int rgb_rojo = 12;
const int rgb_verde = 11;
const int rgb_azul = 10;

const int led_rojo = 22;
const int led_verde = 24;

void setup() {
  dht.begin(); // Comenzamos el sensor DHT

  lcd.init(); // Inicializar el LCD
  lcd.backlight(); //Encender la luz de fondo

  pinMode(rgb_rojo, OUTPUT);
  pinMode(rgb_verde, OUTPUT);
  pinMode(rgb_azul, OUTPUT);

  pinMode(led_rojo, OUTPUT);
  pinMode(led_verde, OUTPUT);
}

void loop() {  
  // Leemos la humedad relativa
  float humedad = dht.readHumidity();
  delay(10);

  // Leemos la temperatura en grados centígrados (por defecto)
  float temperatura = dht.readTemperature();
  delay(10);

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(humedad) || isnan(temperatura)) {

    // Si error en lectura encender rojo, si lectura correcta encender verde
    digitalWrite(led_rojo, HIGH);
    digitalWrite(led_verde, LOW);

    lcd.clear(); // Borrar
    lcd.setCursor(0, 0);
    lcd.print("Error obteniendo");
    lcd.setCursor(0, 1);
    lcd.print("los datos");
    delay(5000);
    lcd.clear(); // Borrar
    return;
  }
  else {
    digitalWrite(led_rojo, LOW);
    digitalWrite(led_verde, HIGH);
  }

  // Mostramos datos por LCD
  lcd.clear(); // Borrar
  lcd.setCursor(0, 0);
  lcd.print("Temp.: " + String(temperatura) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Hum.: " + String(humedad) + " %");

  // Encendemos led en funcion de temperatura

  if (temperatura >= 25) { // Hace calor (ROJO)
    digitalWrite(rgb_rojo, HIGH);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }
  else if (temperatura <= 10) { // Hace frio (CIAN)
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, HIGH);
    digitalWrite(rgb_azul, HIGH);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }
  else { // Temperatura agradable (VERDE)
    digitalWrite(rgb_rojo, HIGH);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }

  // Encendemos led en funcion de humedad

  if (humedad >= 50) { // Hay mucha humedad (MORADO)
    digitalWrite(rgb_rojo, HIGH);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, HIGH);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }
  else if (humedad <= 30) { // Hay poca humedad (AZUL)
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, HIGH);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }
  else { // Humedad optima (VERDE)
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, HIGH);
    digitalWrite(rgb_azul, LOW);
    delay(2000);
    digitalWrite(rgb_rojo, LOW);
    digitalWrite(rgb_verde, LOW);
    digitalWrite(rgb_azul, LOW);
  }
}
