#include <stdint.h>
#include <sys/types.h>
#include "SYSCTL.h"
#include "SYSTICK.h"

#define _GNU_SOURCE
#define STACK_TOP   0x20008000
#define F_CPU       80000000

extern uint8_t __text_start;
extern uint8_t __text_end;
extern uint8_t __data_start;
extern uint8_t __data_end;
extern uint8_t __bss_start;
extern uint8_t __bss_end;

extern void (* __init_array_start)();
extern void (* __init_array_end)();

extern char __heap_start;
extern char __heap_end;

#define HEAP_SIZE 0x00000040
static uint8_t __attribute__((section(".heap"))) heap[HEAP_SIZE];

extern int main();

void default_handler()
{
    while (1);
}

// Processor interrupt service routines
void reset();
void __attribute__((weak, alias("default_handler"))) NMI();
void __attribute__((weak, alias("default_handler"))) hard_fault();
void __attribute__((weak, alias("default_handler"))) memory_management();
void __attribute__((weak, alias("default_handler"))) bus_fault();
void __attribute__((weak, alias("default_handler"))) usage_fault();
void __attribute__((weak, alias("default_handler"))) SV_call();
void __attribute__((weak, alias("default_handler"))) debug_monitor();
void __attribute__((weak, alias("default_handler"))) pend_SV();
void __attribute__((weak, alias("default_handler"))) sys_tick();

// Peripheral interrupt service routines
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_A();
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_B();
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_C();
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_D();
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_E();
void __attribute__((weak, alias("default_handler"))) _ISR_GPIO_port_F();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_0();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_1();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_2();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_3();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_4();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_5();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_6();
void __attribute__((weak, alias("default_handler"))) _ISR_UART_7();
void __attribute__((weak, alias("default_handler"))) _ISR_SSI_0();
void __attribute__((weak, alias("default_handler"))) _ISR_SSI_1();
void __attribute__((weak, alias("default_handler"))) _ISR_SSI_2();
void __attribute__((weak, alias("default_handler"))) _ISR_SSI_3();
void __attribute__((weak, alias("default_handler"))) _ISR_I2C_0();
void __attribute__((weak, alias("default_handler"))) _ISR_I2C_1();
void __attribute__((weak, alias("default_handler"))) _ISR_I2C_2();
void __attribute__((weak, alias("default_handler"))) _ISR_I2C_3();
void __attribute__((weak, alias("default_handler"))) _ISR_CAN_0();
void __attribute__((weak, alias("default_handler"))) _ISR_CAN_1();
void __attribute__((weak, alias("default_handler"))) _ISR_USB();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM0_fault();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM0_generator_0();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM0_generator_1();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM0_generator_2();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM0_generator_3();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM1_fault();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM1_generator_0();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM1_generator_1();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM1_generator_2();
void __attribute__((weak, alias("default_handler"))) _ISR_PWM1_generator_3();
void __attribute__((weak, alias("default_handler"))) _ISR_QEI_0();
void __attribute__((weak, alias("default_handler"))) _ISR_QEI_1();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC0_sequence_0();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC0_sequence_1();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC0_sequence_2();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC0_sequence_3();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC1_sequence_0();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC1_sequence_1();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC1_sequence_2();
void __attribute__((weak, alias("default_handler"))) _ISR_ADC1_sequence_3();
void __attribute__((weak, alias("default_handler"))) _ISR_analogue_comparator_0();
void __attribute__((weak, alias("default_handler"))) _ISR_analogue_comparator_1();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_0A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_0B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_1A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_1B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_2A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_2B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_3A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_3B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_4A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_4B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_5A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer16_5B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_0A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_0B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_1A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_1B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_2A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_2B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_3A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_3B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_4A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_4B();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_5A();
void __attribute__((weak, alias("default_handler"))) _ISR_timer32_5B();
void __attribute__((weak, alias("default_handler"))) _ISR_flash_and_EEPROM_control();
void __attribute__((weak, alias("default_handler"))) _ISR_uDMA_software();
void __attribute__((weak, alias("default_handler"))) _ISR_uDMA_error();
void __attribute__((weak, alias("default_handler"))) _ISR_watchdog();
void __attribute__((weak, alias("default_handler"))) _ISR_hibernation_module();
void __attribute__((weak, alias("default_handler"))) _ISR_system_control();
void __attribute__((weak, alias("default_handler"))) _ISR_system_exception();


void __attribute__((section(".vector_table"))) (* vector_table[])() = {
    (void (*)())STACK_TOP,
    reset,
    NMI,
    hard_fault,
    memory_management,
    bus_fault,
    usage_fault,
    0,
    0,
    0,
    0,
    SV_call,
    debug_monitor,
    0,
    pend_SV,
    sys_tick,
    _ISR_GPIO_port_A,
    _ISR_GPIO_port_B,
    _ISR_GPIO_port_C,
    _ISR_GPIO_port_D,
    _ISR_GPIO_port_E,
    _ISR_UART_0,
    _ISR_UART_1,
    _ISR_SSI_0,
    _ISR_I2C_0,
    _ISR_PWM0_fault,
    _ISR_PWM0_generator_0,
    _ISR_PWM0_generator_1,
    _ISR_PWM0_generator_2,
    _ISR_QEI_0,
    _ISR_ADC0_sequence_0,
    _ISR_ADC0_sequence_1,
    _ISR_ADC0_sequence_2,
    _ISR_ADC0_sequence_3,
    _ISR_watchdog,
    _ISR_timer16_0A,
    _ISR_timer16_0B,
    _ISR_timer16_1A,
    _ISR_timer16_1B,
    _ISR_timer16_2A,
    _ISR_timer16_2B,
    _ISR_analogue_comparator_0,
    _ISR_analogue_comparator_1,
    0,
    _ISR_system_control,
    _ISR_flash_and_EEPROM_control,
    _ISR_GPIO_port_F,
    0,
    0,
    _ISR_UART_2,
    _ISR_SSI_1,
    _ISR_timer16_3A,
    _ISR_timer16_3B,
    _ISR_I2C_1,
    _ISR_QEI_1,
    _ISR_CAN_0,
    _ISR_CAN_1,
    0,
    0,
    _ISR_hibernation_module,
    _ISR_USB,
    _ISR_PWM0_generator_3,
    _ISR_uDMA_software,
    _ISR_uDMA_error,
    _ISR_ADC1_sequence_0,
    _ISR_ADC1_sequence_1,
    _ISR_ADC1_sequence_2,
    _ISR_ADC1_sequence_3,
    0,
    0,
    0,
    0,
    0,
    _ISR_SSI_2,
    _ISR_SSI_3,
    _ISR_UART_3,
    _ISR_UART_4,
    _ISR_UART_5,
    _ISR_UART_6,
    _ISR_UART_7,
    0,
    0,
    0,
    0,
    _ISR_I2C_2,
    _ISR_I2C_3,
    _ISR_timer16_4A,
    _ISR_timer16_4B,
    _ISR_timer16_5A,
    _ISR_timer16_5B,
    _ISR_timer32_0A,
    _ISR_timer32_0B,
    _ISR_timer32_1A,
    _ISR_timer32_1B,
    _ISR_timer32_2A,
    _ISR_timer32_2B,
    _ISR_timer32_3A,
    _ISR_timer32_3B,
    _ISR_timer32_4A,
    _ISR_timer32_4B,
    _ISR_timer32_5A,
    _ISR_timer32_5B,
    _ISR_system_exception,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    _ISR_PWM1_generator_0,
    _ISR_PWM1_generator_1,
    _ISR_PWM1_generator_2,
    _ISR_PWM1_generator_3,
    _ISR_PWM1_fault
};

caddr_t _sbrk(int incr)
{
    static char *head;
    char *prev_head;
    
    if (head == 0) head = &__heap_start;

    prev_head = head;

    if ((head + incr) > (char*)&__heap_end)
    {
        return ((void*)-1); // error - no more memory
    }

    head += incr;

    return (caddr_t)prev_head;
}

void clock_setup()
{
    SYSCTL->RCC2 |= (0x1 << 31) | (0x1 << 30); // set USERCC2 and DIV400
    SYSCTL->RCC2 &= ~(0x7F << 22); // clear SYSDIV2 and SYSDIV2LSB
    SYSCTL->RCC2 |= (0x4 << 22); // set the new SYSDIV2 value for an 80 MHz system clock
    SYSCTL->RCC2 &= ~(0x1 << 13); // clear PWRDN2 to set the PLL running
    while (!SYSCTL->PLLSTAT); // do nothing till the PLL is locked
    SYSCTL->RCC2 &= ~(0x1 << 11); // clear the BYPASS2 bit so that the system clock is now derrived from the PLL
}

void reset()
{
    // populate SRAM with data and bss
    uint8_t * src, * dest;

    src = &__text_end;
    for (dest = &__data_start; dest < &__data_end;)
    {
        *dest++ = *src++;
    }

    for (dest = &__bss_start; dest < &__bss_end;)
    {
        *dest++ = 0;
    }

    clock_setup();

    // SYSTICK setup
    STRELOAD = 0x0;
    STCURRENT = 0x0;
    STCTRL = 0x4; // enable systick and set clock source to system clock

        // run constructors
    void (** constructor_ptr)();
    for (constructor_ptr = &__init_array_start; constructor_ptr < &__init_array_end;)
    {
        (*constructor_ptr++)();
    }

    main();
}