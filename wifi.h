#ifndef WIFI_H
#define WIFI_H

#include "stdafx.h"

class Wifi
{
public:
    Wifi();
    static int getCommandLine(const char*, char*);
    static int getWifiList(char**);

};

#endif // WIFI_H
