#include <stdio.h>
#include "driver/i2s.h"
#include "MP3HeaderDecoder.hh"
#include "Alarm.mp3.h"

MP3HeaderDecoder mp3(I2S_NUM_0);

extern "C" void app_main(void)
{   
    mp3.Init(GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14);
    mp3.Play(Alarm_hupe_mp3, sizeof(Alarm_hupe_mp3));
    int64_t lastHupe = esp_timer_get_time();
    while (true)
    {
        mp3.Loop();
        int64_t now = esp_timer_get_time();
        if(now-lastHupe>2000000){
            mp3.Play(Alarm_hupe_mp3, sizeof(Alarm_hupe_mp3)); //Calling "Play" stops the previous mp3 file and start a new one
            lastHupe=now;
        }
    }
}
