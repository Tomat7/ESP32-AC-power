void log_cfg_addstr(String str0)
{
  strConfig += str0;
}

void log_cfg(String str0)
{
  CPRINT(str0);
  log_cfg_addstr(str0);
}

void log_cfg(String str0, String str1)
{
  CPRINT(str0);
  log_cfg_addstr(str0);
  CPRINT(str1);
  log_cfg_addstr(str1);
}

void log_cfg_ln(String str0)
{
  str0 += "\r\n";
  log_cfg(str0);
}

void log_cfg_ln(String str0, String str1)
{
  log_cfg(str0);
  log_cfg_ln(str1);
}


void log_info(String str0)
{
  PRINT(str0);
  Telnet_info(str0);
}

void log_info(String str0, uint16_t num1)
{
  log_info(str0);
  log_info(String(num1));
}

void log_info(String str0, float num1)
{
  log_info(str0);
  log_info(String(num1));
}

void log_info_ln(String str0)
{
  PRINTLN(str0);
  str0 += "\r\n\n";
  Telnet_info(str0);
}

void log_info_ln(String str0, String str1)
{
  log_info(str0);
  log_info_ln(str1);
}

void log_info_ln(String str0, uint16_t num1)
{
  log_info(str0);
  log_info_ln(String(num1));
}


void log_debug(String str0)
{
  PRINT(str0);
}

void log_debug_ln(String str0)
{
  PRINTLN(str0);
}

void log_debug_f(String str0, int16_t num1)
{
  PRINTF(str0, num1);
}
