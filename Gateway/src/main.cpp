/**
 * Team Epitech (FPKGA)
 * 
 * Programme utilisé pour la gateway LoRa
 * V 1.0
 */


#include <Arduino.h>
#include <M5Stack.h>
#include <LoRa.h>
#include <network.h>

#define BAND 868E6 // LoRa frequency band

const char *ssid = "BadIphone";
const char *password = "motdepasse";

char *url = "http://api.sensor.community/v1/push-sensor-data/";

int packetCount = 0;
int goodPacketCount = 0;
int badPacketCount = 0;

void setup()
{
  M5.begin();
  Serial.begin(115200);

  M5.Lcd.clear(BLUE);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Initialisation de la gateway");

  while (!LoRa.begin(BAND))
  {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("LoRa initialization failed. Check your connections.");
    Serial.println("LoRa initialization failed. Check your connections.");
    delay(2000);
  }
  network.connection(const_cast<char *>(ssid), const_cast<char *>(password));
  Serial.println("LoRa receiver initialized!");
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("LoRa receiver initialized!");
}

#include <stdlib.h>
char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    if (!dest || !src)
        return (NULL);
    for (; src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

int nb_word(char *str, char sep1)
{
    int words = 0;

    for (int i = 0, var = 0; str[i]; i++) {
        if ((str[i] != sep1 && str[i] != '\t') && var == 0) {
            words += 1;
            var = 1;
        } else if (str[i] == sep1 || str[i] == '\t')
            var = 0;
    }
    return (words);
}

char *create_word(int *let, char *str, char sep1)
{
    int i = 0;
    int j = 0;
    char *word;

    *let = 0;
    for (; str[i] == sep1 || str[i] == '\t'; i++);
    for (; (str[i] != sep1 && str[i] != '\t') && str[i] != 0; i++, *let += 1);
    *let = i;
    word = (char *)malloc(sizeof(char) * (*let + 1));
    if (word == NULL)
        return (NULL);
    for (; str[j] == sep1 || str[j] == '\t'; j++);
    for (i = j; (str[i] != sep1 && str[i] != '\t') &&
        str[i] != 0; i++)
        word[i - j] = str[i];
    word[i - j] = 0;
    return (word);
}

char **my_str_to_word_array(char *str, char sep1)
{
    int words = 0;
    char *word = NULL;
    char **word_array = NULL;
    int letters = 0;
    int i = 0;

    if (str == NULL)
        return (NULL);
    words = nb_word(str, sep1);
    word_array = (char**)malloc(sizeof(char *) * (words + 1));
    for (i = 0; i < words; i++) {
        word = create_word(&letters, str, sep1);
        str += letters;
        word_array[i] = word;
    }
    word_array[i] = NULL;
    return (word_array);
}

int my_strlen(char *str)
{
    int i = 0;

    if (!str)
        return (0);
    if (*str == '\0')
        return (0);
    for (; str[i] != '\0'; i++);
    return (i);
}

char *my_strdup(char *str)
{
    char *new_str = NULL;

    if (!str)
        return (NULL);
    new_str = (char *)malloc(sizeof(char) * my_strlen(str) + 1);
    if (new_str != NULL) {
        my_strcpy(new_str, str);
        return (new_str);
    } else
        return (NULL);
}

/**
 * @brief Deconstruct a trame into a string table
 *
 * @fn deconstruct(const char *trame)
 */
char** deconstruct(const char *trame)
{
  char *copy = strdup(trame);
  return my_str_to_word_array(copy, ';');
}

/**
 * @brief Clear a string table
 *
 * @fn clearStringTable(char *str[])
 */
void clearStringTable(char *str[])
{
  int arrayLength = sizeof(str) / sizeof(char *);

  for (int i = 0; i <= arrayLength; i++)
  {
    str[i] = NULL;
  }
  Serial.println("All strings cleared");
}

void loop()
{

  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
      M5.Lcd.clear(BLUE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.clear();

    packetCount++;

    M5.Lcd.print("Packet received: ");
    M5.Lcd.println(packetCount);

    while (LoRa.available())
    {
      char **data = deconstruct(LoRa.readString().c_str());
      if (String(data[0]) == "SENSOUNS")
      {
        goodPacketCount++;
        std::string messageBMP = std::string("{\"sensordatavalues\":[{\"value_type\":\"temperature\",\"value\":\"") + std::string(data[3]) + std::string("\"},{\"value_type\":\"pressure\",\"value\":\"") + std::string(data[5]) + std::string("\"}]}");

        M5.Lcd.println("");
        M5.Lcd.println("");
        M5.Lcd.println("Message: ");
        M5.Lcd.println(messageBMP.c_str());

        Serial.println("Message: " + String(messageBMP.c_str()));
        M5.Lcd.print("HTTP code: ");
        M5.Lcd.print(network.postBMP(url, const_cast<char *>(messageBMP.c_str())));

        std::string messageDust = std::string("{\"sensordatavalues\":[{\"value_type\":\"P1\",\"value\":\"") + std::string(data[7]) + std::string("\"}]}");

        Serial.println("Message: " + String(messageDust.c_str()));
        M5.Lcd.print(" ");
        M5.Lcd.print(network.postDust(url, const_cast<char *>(messageDust.c_str())));

        clearStringTable(data);
      }
      else
      {
        badPacketCount++;
        Serial.println("Erreur mauvaise trame");
      }
      Serial.println("Data: " + String(data[0]));

      M5.Lcd.println("");
      M5.Lcd.println("");
      M5.Lcd.print("Good packets: ");
      M5.Lcd.println(goodPacketCount);
      M5.Lcd.print("Bad packets: ");
      M5.Lcd.println(badPacketCount);
    }
  }
}