#include <Arduino.h>
#include "../lib/location/location.hpp"

#include <Wire.h>
#include <loraSender.h>
#include <bmp280.h>
#include <GP2YDustSensor.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define BAND 866E6

const uint8_t SHARP_LED_PIN = 0x3FF44020; // Sharp Dust/particle sensor Led Pin (PIN 32)
const uint8_t SHARP_VO_PIN = 0x3FF44004;  // Sharp Dust/particle analog out pin used for reading (PIN 4)

Location location;
GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

int counter = 0;

Bmp280 bmp280;
LoraSender lora;

/**
 * @brief Setup the client
 *
 * @fn setup
 */
void setup()
{
  Serial.println("Client initializing...");

  // Init Serial bitrate
  Serial.begin(115200);

  // Init LoRa
  lora.begin();

  // Init Bmp280
  bmp280.begin();

  // Init Dust Sensor
  dustSensor.begin();

  delay(2000);
}

/**
 * @brief The main loop
 *
 * @fn loop
 */
void loop()
{
  // Get Bmp280 data
  Serial.print(bmp280.readTemperature());
  Serial.println(" *C");
  Serial.print(bmp280.readPressure());
  Serial.println(" hPa");

  // Get Dust Sensor data
  Serial.print(dustSensor.getDustDensity());
  Serial.print(" ug/m3; Running average: ");
  Serial.print(dustSensor.getRunningAverage());
  Serial.println(" ug/m3");

  Serial.print("Sending packet n°");
  Serial.print(counter);
  Serial.println(" :");

  char *trame = strcat(lora.formatBmp280Data(bmp280.readTemperature(), bmp280.readPressure()), lora.formatDustSensor(dustSensor.getDustDensity(), false));
  Serial.println(trame);

  // Send LoRa packet to receiver
  lora.sendLora(trame);

  // Get Localisation
  // location.update();

  counter++;

  // Wait 10 seconds before sending the next packet
  delay(10000);
}