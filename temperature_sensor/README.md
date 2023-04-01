Prerequiste for arduino project:

- Installation of the arduino IDE: https://www.arduino.cc/en/guide/windows for windows
- Tool which can be useful to design electric diagram: https://easyeda.com/

temperatureSensorWithLCD.ino:

Liste a material used:
- Aihasd 1602 écran LCD bleu iIC/i2C (https://www.amazon.fr/gp/product/B00Y5AFWU4/ref=ppx_yo_dt_b_asin_image_o08_s00?ie=UTF8&psc=1)
- DHT22 temperature sensor
- Arduino uno

CapteurDeTemperatureAffichageOLED:
- ecran OLED SSD1306 64*128
- Adafruit_SSD1306-master library


additional libraries:
You will need some aditionnal libraries to have the compilation of this program successful.

For example, with the bellow errors you will need to download the corresponding library:
Error: Adafruit_Sensor.h No such file or directory
Library: https://github.com/adafruit/Adafruit_Sensor

Error: DHT.h: No such file or directory
Library: https://github.com/adafruit/DHT-sensor-library

To add a library in your IDE, you have to click on Sketch, Include Library and add .Zip library.
