#include "network.h"
#include <WiFi.h>
#include <network.h>
#include <HTTPClient.h>

/**
 * @file network.cpp
 *
 * @brief Définition de la classe bmp280
 *
 * @author Team Epitech (FPKGA)
 *
 * @version 1.0
 *
 */

/**
 * @brief Etablish a connection to the network
 *
 * @fn Network::connection(char *ssid, char *password)
 */
void Network::connection(char *ssid, char *password)
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
}

/**
 * @brief Send BMP data to the API
 *
 * @fn Network::postBMP(char *url, char *data)
 */
int Network::postBMP(char *url, char *data)
{
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", "esp32-ABDECF");
    http.addHeader("X-Pin", "3");
    int httpCode = http.POST(data);
    http.end();

    Serial.println(httpCode);

    return httpCode;
}

/**
 * @brief Send Dust data to the API
 *
 * @fn Network::postDust(char *url, char *data)
 */
int Network::postDust(char *url, char *data)
{
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", "esp32-ABDECF");
    http.addHeader("X-Pin", "1");
    int httpCode = http.POST(data);
    http.end();

    Serial.println(httpCode);

    return httpCode;
}

/**
 * @brief Get data from the API
 *
 * @fn Network::get(char *url)
 */
int Network::get(char *url)
{
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return httpResponseCode;
}
Network network;