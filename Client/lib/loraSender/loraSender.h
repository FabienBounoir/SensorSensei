#ifndef LORA_SENDER_h
#define LORA_SENDER_h

#include <LoRa.h>

/**
 * @file loraSender.h
 * @brief Declaration of the class LoraSender
 *
 * @version 1.0
 *
 * @author Team Epitech (FPKGA)
 */

/**
 * @class LoraSender
 * @brief Declaration of the class LoraSender
 * @details This class is used to send data through the LoRa module
 */
class LoraSender
{
public:
  LoraSender();
  void begin();
  void sendLora(char *message);
  char *formatBmp280Data(double temperature, double pressure);
  char *formatDustSensor(double dust, boolean needHeader);
};

#endif