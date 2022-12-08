#include <bits/stdint-uintn.h>
#include <stdint.h>
#include "SYSCTL.h"
#include "GPIO.h"
#include "status.h"

status_LED::status_LED()
{
    // on the EK-TM4C123GKL Launchpad development board the tri-colour LED is connected to pins 1, 2 and 3 of port F
    // Port F must be enabled and these pins set as outputs
    SYSCTL->RCGCGPIO |= (0x1 << 5); // enable the clock to port F
    PORTF->LOCK = 0x4C4F434B; // unlock the commit register for port F
    PORTF->CR = 0x1F; // set the commit register bits for all 5 port F pins
    PORTF->DIR = 0x0E; // set LED pins to be outputs and the rest as inputs
    PORTF->DEN = 0x1F; // enable all port F pins
}

void status_LED::set_status(uint8_t status)
{
    _status = status & 0x7;
    PORTF->DATA &= ~(0x7 << 1);
    PORTF->DATA |= (_status << 1);
}

uint8_t status_LED::get_status(void)
{
    return _status;
}

uint8_t status_LED::operator=(uint8_t status)
{
    _status = status & 0x7;
    PORTF->DATA &= ~(0x7 << 1);
    PORTF->DATA |= (_status << 1);
    return _status;
}