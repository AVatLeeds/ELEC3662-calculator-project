#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

#define OFF     0
#define RED     1
#define GREEN   4
#define BLUE    2
#define MAGENTA 3
#define YELLOW  5
#define CYAN    6
#define WHITE   7

class status_LED
{
    public:
    status_LED(); // constructor sets up the pins that drive the tri-colour LED
    void set_status(uint8_t status);
    uint8_t get_status(void);
    uint8_t operator=(uint8_t status);

    private:
    uint8_t _status;
};

#endif