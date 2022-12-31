/* Load Memory Address (LMA) is the origin location where the data will be loaded onto the machine.             */
/* Virtual Memory Address (VMA) is the origin location that all addresses will be resolved relative to.         */
/* This allows data to be relocated to the VMA once it has been loaded onto the machine.                        */
/* Within "SECTIONS" the locations for each section must be specified. If only one is specified it is the LMA,  */
/* otherwise it is specified as "> (LMA) AT > (VMA)"                                                            */

ENTRY(reset)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K 
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
    .text :
    {
        __text_start = .;
        TM4C123GXL_RTE.o(.vector_table)
        __init_array_start = .;
        *(.init_array)
        . = ALIGN(4);
        __init_array_end = .;
        *(.text)
        . = ALIGN(4);
        __text_end = .;
    } > FLASH

    .rodata :
    {
        *(.rodata)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        __data_start = .;
        *(.data)
        . = ALIGN(4);
        __data_end = .;
    } > SRAM AT > FLASH

    .bss :
    {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        __bss_end = .;
    } > SRAM AT > SRAM

    .heap (NOLOAD) :
    {
        __heap_start = .;
        TM4C123GXL_RTE.o(.heap)
        __heap_end = .;
    } > SRAM
    
}