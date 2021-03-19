// Внимание! Проверь пароль WIFI_PASS в config_wifi.h

void initETH()
{
#ifdef ESP32
//  WiFi.disconnect(true);
#ifdef USE_DHCP
	log_cfg_ln("+ WiFi will use DCHP");
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(ESP_HOSTNAME);
#else
	if (WiFi.config(local_IP, gateway, subnet)) { log_cfg_ln("+ WiFi set static ip-address OK"); }
	else { log_cfg_ln("-- WiFi set static IP-address ERROR"); }
  WiFi.setHostname(ESP_HOSTNAME);
#endif

	log_cfg_ln(" . WiFi connecting to ", WIFI_NAME);
	WiFi.mode(WIFI_STA);
	WiFi.setSleep(false);
	WiFi.begin(WIFI_NAME, WIFI_PASS);
	log_cfg_ln(" . MAC: ", WiFi.macAddress());

	static char macbuff[17] = { "                " };
	String macStr = WiFi.macAddress();
	macStr.toCharArray(macbuff, 18);
	LD_printString_6x8("MAC:", LCDX1, 4);
	LD_printString_6x8(macbuff, LCDX1 + 25, 4);

	uint16_t wifiAttempts = WIFI_TIMEOUT + 30;

	while ((WiFi.status() != WL_CONNECTED) && (wifiAttempts > 0));
	{
		//check_WiFi();
		delay(100);
		wifiAttempts--;
		log_cfg(" .");
	} 
	
	log_cfg_ln("");

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
		if (showInfo > 0) log_info_ln("-- WiFi ERRORs: ", wifiErrors);
	}
	
	if (wifiErrors > WIFI_TIMEOUT)
	{
		if (showInfo > 0)
		{
			log_info_ln("-- CAN'T CONNECT WiFi");
			log_info_ln("-- RESTART NOW.");
		}
		delay(3000);
		ESP.restart();
	}
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

String IPtoStr(IPAddress ipAddr)
{
#ifdef ESP32
	static char IPbuff[17] = { "                " };
	sprintf(IPbuff, "%i.%i.%i.%i", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
	return String(IPbuff);
#endif
}

void displayIP()
{
#ifdef ESP32
	static char macbuff[17] = { "                " };
	sprintf(macbuff, "%i.%i.%i.%i", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
	LD_printString_6x8("IP:", LCDX1, 6);
	LD_printString_6x8(macbuff, LCDX1 + 22, 6);
#endif
}
