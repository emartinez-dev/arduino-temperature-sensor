#include <LiquidCrystal.h>
#include "DHT.h"

/* Conexion pines
d1 -> d4      pantalla
d2 -> d5      pantalla
d5 -> d6      pantalla
d6 -> d7      pantalla
d7 -> rs      pantalla
d8 -> enable  pantalla
sd3 -> sensor (GPIO10)
*/

#define DHTPIN 10
#define DHTTYPE DHT11

// iconos creados
byte temperatura[9] = {
  B00110,
  B01010,
  B01010,
  B01010,
  B11111,
  B10001,
  B10001,
  B01110,
};

byte humedad[9] = {
  B00000,
  B00100,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
};

LiquidCrystal lcd(D7, D8, D1, D2, D5, D6);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Serial.begin(9600);
  lcd.createChar(0, temperatura);
  lcd.createChar(1, humedad);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t))
    return ;
 
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.print(t, 1);
  lcd.print("C ");
  
  lcd.setCursor(10, 0);
  lcd.write(byte(1));
  lcd.print(h, 1);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  float sensacion_termica = dht.computeHeatIndex(t, h, false);
  if (sensacion_termica > 25.0)
    lcd.print("   Hace calor   ");
  else if (sensacion_termica < 15.0)
    lcd.print("   Hace frio    ");
  else if (sensacion_termica < 20.0)
    lcd.print(" Hace fresquito ");
  else
    lcd.print("  Se esta bien  ");

  /* 
  // debug
  Serial.print("Temperatura: ");
  Serial.print(t); 
  Serial.print(" ºC ");
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println("%");
  */
}
