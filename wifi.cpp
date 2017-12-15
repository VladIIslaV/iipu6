#include "wifi.h"

Wifi::Wifi()
{

}

int Wifi::getCommandLine(const char *command, char* result)
{
    result[0] = '\0';
    char* tmp = new char[256];
    FILE *file = popen(command, "r");
    if(!file)
    {
        cout << "Open error" << endl;
        return 0;
    }
    int i = 0;
    for(i = 0; fgets(tmp, 256, file); i++)
        strcat(result, tmp);
    pclose(file);
    delete(tmp);
    return i;
}

int Wifi::getWifiList(char** wire)
{
    int i = 0, j = 0;
    char* result = new char[4096];
    char* tmp = new char[64];

    Wifi::getCommandLine("sudo iwlist scan | grep \'ESSID\\|Address\\|Quality\\|WPA\'", result);

    while(strstr(result, "Cell"))
    {
        getField(result, tmp, "Cell", 19, '\n');

        strcat(wire[i], tmp);
        getField(result, tmp, "Quality", 8, ' ');
        strcat(wire[i], tmp);
        getField(result, tmp, "ESSID", 7, '\"');
        strcat(wire[i], tmp);

        if(strstr(result, "Cell") > strstr(result, "IE:") || !strstr(result, "Cell")){
            strcpy(result, strstr(result, "IE:"));
            if(result[4] == 'I')
                strcat(wire[i], "WPA2\t\0");
            else if(result[4] == 'W')
                strcat(wire[i], "WPA1\t\0");
        }
        i++;
    }
    delete(tmp);
    delete(result);
    return i;
}

void Wifi::getField(char *source, char *destination, const char *field_name, int offset, const char last_sign)
{
    int i = 0;
    strcpy(source, strstr(source, field_name) + offset);
    for(i = 0; source[i] != last_sign; i++)
        destination[i] = source[i];
    destination[i++] = '\t';
    if(i < 12) destination[i++] = '\t';
    destination[i] = '\0';
}

