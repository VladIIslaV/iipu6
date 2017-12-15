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

    Wifi::getCommandLine("sudo iwlist scan | grep \'ESSID\\|Address\\|BSSID\\|WPA\'", result);

    //cout << result << endl;
    while(strstr(result, "Cell"))
    {
        strcpy(result, strstr(result, "Cell") + 19);
        for(j = 0; j < 17; j++)
            wire[i][j] = result[j];
        wire[i][j++] = '\t';
        wire[i][j++] = '\0';

        strcpy(result, strstr(result, "ESSID") + 7);
        for(j = 0; result[j] != '\"'; j++)
            tmp[j] = result[j];
        tmp[j++] = '\t';
        tmp[j] = '\0';
        cout << "### " << tmp << " ###" << endl;
        strcat(wire[i], tmp);


        if(strstr(result, "Cell") > strstr(result, "IE:") || !strstr(result, "Cell")){
            strcpy(result, strstr(result, "IE:"));

            if(result[4] == 'I')
                strcat(wire[i], "WPA2\t");
            else if(result[4] == 'W')
                strcat(wire[i], "WPA1\t");

        }
        i++;
    }
    delete(tmp);
    delete(result);
    return i;
}

