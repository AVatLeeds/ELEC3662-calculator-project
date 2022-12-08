#include <stdint.h>
#include "status.h"

status_LED status;

int main(void)
{   
    status = WHITE;
    while(1);
}

void hard_fault()
{
    status = RED;
    while (1);
}

void usage_fault()
{
    status = MAGENTA;
    while (1);
}

void bus_fault()
{
    status = YELLOW;
    while (1);
}