#include <stdio.h>
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"

#include "Nvs.h"
#include "Bluetooth.h"
#include "Json_parse.h"

#include "Uart0.h"
#include "Led.h"
#include "E2prom.h"
#include "sht31.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"



void timer_periodic_cb(void *arg);

esp_timer_handle_t timer_periodic_handle = 0; //定时器句柄

esp_timer_create_args_t timer_periodic_arg = {
    .callback =
        &timer_periodic_cb,
    .arg = NULL,
    .name = "PeriodicTimer"};

void timer_periodic_cb(void *arg) //1ms中断一次
{
    static int64_t timer_count = 0;

    timer_count++;
    if (timer_count >= 1000) //1s
    {
        timer_count = 0;

        sht31_readTempHum();
        double Temperature = sht31_readTemperature();
        double Humidity = sht31_readHumidity();
        //printf("Temperature=%.2f,Humidity=%.2f\n", Temperature, Humidity);
        
        char gatt_name[100];
        int len = sprintf(gatt_name, "%.2f,%.2f", Temperature, Humidity);
        raw_scan_rsp_data[0] = len + 1;
        raw_scan_rsp_data[1] = 0x09;
        for(int i = 0; i<len; i++)
        {
            raw_scan_rsp_data[2+i] = gatt_name[i];
        }
        esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, raw_scan_rsp_data[0]+1);
    }

}


static void Uart0_Task(void *arg)
{
    while (1)
    {
        Uart0_read();
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}


void app_main(void)
{
    nvs_flash_init(); //初始化flash

    Led_Init();
    //E2prom_Init();
    Uart0_Init();
    i2c_init();
    xTaskCreate(Uart0_Task, "Uart0_Task", 4096, NULL, 10, NULL);

    ble_app_start();

  /*******************************timer 1s init**********************************************/
  esp_err_t err = esp_timer_create(&timer_periodic_arg, &timer_periodic_handle);
  err = esp_timer_start_periodic(timer_periodic_handle, 1000); //创建定时器，单位us，定时1ms
  if (err != ESP_OK)
  {
    printf("timer periodic create err code:%d\n", err);
  }

    
}
