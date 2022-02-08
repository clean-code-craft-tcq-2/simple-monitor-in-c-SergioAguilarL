#include <stdio.h>
#include <assert.h>

#define TEMPERATURE_LOW_LIMIT 0
#define TEMPERATURE_HIGH_LIMIT 45
#define SOC_LOW_LIMIT 20
#define SOC_HIGH_LIMIT 80
#define CHARGERATE_LOW_LIMIT 0
#define CHARGERATE_HIGH_LIMIT 0.8
#define NOT_OK 0
#define E_OK 1

int magnitudInRange(float lowLimit, float highLimit, float magnitud)
{
    return  (magnitud > lowLimit && magnitud < highLimit);
}


int batteryIsOk(float temperature, float soc, float chargeRate)
{
    int retval = E_OK;
    if(!magnitudInRange(TEMPERATURE_LOW_LIMIT,TEMPERATURE_HIGH_LIMIT,temperature))
    {
        printf("Temperature out of range!\n");
        retval = NOT_OK;
    }
    else if (!magnitudInRange(SOC_LOW_LIMIT,SOC_HIGH_LIMIT,soc))
    {
        printf("State of Charge out of range!\n");
        retval = NOT_OK;
    }
    else if (!magnitudInRange(CHARGERATE_LOW_LIMIT,CHARGERATE_HIGH_LIMIT,chargeRate))
    {
        printf("Charge Rate out of range!\n");
        retval = NOT_OK;
    }
    return retval;
}

int main() {

    //TC1 magnitudInRange input lowLimit
    assert(magnitudInRange(0,45,0) == 0);
    //TC2 magnitudInRange input middle range value
    assert(magnitudInRange(0,45,20) == 1);
    //TC3 magnitudInRange input highLimit 
    assert(magnitudInRange(0,45,45) == 0);
    
    //TC4 batteryIsOk Temperature out of range
    assert(batteryIsOk(50,40,0.5)== NOT_OK);
    //TC5 batteryIsOk SOC out of range
    assert(batteryIsOk(20,100,0.5)== NOT_OK);
    //TC6 batteryIsOk chargeRate out of range
    assert(batteryIsOk(20,40,1)== NOT_OK);
    //TC6 batteryIsOk all in range
    assert(batteryIsOk(20,40,0.5)== E_OK);
}
