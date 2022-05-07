#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(11, 12, 2, 3, 4, 5);

const int AirValue = 590;   //you need to replace this value with Value_1.
const int WaterValue = 250;  //you need to replace this value with Value_2.
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT22

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  lcd.begin(16, 2);
  lcd.print("Moisture:");

  dht.begin();

  //Debug...
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  Serial.println("Reading from de Sensor...");
}


void loop() {
  soilMoistureValue = analogRead(A0);

  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humedad: ");
  if (soilmoisturepercent >= 100)
  {
    Serial.println("temp Soil" + String(soilmoisturepercent) + "%");
    lcd.print("100 %");
  }
  else if (soilmoisturepercent <= 0)
  {
    Serial.println("temp Soil" + String(soilmoisturepercent) + "%");
    lcd.print("0 %");
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    Serial.print("temp Soil" + soilmoisturepercent);
    Serial.println("%");
    lcd.print(String(soilmoisturepercent) + String("%"));
  }

  Serial.println("humidity Sensor " + String(hum) + "%");
  Serial.println("temp Sensor " + String(temp) + "ºC");
  lcd.setCursor(0, 1);
  lcd.print("T:" + String(temp, 1) + "C" + " H:" + String(hum, 1) + "%");
  delay(2000);  // wait 2 seconds until next reading.
}
