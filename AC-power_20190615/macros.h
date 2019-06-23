#ifndef _MACROS_h
#define _MACROS_h

#if defined(OLED_SH1106)
#define LCDX1 0           // смещение 1-го "столбца" на экране
#define LCDX2 65          // смещение 2-го "столбца" на экране
#else
#define LCDX1 1           // смещение 1-го "столбца" на экране
#define LCDX2 67          // смещение 2-го "столбца" на экране
#endif

#ifdef SERIAL_DEBUG
#ifndef SERIAL_INFO
#define SERIAL_INFO
#endif
#define DPRINTLN(...) (Serial.println(__VA_ARGS__))
#define DPRINT(...) (Serial.print(__VA_ARGS__))
#define DPRINTF(a, ...) Serial.print(a); Serial.println(__VA_ARGS__)
#else
#define DPRINTLN(...)
#define DPRINT(...)
#define DPRINTF(a, ...)
#endif  // SERIAL_DEBUG

#ifdef DEV_DEBUG
#define D(a) a
#else
#define D(a)
#endif  // SERIAL_DEBUG2

#ifdef SERIAL_INFO
#ifndef SERIAL_CONFIG
#define SERIAL_CONFIG
#endif
#define PRINTF(a, ...) Serial.print(a); Serial.println(__VA_ARGS__)
#define PRINTLN(...) (Serial.println(__VA_ARGS__))
#define PRINT(...) (Serial.print(__VA_ARGS__))
#else
#define PRINTF(a, ...)
#define PRINTLN(xArg)
#define PRINT(zArg)
#endif  // SERIAL_INFO

#ifdef USE_OLED
#define LD_init() LD.init()
#define LD_clearDisplay() LD.clearDisplay()
#define LD_printNumber(a) LD.printNumber(a)
#define LD_printString_6x8(a,b,c) LD.printString_6x8(a, b, c)
#define LD_printString_12x16(a,b,c) LD.printString_12x16(a, b, c)
#define LD_printChar_6x8(a) LD.printString_6x8(a)
#define LD_printChar_12x16(a) LD.printString_12x16(a)
#else
#define LD_init()
#define LD_clearDisplay()
#define LD_printNumber(a)
#define LD_printString_6x8(a,b,c)
#define LD_printString_12x16(a,b,c)
#define LD_printChar_6x8(a)
#define LD_printChar_12x16(a)
#endif  // USE_OLED

/*
#define DISP_init() LD.init()
#define DISP_clear() LD.clearDisplay()
#define DISP_Number(a) LD.printNumber(a)
#define DISP_String_6x8(a,b,c) LD.printString_6x8(a, b, c)
#define DISP_String_12x16(a,b,c) LD.printString_12x16(a, b, c)
#define DISP_Char_6x8(a) LD.printString_6x8(a)
#define DISP_Char_12x16(a) LD.printString_12x16(a)
*/
#define INCLUDE_vTaskDelay 1

#define DELAYx vTaskDelay(300 / portTICK_PERIOD_MS)

#define WAIT100 vTaskDelay(100 / portTICK_PERIOD_MS)
#define WAIT200 vTaskDelay(200 / portTICK_PERIOD_MS)
#define WAIT300 vTaskDelay(300 / portTICK_PERIOD_MS)

#endif //_MACROS_h

