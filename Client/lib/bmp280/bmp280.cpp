#include "bmp280.h"

#define GY_BMP280_ADDRESS 0x76

/**
 * @file bmp280.cpp
 *
 * @brief Définition de la classe bmp280
 *
 * @author Team Epitech (FPKGA)
 *
 * @version 1.0
 *
 */

Bmp280::Bmp280() {}

/**
 * @brief Initialize the bmp280 sensor
 *
 * @fn Bmp280::begin
 */
void Bmp280::begin()
{
  Wire.begin();
  bmp.begin(GY_BMP280_ADDRESS);
}

/**
 * @brief Read the temperature from the bmp280 sensor
 *
 * @fn Bmp280::readTemperature
 */
float Bmp280::readTemperature()
{
  return bmp.readTemperature();
}

/**
 * @brief Read the pressure from the bmp280 sensor
 *
 * @fn Bmp280::readPressure
 */
float Bmp280::readPressure()
{
  return bmp.readPressure() * 10;
}
