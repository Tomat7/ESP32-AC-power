// Внимание! Проверь пароль WIFI_PASS в config_wifi.h

void setup_Network()   //Config Modbus IP
{
#ifdef ESP32
	log_cfg_ln("+ WiFi connecting to SSID: ", WIFI_NAME);
	displaySSID();
	log_cfg_ln(" . MAC: ", WiFi.macAddress());
	displayMAC();
	initETH();
	check_WiFi();
	//	if (!wifiErrors) { log_cfg_ln(" + WiFi connected!"); }
	//	else { log_cfg_ln("-- WiFi NOT FOUND! Will try to connect later."); }
	serialIP();
	displayIP();
	check_WiFi();
	if (!wifiErrors) { log_cfg_ln(" + WiFi setup OK"); }
	else { log_cfg_ln("-- WiFi setup finished with ERROR"); }
#endif // ESP32
}

void initETH()
{
#ifdef ESP32
	//  WiFi.disconnect(true);
#ifdef USE_DHCP
	log_cfg_ln(" . WiFi will use DCHP");
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(ESP_HOSTNAME);
#else
	if (WiFi.config(local_IP, gateway, subnet)) log_cfg_ln(" . WiFi configured static IP");
	else log_cfg_ln("-- WiFi static IP-address ERROR");
	WiFi.setHostname(ESP_HOSTNAME);
#endif // USE_DHCP

//	log_cfg_ln(" . WiFi connecting to ", WIFI_NAME);
	WiFi.mode(WIFI_STA);
	WiFi.setSleep(false);
	WiFi.begin(WIFI_NAME, WIFI_PASS);
//	log_cfg_ln(" . MAC: ", WiFi.macAddress());

	while ((WiFi.status() != WL_CONNECTED) && (wifiErrors < WIFI_TIMEOUT))
	{
		delay(500);
		wifiErrors++;
		log_cfg(" .");
	}

	log_cfg_ln(" ok");

#endif // ESP32
}

void check_WiFi()
{
#ifdef ESP32
	if (WiFi.status() == WL_CONNECTED)
	{
		wifiErrors = 0;
		if (showInfo > 0) log_info_ln("+ WiFi ok");
	}
	else
	{
		wifiErrors++;
		log_info_ln("-- WiFi errors: ", wifiErrors);
	}

	if (wifiErrors > WIFI_TIMEOUT)
	{
		log_info_ln("-- WiFi not found. RESTART NOW!");
		LD_printString_12x16("WiFi error!", LCDX1, 0);
		LD_printString_6x8("rebooting...", LCDX1, 7);
		delay(3000);
		ESP.restart();
	}
#endif
}


String IPtoStr(IPAddress ipAddr)
{
#ifdef ESP32
	static char IPbuff[17] = { "                " };
	sprintf(IPbuff, "%i.%i.%i.%i", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
	return String(IPbuff);
#endif
}

void displaySSID()
{
#ifdef ESP32
	LD_printString_6x8("SSID:", LCDX1, 3);
	LD_printString_6x8(WIFI_NAME, LCDX1 + 32, 3);
#endif
}

void displayMAC()
{
#ifdef ESP32
	static char macbuff[17] = { "                " };
	String macStr = WiFi.macAddress();
	macStr.toCharArray(macbuff, 18);
	LD_printString_6x8("MAC:", LCDX1, 5);
	LD_printString_6x8(macbuff, LCDX1 + 25, 5);
#endif
}

void displayIP()
{
#ifdef ESP32
	static char macbuff[17] = { "                " };
	sprintf(macbuff, "%i.%i.%i.%i", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
	LD_printString_6x8("IP:", LCDX1, 7);
	LD_printString_6x8(macbuff, LCDX1 + 22, 7);
#endif
}

void serialIP()
{
#ifdef ESP32
	log_cfg_ln(" . IP: ", IPtoStr(WiFi.localIP()));
	log_cfg_ln(" . MASK: ", IPtoStr(WiFi.subnetMask()));
	log_cfg_ln(" . GATEWAY: ", IPtoStr(WiFi.gatewayIP()));
#endif
}

