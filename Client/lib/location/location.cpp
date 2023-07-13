// init a location cpp class
#include "location.hpp"

TinyGPSPlus gps;

/**
 * @file location.cpp
 *
 * @brief Définition de la classe location
 *
 * @author Team Epitech (FPKGA)
 *
 * @version 1.0
 *
 */

Location::Location()
{
    std::cout << "Location Class Init" << std::endl;
    longitude = 0;
    latitude = 0;
}

Location::~Location()
{
    std::cout << "Location Class Destroy" << std::endl;
}

/**
 * @brief Update localisation data
 *
 * @fn Location::update
 */
void Location::update()
{
    while (Serial.available() > 0)
    {
        gps.encode(Serial.read());
    }

    if (gps.location.isUpdated())
    {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat());
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng());

        longitude = gps.location.lng();
        latitude = gps.location.lat();
    }
}
