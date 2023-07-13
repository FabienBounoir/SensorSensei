#include "loraSender.h"
#include <LoRa.h>
#include <SPI.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

// #define BAND 866E6
#define BAND 868E6

char *DELIMITER = ";";
char *HEADER = "SENSOUNS";

/**
 * @file loraSender.cpp
 *
 * @brief Définition de la classe loraSender
 *
 * @author Team Epitech (FPKGA)
 *
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe LoraSender
 *
 * @fn LoraSender::LoraSender
 */
LoraSender::LoraSender()
{
}

/**
 * @brief Initialisation du module LoraSender
 *
 * @fn LoraSender::begin
 */
void LoraSender::begin()
{
  // LoRa
  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  Serial.println("LoRa Initializing OK!");
}

/**
 * @brief Format data from Bmp280
 *
 * @fn LoraSender::formatBmp280Data
 * @param temperature
 * @param pressure
 */
char *LoraSender::formatBmp280Data(double temperature, double pressure)
{
  // Create message for Bmp280
  std::string message = std::string(HEADER) + DELIMITER + "DATA" + DELIMITER + "TEMP" + DELIMITER + std::to_string(temperature) + DELIMITER + "PRESSURE" + DELIMITER + std::to_string(pressure);
  return const_cast<char *>(message.c_str());
}

/**
 * @brief Format data from Dust Sensor
 *
 * @fn LoraSender::formatDustSensor
 * @param dust
 * @param needHeader
 */
char *LoraSender::formatDustSensor(double dust, boolean needHeader = false)
{
  // Create message for Dust Sensor
  std::string message = needHeader ? std::string(HEADER) + DELIMITER + "DATA" + DELIMITER + "DUST" + DELIMITER + std::to_string(dust)
                                   : std::string(DELIMITER) + "DUST" + DELIMITER + std::to_string(dust);
  return const_cast<char *>(message.c_str());
}

/**
 * @brief Send data to Lora
 *
 * @fn LoraSender::sendLora
 * @param message
 */
void LoraSender::sendLora(char *message)
{
  // Send message
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
}