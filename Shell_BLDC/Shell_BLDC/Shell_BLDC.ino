/*
 Author:            Escuderia Borregos CCM.
 Description:       ESP32 Firmware code for the Shell Eco-marathon 2020 @ Sonoma, CA.
 Colaborators:      Israel Cayetano, Fernando Zaragoza, Angel Romero
*/

/******************************************************************
 *                         I N C L U D E S                        *
 ******************************************************************/

#include "DRV8323H.h"                   // #include "PWM_ESP32.h" is included in the BLDC Driver header file.
#include "ESP32_ExtInterrupt.h"
#include "ESP32_TimInterrupt.h"
#include "Module.h"

 /*****************************************************************
 *                  C L A S S   I N S T A N C E S                 *
 ******************************************************************/
Timer timer0;
Timer timer1;

 /*****************************************************************
 *                G L O B A L   D E F I N I T I O N S             *
 ******************************************************************/
static void printHello(void) {
    Serial.println("Hello");
}
/*
static void fn(void) {

}
*/
const moduleDesc_S prints = {
    /*
    &fn,			// 1Hz   CLK function
    &fn,			// 10Hz  CLK function,			
    nullptr,		// 20Hz  CLK function
    &print_100Hz,   // 50Hz  CLK function
    NULL,		    // 100Hz CLK function
    &fn,            // 200Hz CLK function
    &fn,
    */
    &printHello,
};
const moduleDesc_S prints2 = {
    /*
    &fn,			// 1Hz   CLK function
    & fn,			// 10Hz  CLK function,			// 20Hz  CLK function
    //nullptr,		    // 50Hz  CLK function
    & print_100Hz,
    &print_100Hz,		// 100Hz CLK function
    & fn,            // 200Hz CLK function
    & fn,
    & fn
    */
    NULL,
};
 /*****************************************************************
 *                         M A I N  L O O P S                      *
 ******************************************************************/

void setup() {
# if SERIAL_DEBUG
    Serial.begin(115200);
# endif
    static const moduleDesc_S moduleCLK_1[] = {prints, prints2, prints};

    timer1.interruptInit(LEDC_TIMER1, MS1000);
    //timer0.interruptInit(LEDC_TIMER0, MS50);

    //moduleCLK_1[0].periodic50Hz_CLK();
    //moduleCLK_1[1]->periodic50Hz_CLK();
    timer1.modulesInit(COUNTOF(moduleCLK_1), moduleCLK_1); 

}


void loop() {
    /*if (timer0.checkTimer()) {
# if SERIAL_DEBUG
        Serial.print("Timer 0: ");
        Serial.println(timer0.flag.counter);
# endif
    }*/
    if (timer1.checkTimer()) {
# if SERIAL_DEBUG
        Serial.print("Timer 1: ");
        Serial.println(timer1.flag.counter);
# endif
    }
}

