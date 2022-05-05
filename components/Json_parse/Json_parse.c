#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cJSON.h>
#include "esp_system.h"
#include "Json_parse.h"
#include "Nvs.h"

#include "esp_wifi.h"
#include "E2prom.h"
#include "Bluetooth.h"
#include "Led.h"

esp_err_t parse_Uart0(char *json_data)
{
        cJSON *json_data_parse = NULL;
        cJSON *json_data_parse_ProductID = NULL;
        cJSON *json_data_parse_SeriesNumber = NULL;

        //if(strstr(json_data,"{")==NULL)
        if (json_data[0] != '{')
        {
                printf("uart0 Json Formatting error1\n");
                return 0;
        }

        json_data_parse = cJSON_Parse(json_data);
        if (json_data_parse == NULL) //如果数据包不为JSON则退出
        {
                printf("uart0 Json Formatting error\n");
                cJSON_Delete(json_data_parse);

                return 0;
        }
        else
        {
                return 1;
        }
}
