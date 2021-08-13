#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <SD.h>

#define BMP_SCK (10)
#define BMP_MISO (9)
#define BMP_MOSI (8)
#define BMP_CS (7)
#define CS_PIN SDCARD_SS_PIN
#define SEA_PRESSURE 1013.25

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
File myFile;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600); // begin talking to the computer

    if (!bmp.begin()) {
        Serial.println("Could not find valid BMP280");
        while (1) {} // stop here if sensor doesn't work
    }


    bmp.setSampling(
        Adafruit_BMP280 :: MODE_NORMAL, 
        Adafruit_BMP280 :: SAMPLING_X2, 
        Adafruit_BMP280 :: SAMPLING_X16,
        Adafruit_BMP280 :: FILTER_X16,
        Adafruit_BMP280 :: STANDBY_MS_500);

    SD.begin(CS_PIN);
    myFile = SD.open("gbg4.txt", FILE_WRITE);

    if (myFile) {
        Serial.println("Succeded to open file!");
    } else {
        Serial.println("Failed to open file!");
        while (1) {} // stop and wait
    }

    // header
    Serial.println("Time, Pressure, Temperature, Altitude");
    myFile.println("Time, Preassure, Temperature, Altitude");

    myFile.flush();

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop () {
    myFile.print(millis());
    myFile.print(",");
    myFile.print(bmp.readPressure());
    myFile.print(",");
    myFile.print(bmp.readTemperature());
    myFile.print(",");
    myFile.println(bmp.readAltitude(SEA_PRESSURE));
    myFile.flush();
    delay(500);
}

