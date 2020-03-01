// Basé sur le code de LadyAda traduit et modifie par moi, domaine public
#include "DHT.h"
#define DHTPIN 8 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
#include <Wire.h> // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library >
LiquidCrystal_I2C lcd(0x3F, 26, 2);

 String ConvertionFloatToString(float Val)
{  
 char bufFloat[5];
 String str;
 dtostrf(Val,5,2, bufFloat);
 str = String(bufFloat);
 return str;
}

void setup()
{
 Serial.begin(9600);
 Serial.println("DHTxx test!");
 dht.begin();
 lcd.init(); // initializing the LCD
 lcd.backlight(); // Enable or Turn On the backlight
}
void loop()
{
 delay(2000);
 
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
 

//Affichages : 
// Ligne 1: 
lcd.setCursor(0, 0);  // positionne le curseur à la colonne 1 et à la ligne 1 
lcd.print("Humidite: "); 
lcd.setCursor(10, 0); 
lcd.print(h); 
lcd.setCursor(15, 0); 
lcd.print("%"); 

// Ligne 2: 
lcd.setCursor(0, 1);  // positionne le curseur à la colonne 1 et à la ligne 2 
lcd.print("Temp: "); 
lcd.setCursor(10, 1); 
lcd.print(t);
}
