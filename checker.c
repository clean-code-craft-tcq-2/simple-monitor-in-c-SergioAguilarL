#include <stdio.h>
#include <assert.h>

#define TEMPERATURE_LOW_LIMIT 0
#define TEMPERATURE_HIGH_LIMIT 45
#define SOC_LOW_LIMIT 20
#define SOC_HIGH_LIMIT 80
#define CHARGERATE_LOW_LIMIT 0
#define CHARGERATE_HIGH_LIMIT 0.8
#define NOT_OK 1
#define E_OK 0
#define LOW  0 
#define IN_RANGE 1
#define HIGH 2

int magnitudInRange(float lowLimit, float highLimit, float magnitud)
{
    int retVal = IN_RANGE;
    if(magnitud <= lowLimit )
    {
        retVal = LOW;
    }
    else if(magnitud >= highLimit)
    {
        retVal = HIGH;
    }
    return  retVal;
}

int printMessage(const char* magnitud, int state)
{
    int retVal;
    const char* magnitudState[] = {"low", "in range","high"};
    printf("%s",magnitud);
    printf(" is ");
    printf("%s\n", magnitudState[state]);
    if(state == 1)
    {
        retVal = E_OK;
    }
    else
    {
        retVal = NOT_OK;
    }

    return retVal;
}

int batteryIsOk(float temperature, float soc, float chargeRate)
{
    int retval = E_OK;
    int magnitudState = 0;
    const char* magnitudArray[] = {"temperature","SOC","chargeRate"};
     magnitudState =  magnitudInRange(TEMPERATURE_LOW_LIMIT,TEMPERATURE_HIGH_LIMIT,temperature);
    retval = printMessage(magnitudArray[0],magnitudState);
    magnitudState = magnitudInRange(SOC_LOW_LIMIT,SOC_HIGH_LIMIT,soc);
    retval |= printMessage(magnitudArray[1],magnitudState);
    magnitudState = magnitudInRange(CHARGERATE_LOW_LIMIT,CHARGERATE_HIGH_LIMIT,chargeRate);
    retval |= printMessage(magnitudArray[2],magnitudState);
    return retval;
}

int main() {

    //TC1 magnitudInRange input lowLimit
    assert(magnitudInRange(0,45,0) == LOW);
    //TC2 magnitudInRange input middle range value
    assert(magnitudInRange(0,45,20) == IN_RANGE);
    //TC3 magnitudInRange input highLimit 
    assert(magnitudInRange(0,45,45) == HIGH);
    
    //TC4 batteryIsOk Temperature is HIGH
    assert(batteryIsOk(50,40,0.5)== NOT_OK);
    //TC5 batteryIsOk SOC is HIGH
    assert(batteryIsOk(20,100,0.5)== NOT_OK);
    //TC6 batteryIsOk chargeRate is HIGH
    assert(batteryIsOk(20,40,1)== NOT_OK);
    //TC7 batteryIsOk Temperature is LOW
    assert(batteryIsOk(-10,40,0.5)== NOT_OK);
    //TC8 batteryIsOk SOC is LOW
    assert(batteryIsOk(20,10,0.5)== NOT_OK);
    //TC69 batteryIsOk chargeRate is LOW
    assert(batteryIsOk(20,40,-0.1)== NOT_OK);
    //TC10 batteryIsOk all in range
    assert(batteryIsOk(20,40,0.5)== E_OK);

    //TC11 printmessage low
    assert(printMessage("temperature", 0) == NOT_OK);
    //TC11 printmessage in range
    assert(printMessage("temperature", 1) == E_OK);
    //TC11 printmessage High
    assert(printMessage("temperature",2) == NOT_OK);
}
