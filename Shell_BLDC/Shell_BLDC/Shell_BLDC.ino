/*
 Author:            Escuderia Borregos CCM.
 Description:       ESP32 Firmware code for the Shell Eco-marathon 2020 @ Sonoma, CA.
 Colaborators:      Israel Cayetano, Fernando Zaragoza
*/

/******************************************************************
 *            I N C L U D E S   &  D E F I N E S                   *
 ******************************************************************/

#include "DRV8323H.h"                   // #include "PWM_ESP32.h" is included in the BLDC Driver header file.
#include "ESP32_ExtInterrupt.h"
#include "ESP32_TimInterrupt.h"
#include "Module.h"

 /*****************************************************************
 *                G L O B A L   F U N C T I O N S                *
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
 *               G L O B A L    D E C L A R A T I O N S             *
 ******************************************************************/
static const uint8_t inh[]      = INH_NIMU_PINS;
static const uint8_t inl[]      = INL_NIMU_PINS;
static const uint8_t encoder[]  = ENC_NIMU_PINS;
static const uint8_t n_fault     = 24;
/*****************************************************************
*                  C L A S S   I N S T A N C E S                 *
******************************************************************/
Timer   timer0;
Timer   timer1;
BLDC    motor(inh, inl, encoder, n_fault);

/*****************************************************************
*                       S E T U P    L O O P                     *
******************************************************************/
static const moduleDesc_S moduleCLK_1[] = { motor.DRV_desc, prints2, prints };

void setup(void) {
# if SERIAL_DEBUG
    Serial.begin(115200);
# endif

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
    if (motor.encA.available() || motor.encB.available() || motor.encC.available())
    {
        motor.doSequence(FORWARD, 5);
    }

}

