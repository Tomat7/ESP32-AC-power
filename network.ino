// Внимание! Проверь пароль WIFI_PASS в config_wifi.h

void initETH()
{
#ifdef ESP32
#ifdef USE_DHCP
	PRINTF("+ WiFi will use DCHP");
#else
	if (WiFi.config(local_IP, gateway, subnet)) { PRINTF("+ WiFi set static ip-address OK"); }
	else { PRINTF("-- WiFi set static IP-address ERROR"); }
#endif

	PRINTF(".  WiFi connecting to ", WIFI_NAME);
	WiFi.mode(WIFI_STA);
	WiFi.setSleep(false);
	WiFi.begin(WIFI_NAME, WIFI_PASS);
	PRINTF(".  MAC: ", WiFi.macAddress());

	static char macbuff[17] = { "                " };
	String macStr = WiFi.macAddress();
	macStr.toCharArray(macbuff, 18);
	LD_printString_6x8("MAC:", LCDX1, 2);
	LD_printString_6x8(macbuff, LCDX1 + 25, 2);

	uint16_t wifiAttempts = WIFI_TIMEOUT;

	while ((WiFi.status() != WL_CONNECTED) && (wifiAttempts > 0));
	{
		//check_WiFi();
		delay(100);
		wifiAttempts--;
		PRINT(".");
	} 
	
	PRINTLN("");
#endif // ESP32
}

void check_WiFi()
{
#ifdef ESP32
	if (WiFi.status() == WL_CONNECTED) 
	{ 
		wifiErrors = 0; 
		PRINTLN("+ WiFi ok");
	}
	else 
	{ 
		wifiErrors++;
		PRINTF("-- WiFi ERRORs: ", wifiErrors);
	}
	
	if (wifiErrors > WIFI_TIMEOUT)
	{
		PRINTLN("-- CAN'T CONNECT WiFi");
		PRINTLN("-- RESTART NOW.");
		delay(3000);
		ESP.restart();
	}
#endif
}

void serialIP()
{
#ifdef ESP32
	PRINTF(".  IP: ", WiFi.localIP());
	PRINTF(".  MASK: ", WiFi.subnetMask());
	PRINTF(".  GATEWAY: ", WiFi.gatewayIP());
#endif
}

void displayIP()
{
#ifdef ESP32
	static char macbuff[17] = { "                " };
	sprintf(macbuff, "%i.%i.%i.%i", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
	LD_printString_6x8("IP:", LCDX1, 4);
	LD_printString_6x8(macbuff, LCDX1 + 22, 4);
#endif
}
