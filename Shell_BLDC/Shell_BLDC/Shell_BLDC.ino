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

const moduleDesc_S prints = {
    &printHello,
};
const moduleDesc_S prints2 = {
    NULL,
};

/*****************************************************************
*                       S E T U P    L O O P                     *
******************************************************************/
void setup(void) {
# if SERIAL_DEBUG
    Serial.begin(115200);
# endif
    static const moduleDesc_S moduleCLK_1[] = {prints, prints2, prints};

    timer1.interruptInit(LEDC_TIMER1, MS1000);
    //timer0.interruptInit(LEDC_TIMER0, MS50);
    timer1.modulesInit(COUNTOF(moduleCLK_1), moduleCLK_1); 

}

/*****************************************************************
*                         M A I N  L O O P                       *
******************************************************************/
void loop(void) {
//    if (timer0.checkTimer()) {
//# if SERIAL_DEBUG
//        Serial.print("Timer 0: ");
//        Serial.println(timer0.flag.counter);
//# endif
//    }
    if (timer1.checkTimer()) {
# if SERIAL_DEBUG
        Serial.print("Timer 1: ");
        Serial.println(timer1.flag.counter);
# endif
    }
}

