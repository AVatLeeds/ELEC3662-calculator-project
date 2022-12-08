#ifndef SYSCTL_H
#define SYSCTL_H

#include <stdint.h>

//#define DID0        0x000
//#define DID1        0x004
//#define PBORCTL     0x030
//#define RIS         0x050
//#define IMC         0x054
//#define MISC        0x058
//#define RESC        0x05C
//#define RCC         0x060
//#define GPIOHBCTL   0x06C
//#define RCC2        0x070
//#define MOSCCTL     0x07C
//#define DSLPCLKCFG  0x144
//#define SYSPROP     0x14C
//#define PIOSCCAL    0x150
//#define PIOSCSTAT   0x154
//#define PLLFREQ0    0x160
//#define PLLFREQ1    0x164
//#define PLLSTAT     0x168
//#define SLPPWRCFG   0x188
//#define DSLPPWRCFG  0x18C
//#define LDOSPCTL    0x1B4
//#define LDOSPCAL    0x1B8
//#define LDODPCTL    0x1BC
//#define LDODPCAL    0x1C0
//#define SDPMST      0x1CC
//#define PPWD        0x300
//#define PPTIMER     0x304
//#define PPGPIO      0x308
//#define PPDMA       0x30C
//#define PPHIB       0x314
//#define PPUART      0x318
//#define PPSSI       0x31C
//#define PPI2C       0x320
//#define PPUSB       0x328
//#define PPCAN       0x334
//#define PPADC       0x338
//#define PPACMP      0x33C
//#define PPPWM       0x340
//#define PPQEI       0x344
//#define PPEEPROM    0x358
//#define PPWTIMER    0x35C
//#define SRWD        0x500
//#define SRTIMER     0x504
//#define SRGPIO      0x508
//#define SRDMA       0x50C
//#define SRHIB       0x514
//#define SRUART      0x518
//#define SRSSI       0x51C
//#define SRI2C       0x520
//#define SRUSB       0x528
//#define SRCAN       0x534
//#define SRADC       0x538
//#define SRACMP      0x53C
//#define SRPWM       0x540
//#define SRQEI       0x544
//#define SREEPROM    0x558
//#define SRWTIMER    0x55C
//#define RCGCWD      0x600
//#define RCGCTIMER   0x604
//#define RCGCGPIO    0x608
//#define RCGCDMA     0x60C
//#define RCGCHIB     0x614
//#define RCGCUART    0x618
//#define RCGCSSI     0x61C
//#define RCGCI2C     0x620
//#define RCGCUSB     0x628
//#define RCGCCAN     0x634
//#define RCGCADC     0x638
//#define RCGCACMP    0x63C
//#define RCGCPWM     0x640
//#define RCGCQEI     0x644
//#define RCGCEEPROM  0x658
//#define RCGCWTIMER  0x65C
//#define SCGCWD      0x700
//#define SCGCTIMER   0x704
//#define SCGCGPIO    0x708
//#define SCGCDMA     0x70C
//#define SCGCHIB     0x714
//#define SCGCUART    0x718
//#define SCGCSSI     0x71C
//#define SCGCI2C     0x720
//#define SCGCUSB     0x728
//#define SCGCCAN     0x734
//#define SCGCADC     0x738
//#define SCGCACMP    0x73C
//#define SCGCPWM     0x740
//#define SCGCQEI     0x744
//#define SCGCEEPROM  0x758
//#define SCGCWTIMER  0x75C
//#define DCGCWD      0x800
//#define DCGCTIMER   0x804
//#define DCGCGPIO    0x808
//#define DCGCDMA     0x80C
//#define DCGCHIB     0x814
//#define DCGCUART    0x818
//#define DCGCSSI     0x81C
//#define DCGCI2C     0x820
//#define DCGCUSB     0x828
//#define DCGCCAN     0x834
//#define DCGCADC     0x838
//#define DCGCACMP    0x83C
//#define DCGCPWM     0x840
//#define DCGCQEI     0x844
//#define DCGCEEPROM  0x858
//#define DCGCWTIMER  0x85C
//#define PRWD        0xA00
//#define PRTIMER     0xA04
//#define PRGPIO      0xA08
//#define PRDMA       0xA0C
//#define PRHIB       0xA14
//#define PRUART      0xA18
//#define PRSSI       0xA1C
//#define PRI2C       0xA20
//#define PRUSB       0xA28
//#define PRCAN       0xA34
//#define PRADC       0xA38
//#define PRACMP      0xA3C
//#define PRPWM       0xA40
//#define PRQEI       0xA44
//#define PREEPROM    0xA58
//#define PRWTIMER    0xA5C

struct system_control
{
    volatile uint32_t       DID0;           //0x000
    volatile uint32_t       DID1;           //0x004
    volatile const uint32_t RESERVED0[10];
    volatile uint32_t       PBORCTL;        //0x030
    volatile const uint32_t RESERVED1[7];
    volatile uint32_t       RIS;            //0x050
    volatile uint32_t       IMC;            //0x054
    volatile uint32_t       MISC;           //0x058
    volatile uint32_t       RESC;           //0x05C
    volatile uint32_t       RCC;            //0x060
    volatile const uint32_t RESERVED3[2];
    volatile uint32_t       GPIOHBCTL;      //0x06C
    volatile uint32_t       RCC2;           //0x070
    volatile const uint32_t RESERVED4[2];
    volatile uint32_t       MOSCCTL;        //0x07C
    volatile const uint32_t RESERVED5[49];
    volatile uint32_t       DSLPCLKCFG;     //0x144
    volatile const uint32_t RESERVED6[1];
    volatile uint32_t       SYSPROP;        //0x14C
    volatile uint32_t       PIOSCCAL;       //0x150
    volatile uint32_t       PIOSCSTAT;      //0x154
    volatile const uint32_t RESERVED7[2];
    volatile uint32_t       PLLFREQ0;       //0x160
    volatile uint32_t       PLLFREQ1;       //0x164
    volatile uint32_t       PLLSTAT;        //0x168
    volatile const uint32_t RESERVED8[7];
    volatile uint32_t       SLPPWRCFG;      //0x188
    volatile uint32_t       DSLPPWRCFG;     //0x18C
    volatile const uint32_t RESERVED9[9];
    volatile uint32_t       LDOSPCTL;       //0x1B4
    volatile uint32_t       LDOSPCAL;       //0x1B8
    volatile uint32_t       LDODPCTL;       //0x1BC
    volatile uint32_t       LDODPCAL;       //0x1C0
    volatile const uint32_t RESERVED10[2];
    volatile uint32_t       SDPMST;         //0x1CC
    volatile const uint32_t RESERVED11[76];
    volatile uint32_t       PPWD;           //0x300
    volatile uint32_t       PPTIMER;        //0x304
    volatile uint32_t       PPGPIO;         //0x308
    volatile uint32_t       PPDMA;          //0x30C
    volatile const uint32_t RESERVED12[1];
    volatile uint32_t       PPHIB;          //0x314
    volatile uint32_t       PPUART;         //0x318
    volatile uint32_t       PPSSI;          //0x31C
    volatile uint32_t       PPI2C;          //0x320
    volatile const uint32_t RESERVED13[1];
    volatile uint32_t       PPUSB;          //0x328
    volatile const uint32_t RESERVED14[2];
    volatile uint32_t       PPCAN;          //0x334
    volatile uint32_t       PPADC;          //0x338
    volatile uint32_t       PPACMP;         //0x33C
    volatile uint32_t       PPPWM;          //0x340
    volatile uint32_t       PPQEI;          //0x344
    volatile const uint32_t RESERVED15[4];
    volatile uint32_t       PPEEPROM;       //0x358
    volatile uint32_t       PPWTIMER;       //0x35C
    volatile const uint32_t RESERVED16[104];
    volatile uint32_t       SRWD;           //0x500
    volatile uint32_t       SRTIMER;        //0x504
    volatile uint32_t       SRGPIO;         //0x508
    volatile uint32_t       SRDMA;          //0x50C
    volatile const uint32_t RESERVED17[1];
    volatile uint32_t       SRHIB;          //0x514
    volatile uint32_t       SRUART;         //0x518
    volatile uint32_t       SRSSI;          //0x51C
    volatile uint32_t       SRI2C;          //0x520
    volatile const uint32_t RESERVED18[1];
    volatile uint32_t       SRUSB;          //0x528
    volatile const uint32_t RESERVED19[2];
    volatile uint32_t       SRCAN;          //0x534
    volatile uint32_t       SRADC;          //0x538
    volatile uint32_t       SRACMP;         //0x53C
    volatile uint32_t       SRPWM;          //0x540
    volatile uint32_t       SRQEI;          //0x544
    volatile const uint32_t RESERVED20[4];
    volatile uint32_t       SREEPROM;       //0x558
    volatile uint32_t       SRWTIMER;       //0x55C
    volatile const uint32_t RESERVED21[40];
    volatile uint32_t       RCGCWD;         //0x600
    volatile uint32_t       RCGCTIMER;      //0x604
    volatile uint32_t       RCGCGPIO;       //0x608
    volatile uint32_t       RCGCDMA;        //0x60C
    volatile const uint32_t RESERVED22[1];
    volatile uint32_t       RCGCHIB;        //0x614
    volatile uint32_t       RCGCUART;       //0x618
    volatile uint32_t       RCGCSSI;        //0x61C
    volatile uint32_t       RCGCI2C;        //0x620
    volatile const uint32_t RESERVED23[1];
    volatile uint32_t       RCGCUSB;        //0x628
    volatile const uint32_t RESERVED24[2];
    volatile uint32_t       RCGCCAN;        //0x634
    volatile uint32_t       RCGCADC;        //0x638
    volatile uint32_t       RCGCACMP;       //0x63C
    volatile uint32_t       RCGCPWM;        //0x640
    volatile uint32_t       RCGCQEI;        //0x644
    volatile const uint32_t RESERVED25[4];
    volatile uint32_t       RCGCEEPROM;     //0x658
    volatile uint32_t       RCGCWTIMER;     //0x65C
    volatile const uint32_t RESERVED26[40];
    volatile uint32_t       SCGCWD;         //0x700
    volatile uint32_t       SCGCTIMER;      //0x704
    volatile uint32_t       SCGCGPIO;       //0x708
    volatile uint32_t       SCGCDMA;        //0x70C
    volatile const uint32_t RESERVED27[1];
    volatile uint32_t       SCGCHIB;        //0x714
    volatile uint32_t       SCGCUART;       //0x718
    volatile uint32_t       SCGCSSI;        //0x71C
    volatile uint32_t       SCGCI2C;        //0x720
    volatile const uint32_t RESERVED28[1];
    volatile uint32_t       SCGCUSB;        //0x728
    volatile const uint32_t RESERVED29[2];  
    volatile uint32_t       SCGCCAN;        //0x734
    volatile uint32_t       SCGCADC;        //0x738
    volatile uint32_t       SCGCACMP;       //0x73C
    volatile uint32_t       SCGCPWM;        //0x740
    volatile uint32_t       SCGCQEI;        //0x744
    volatile const uint32_t RESERVED30[4];
    volatile uint32_t       SCGCEEPROM;     //0x758
    volatile uint32_t       SCGCWTIMER;     //0x75C
    volatile const uint32_t RESERVED31[40];
    volatile uint32_t       DCGCWD;         //0x800
    volatile uint32_t       DCGCTIMER;      //0x804
    volatile uint32_t       DCGCGPIO;       //0x808
    volatile uint32_t       DCGCDMA;        //0x80C
    volatile const uint32_t RESERVED32[1];
    volatile uint32_t       DCGCHIB;        //0x814
    volatile uint32_t       DCGCUART;       //0x818
    volatile uint32_t       DCGCSSI;        //0x81C
    volatile uint32_t       DCGCI2C;        //0x820
    volatile const uint32_t RESERVED33[1];
    volatile uint32_t       DCGCUSB;        //0x828
    volatile const uint32_t RESERVED34[2];
    volatile uint32_t       DCGCCAN;        //0x834
    volatile uint32_t       DCGCADC;        //0x838
    volatile uint32_t       DCGCACMP;       //0x83C
    volatile uint32_t       DCGCPWM;        //0x840
    volatile uint32_t       DCGCQEI;        //0x844
    volatile const uint32_t RESERVED35[4];
    volatile uint32_t       DCGCEEPROM;     //0x858
    volatile uint32_t       DCGCWTIMER;     //0x85C
    volatile const uint32_t RESERVED36[104];
    volatile uint32_t       PRWD;           //0xA00
    volatile uint32_t       PRTIMER;        //0xA04
    volatile uint32_t       PRGPIO;         //0xA08
    volatile uint32_t       PRDMA;          //0xA0C
    volatile const uint32_t RESERVED37[1];
    volatile uint32_t       PRHIB;          //0xA14
    volatile uint32_t       PRUART;         //0xA18
    volatile uint32_t       PRSSI;          //0xA1C
    volatile uint32_t       PRI2C;          //0xA20
    volatile const uint32_t RESERVED38[1];
    volatile uint32_t       PRUSB;          //0xA28
    volatile const uint32_t RESERVED39[2];
    volatile uint32_t       PRCAN;          //0xA34
    volatile uint32_t       PRADC;          //0xA38
    volatile uint32_t       PRACMP;         //0xA3C
    volatile uint32_t       PRPWM;          //0xA40
    volatile uint32_t       PRQEI;          //0xA44
    volatile const uint32_t RESERVED40[4];
    volatile uint32_t       PREEPROM;       //0xA58
    volatile uint32_t       PRWTIMER;       //0xA5C
};

#define SYSCTL_BASE     0x400FE000

#define SYSCTL          ((struct system_control *)SYSCTL_BASE)

#endif