#ifndef _LOCATION_hpp
#define _LOCATION_hpp

#include <iostream>
#include <TinyGPSPlus.h>

/**
 * @file location.h
 * @brief Déclaration de la classe location
 *
 * @version 1.0
 *
 * @author Team Epitech (FPKGA)
 */

/**
 * @class Location
 * @brief Declaration of the class Location
 * @details This class is used to get the location of the device
 */
class Location
{
public:
    Location();
    ~Location();
    void update();
    double longitude;
    double latitude;
};

extern Location location;
#endif
