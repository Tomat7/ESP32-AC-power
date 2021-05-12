
void setup_Telnet()
{
#ifdef USE_TELNET
	telnetd.begin();
	telnetd.setNoDelay(true);
	log_cfg_ln("+ TELNET server started.");
#else
	log_cfg_ln("-- NO TELNET server in this version.");
#endif	// USE_TELNET
}

void check_Telnet()
{
#ifdef USE_TELNET
	uint8_t i;

	//check if there are any NEW clients
	if (telnetd.hasClient())
	{
		for (i = 0; i < MAX_SRV_CLIENTS; i++)				//find free/disconnected spot
		{

			if (!rClients[i] || !rClients[i].connected())
			{
				if (rClients[i]) rClients[i].stop();
				rClients[i] = telnetd.available();
				if (!rClients[i]) CPRINTLN("available broken");

				CPRINT("New client: "); CPRINT(i); CPRINT(' '); CPRINTLN(rClients[i].remoteIP());
				Telnet_print(strConfig, i);
				Telnet_print1(strUptime(), i);
				break;
			}
		}
		if (i >= MAX_SRV_CLIENTS) { telnetd.available().stop(); }	//no free/disconnected spot so reject
	}

	for (i = 0; i < MAX_SRV_CLIENTS; i++)		//check Telnet-clients for data
	{
		if (rClients[i] && rClients[i].connected()) { Telnet_input(i); }
		else { if (rClients[i]) rClients[i].stop(); }
		
		if (!rClients[i] || !rClients[i].connected()) 
		{ 
			showInfo = 0;
			showPeriod = SHOW_PERIOD;
		}
	}

#endif // USE_TELNET
}

void stop_Telnet()
{
#ifdef USE_TELNET
	CPRINTLN("- TELNET: stop all connection.");
	for (uint8_t i = 0; i < MAX_SRV_CLIENTS; i++)
	{
		if (rClients[i]) rClients[i].stop();
	}
	delay(100);
#endif	// USE_TELNET
}

#ifdef USE_TELNET

void Telnet_print(String msg0, uint8_t z)
{
	uint32_t len0 = msg0.length();
	char ch0[len0];
	msg0.toCharArray(ch0, len0);
	rClients[z].write(ch0, len0);
}

void Telnet_print1(String msg0, uint8_t z)
{
	Telnet_print("\r\n", z);
	Telnet_println(msg0, z);
}

void Telnet_println(String msg0, uint8_t z)
{
	msg0 += "\r\n\n";
	Telnet_print(msg0, z);
	Telnet_print("PLC-" + String(PLC_ID) + "/> ", z);
}

void Telnet_info(String msg0)
{
	for (uint8_t s = 0; s < MAX_SRV_CLIENTS; s++)
	{
		if (rClients[s] && rClients[s].connected())
		{
			Telnet_print(msg0, s);
			delay(1);
		}
	}
}

void Telnet_input(uint8_t x)
{
	String T1, Var;

	while (rClients[x].available()) 
	{
		char ch = rClients[x].read();
		Var += ch;
		if ((ch == '\n') || !rClients[x].available())
		{
			Var.toUpperCase();        // ??
			if (Var.substring(0, 2) == "SP")
			{
				T1 = Var.substring(Var.indexOf("SP", 2) + 3); 
				float Pserial = T1.toFloat();     
				CPRINTF("Set ShowPeriod from Telnet: ", Pserial);
				Telnet_print("ShowPeriod set to: ", x);
				Telnet_println(String(Pserial), x);
				showPeriod = (uint16_t)(Pserial);
			}
			else if (Var.substring(0, 3) == "RST")
			{
				Serial.println("Restarting... ");
				Telnet_println("Restarting...", x);
				delay(1000);
				ESP.restart();
			}
			else if (Var.substring(0, 4) == "STOP")
			{
				showInfo = 0;
				Serial.println("Stop... ");
				Telnet_println("Stop...", x);
			}
			else if (Var.substring(0, 4) == "INFO")
			{
				showInfo = 1;
				Serial.println("Info... ");
				Telnet_println("Info...", x);
			}
			else if (Var.substring(0, 4) == "MORE")
			{
				showInfo = 2;
				Serial.println("More... ");
				Telnet_println("More...", x);
			}
			else if (Var.substring(0, 5) == "DEBUG")
			{
				showInfo = 3;
				Serial.println("Debug... ");
				Telnet_println("Debug...", x);
				Serial.println(strUptime());
				Telnet_print1(strUptime(), x);
				//showDebug = true;
			}
			else if (Var.substring(0, 6) == "UPTIME")
			{
				//Serial.println("Uptime... ");
				//Telnet_println("Uptime...", x);
				Serial.println(strUptime());
				Telnet_print1(strUptime(), x);
				Serial.println(strFreeMem());
				Telnet_print1(strFreeMem(), x);
				//showDebug = true;
			}
			
			else if (Var.substring(0, 4) == "CONF")
			{
				Serial.println("Config... ");
				Telnet_println(strConfig, x);
			}
			else if (Var.substring(0, 4) == "TIME")
			{
				//Telnet_println(strGetLocalTime(), x);
				//showMore = true;
			}
			else
			{
				Telnet_print("PLC-" + String(PLC_ID) + "/> ", x);
				//ch = rClients[x].read();
				//rClients[x].flush();
			}
			Var = "";
		}
	}
}

String strUptime()
{
	char UpTimeStr[20];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;
	snprintf(UpTimeStr, 50, "Uptime:%4d:%02d:%02d", hr, min % 60, sec % 60);
	return String(UpTimeStr);
}

String strFreeMem()
{
	char FreeMemStr[30];
	snprintf(FreeMemStr, 50, "Free memory:%7d bytes", ESP.getFreeHeap());
	return String(FreeMemStr);
}

#endif	// USE_TELNET

