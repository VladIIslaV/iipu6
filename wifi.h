#ifndef WIFI_H
#define WIFI_H

#include "stdafx.h"

class Wifi
{
public:
    static int getCommandLine(const char* command, char* result);
    static int getWifiList(char** result);
    static void getField(char* source, char* destination, const char* field_name, int offset, const char last_sign);
    static void connect(const char* ESSID);
};

#endif // WIFI_H
