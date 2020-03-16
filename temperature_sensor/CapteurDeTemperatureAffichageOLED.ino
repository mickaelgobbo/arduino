/*
  Programme de démo pour écran OLED 128x64 pixels I2C basé sur le contrôleur SSD1306
  Ajout de traduction en français
  Projets DIY - mars 2016 - https://www.projetsdiy.fr
  
*/
/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "DHT.h"
#define DHTPIN 8 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
#include <Wire.h> // This library is already built in to the Arduino IDE

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
// Logo Adafruit
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

 String ConvertionFloatToString(float Val)
{  
 char bufFloat[5];
 String str;
 dtostrf(Val,5,2, bufFloat);
 str = String(bufFloat);
 return str;
}


void setup()   {                
  Serial.begin(9600);

  Serial.println("DHTxx test!");
  dht.begin();
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  //Utiliser le scanner I2C pour trouver le port série sur lequel se trouve votre écran 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64) 
  // init done
  
  display.display();        // show splashscreen  // Affiche le logo Adafruit par défaut
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer   // Efface l'écran 

}

void loop() {

   // La lecture du capteur prend 250ms
 // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 // pour lire en farenheit, il faut le paramère (isFahrenheit = true) :
 float f = dht.readTemperature(true);
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 
 // Calcul de l'indice de temperature en Farenheit
 float hif = dht.computeHeatIndex(f, h);
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, false);

   display.clearDisplay();   // clears the screen and buffer   // Efface l'écran 
   
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Humidite: ");
  
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(60,0);
  display.println(h);
  display.setCursor(90,0);
  display.println("%");
  display.setCursor(0,10);
  display.println("Temp: "); 
  display.setCursor(30,10);
  display.println(t); 
  display.display();  
  delay(2000);
}
