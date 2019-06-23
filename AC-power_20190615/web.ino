
void setup_Web()
{
#ifdef USE_WEBSERVER
    if (MDNS.begin("esp32")) { PRINTLN("+ MDNS responder started."); }
    server.on("/", handleRoot);
    server.on("/on", handleON);
    server.on("/off", handleOFF);
    //server.on("/inline", [] () { server.send(200, "text/plain", "this works as well"); });
    server.onNotFound(handleNotFound);
    server.begin();
    PRINTLN("+ HTTP server started.");
#else
    PRINTLN("-- NO HTTP server in this version.");
#endif
}

#ifdef USE_WEBSERVER
void handleRoot()
{
    server.send(200, "text/html", SendHTML(TEH.Pset));
}

void handleON()
{
    if ((server.args() == 1) && (server.argName(0) == "p"))
    {
        String sPweb = server.arg(0);
        Pweb = sPweb.toInt();
        setPower(Pweb);
    }
    server.send(200, "text/html", SendHTML(Pweb));
}

void handleOFF()
{
    Pweb = 0;
    setPower(Pweb);
    server.send(200, "text/html", SendHTML(Pweb));
}

void handleNotFound()
{
    //String UriPath = server.uri();
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    //message += UriPath.substring(1, 3);
    //message += UriPath.substring(3);
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}

String SendHTML(uint16_t Ptmp)
{
    char HtmlStr[50];
	//char CmpDate[10];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<meta http-equiv=\"refresh\" content=\"5;url=/\">\n";
    ptr += "<title>Power Controller</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr += ".button-on {background-color: #3366CC;}\n"; //#3498db #336699
    ptr += ".button-on:active {background-color: #003399;}\n"; //#2980b9
    ptr += ".button-off {background-color: #FF0033;}\n";
    ptr += ".button-off:active {background-color: #CC0000;}\n";
    ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<h1>ESP32 AC Power regulator</h1>\n";

    snprintf(HtmlStr, 50, "<h3>Pset: %4d, Pnow: %4d.</h3>\n", Ptmp, TEH.Pnow);
    ptr += HtmlStr;
	snprintf(HtmlStr, 50, "<h3>Temp1: %.2f </h3>\n", dsTemp[0]);
	ptr += HtmlStr;
	D(snprintf(HtmlStr, 50, "<p>_Ucntr: %4d, _Icntr: %4d.</p>\n", TEH._Ucntr, TEH._Icntr));
	D(ptr += HtmlStr);
	D(snprintf(HtmlStr, 50, "<p>_ZCcntr/sec: %4d, RMScntr/sec: %4d.</p>\n", TEH.CounterZC, TEH.CounterRMS));
	D(ptr += HtmlStr);
	
	snprintf(HtmlStr, 50, "<p>Uptime: %02d:%02d:%02d</p>\n", hr, min % 60, sec % 60);
    ptr += HtmlStr;

    ptr += "<a class=\"button button-off\" href=\"/off\">STOP</a>\n";
    //ptr += "<p><a class=\"button button-on\" href=\"/on?p=100\">100</a>\n";
    
    String PButton = "<p><a class=\"button button-on\" href=\"/on?p=";

#ifdef WEB_POWER1
    snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER1, WEB_POWER1);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER2
	snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER2, WEB_POWER2);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER3
	snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER3, WEB_POWER3);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER4
    snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER4, WEB_POWER4);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER5
    snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER5, WEB_POWER5);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER6
    snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER6, WEB_POWER6);
    ptr += PButton + HtmlStr;
#endif
#ifdef WEB_POWER7
	snprintf(HtmlStr, 50, "%d\">%d</a>", WEB_POWER7, WEB_POWER7);
	ptr += PButton + HtmlStr;
#endif

    /* ptr += "<p><a class=\"button button-on\" href=\"/on?p=1000\">1000</a>\n";
       ptr += "<p><a class=\"button button-on\" href=\"/on?p=1500\">1500</a>\n";
       ptr += "<p><a class=\"button button-on\" href=\"/on?p=1700\">1700</a>\n";
       ptr += "<p><a class=\"button button-on\" href=\"/on?p=3000\">3000</a>\n";
      */

	snprintf(HtmlStr, 50, "<p>Compiled on %s (C) Tomat7</p>\n", __DATE__);
	ptr += HtmlStr;
	
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}

void DateToBuff(char const *date, char *buff) 
{
	int month, day, year;
	static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
	sscanf(date, "%s %d %d", buff, &day, &year);
	month = (strstr(month_names, buff) - month_names) / 3 + 1;
	snprintf(buff, 10, "%d%02d%02d", year, month, day);
}
#endif
