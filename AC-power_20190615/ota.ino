// Внимание! Проверь пароль OTA_PASS в config_wifi.h и в board.txt

void setup_OTA()
{
#ifdef USE_OTA
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASS);
    ArduinoOTA.setPort(OTA_PORT);

    ArduinoOTA.onStart([] ()          // switch off all the PWMs during upgrade
    {
		TEH.stop();
		delay(10);

#ifdef TASK_INFO
		vTaskDelete(taskInfo);
#endif
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) { type = "sketch"; }
        else { type = "filesystem"; }
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        PRINTLN("OTA update starting " + type);
     
        LD_clearDisplay();
        LD_printString_12x16("OTA update", LCDX1, 0);
    });

    ArduinoOTA.onProgress([] (unsigned int progress, unsigned int total)
    {
        Serial.printf(" .. %u%%\r", (progress / (total / 100)));
        LD_printString_12x16("%% ", 24, 3);
        LD_printNumber((long)(progress / (total / 100)));
    });

    ArduinoOTA.onEnd([] ()             // do a fancy thing with our board led at end
    {
        PRINTLN("\n OTA update finished!");
        LD_printString_12x16("OTA OK!", LCDX1, 6);
        delay(3000);
        //modbusON = true;
    });

    ArduinoOTA.onError([] (ota_error_t error)
    {
        String OTAErrorInfo;
        Serial.printf("OTA Error[%u]: ", error);
        LD_printString_12x16("OTA error", LCDX1, 3);

        if (error == OTA_AUTH_ERROR) { OTAErrorInfo = "OTA Auth Failed"; }
        else if (error == OTA_BEGIN_ERROR) { OTAErrorInfo = "OTA Begin Failed"; }
        else if (error == OTA_CONNECT_ERROR) { OTAErrorInfo = "OTA Connect Failed"; }
        else if (error == OTA_RECEIVE_ERROR) { OTAErrorInfo = "OTA Receive Failed"; }
        else if (error == OTA_END_ERROR) { OTAErrorInfo = "OTA End Failed"; }

        PRINTLN(OTAErrorInfo);
        LD_printString_6x8(OTAErrorInfo.c_str(), LCDX1, 5);
        delay(3000);
        PRINTLN("rebooting...");
        LD_printString_6x8("reboot...", LCDX1, 6);
        delay(1000);
        (void)error;
        ESP.restart();
    });

    /* setup the OTA server */
    ArduinoOTA.begin();
    PRINTLN("+ OTA activated.");
#else
    PRINTLN("-- NO OTA in this version.");
#endif
}

