#pragma once

#define PLC_ID 0x0C	// Задает IP-address если нет USE_DHCP. See config_wifi.h for details.
#define SKETCHINFO __DATE__ " " __TIME__ " " __FILE__

//#define USE_DHCP		// если нет USE_DHCP IP-address будет задан на основе PLC_ID.
#define USE_MODBUS		// устанавливать мощность из регистров Модбаса
#define USE_SETSERIAL	// устанавливать мощность с СОМ-порта
#define USE_WEBSERVER	// устанавливать/показывать мощность с/на WEB-странице
#define USE_ENCODER		// устанавливать мощность с энкодера
#define USE_OLED		// можно работать и без дисплея
#define USE_OTA			// обновление по Wi-Fi (почти бесполезная фича)
#define USE_DS18B20		// использовать датчик температуры. коннфигурация ниже

#define TASK_ADC			// сбор ADC в отдельном task, а не в interrupt (несовместимо c TASK_SHOW)
#define TASK_INFO			// вывод информации в Serial в отдельном task, а не в loop()
#if defined(TASK_INFO) && defined (TASK_ADC)
#undef TASK_ADC				// выключаем ADC в отдельном task если вывод в Serial в отдельном task
#endif

#define POWER_MAX 3500		// больше этой мощности установить не получится
#define SHOW_PERIOD	1000	// как часто обновлять информацию на экране и в Serial
#define SERIAL_INFO		// выводить в COM-порт информацию
#define SERIAL_DEBUG	// выводить в COM-порт дополнительную информацию
#define DEV_DEBUG		// скомпилить DEBUG версию и выводить в COM-порт еще больше информации

// PIN configuration
#define PIN_U 39
#define PIN_I 36
#define PIN_ZCROSS 25
#define PIN_TRIAC 26

// Коэффициенты для измерителей тока и напряжения (как для датчика ACS712)
#define U_RATIO 0.2
#define I_RATIO 0.02
#define U_CORRECTION {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0.6,0.7,2.8,8.9,12,14.1,15.2,17.3,18.4}

// Смещение нуля датчиков тока и напряжения
#define U_ZERO 1931     // используется если при включении устройства не было питания на силовой части
#define I_ZERO 1942     // нужно только в некоторых случаях, при нормальной работе не применяется

#define ZC_CRAZY		// если ZeroCross прерывание выполняется слишком часто :-(
#define ZC_EDGE RISING	// FALLING, RISING

// Параметры АЦП
#define ADC_RATE 200    // количество отсчетов АЦП на ПОЛУволну - 200 (для прерываний)
#define ADC_WAVES 10    // количество обсчитываемых ПОЛУволн - 4
#define ADC_NOISE 1000  // попробуем "понизить" шум АЦП

// Параметры регулятора.
#define ANGLE_MIN 1000		// минимальный угол открытия - определяет MIN возможную мощность
#define ANGLE_MAX 10100		// максимальный угол открытия триака - определяет MAX возможную мощность
#define ANGLE_DELTA 100		// запас по времени для открытия триака

// Encoder config
#define ENCODER_pSW 16     // энкодер SW кнопка
#define ENCODER_pCLK 4    // Pin для энкодера CLK
#define ENCODER_pDT 17   // Pin для энкодера DT
#define ENCODER_STEP 50

// DS18B20 configuration
#define PIN_DS { 18 }    // pin на котором ds18b20 (не забывайте про подтягивающий резистор 4.7 кОм!)
#define DS_CONVTIME 750
#define DS_ERRORS 3
#define DS_MIN_T -55

// WEB page "button names"
#define WEB_POWER1 100
#define WEB_POWER2 500
#define WEB_POWER3 1000
#define WEB_POWER4 1500
#define WEB_POWER5 1700
#define WEB_POWER6 2400
#define WEB_POWER7 3000

// Modbus registers config
#define hrSECONDS 0
#define hrDSTEMP 1
#define hrPSET 2
#define hrPNOW 3
#define hrUNOW 4
#define hrINOW 5
#define hrU_CNTR 6
#define hrI_CNTR 7
#define MB_TIMEOUT 70					// сколько можно работать без Мастера не сбрасывая мощность
#define WIFI_TIMEOUT MB_TIMEOUT + 10	// сколько можно работать без WIFI до перезагрузки
