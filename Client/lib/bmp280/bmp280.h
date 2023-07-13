#ifndef BMP280_h
#define BMP280_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/**
 * @file bmp280.h
 * @brief Déclaration de la classe Bmp280
 *
 * @version 1.0
 *
 * @author Team Epitech (FPKGA)
 */

/**
 * @class Bmp280
 * @brief Declaration of the class Bmp280
 * @details This class is used to get the temperature and pressure from the bmp280 sensor
 */
class Bmp280
{
public:
  Bmp280();
  void begin();
  float readTemperature(); // Temperature in C
  float readPressure();    // Pressure in hPa
private:
  Adafruit_BMP280 bmp;
};

#endif