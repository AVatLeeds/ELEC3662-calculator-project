CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++

CFLAGS =	-g\
			-O0\
			-Wall\
			-mthumb\
			-mno-thumb-interwork\
			-mcpu=cortex-m4\
			-mfloat-abi=hard\
			-nostartfiles\
			-fno-rtti\
			-fsingle-precision-constant\
			-fno-exceptions

LD = arm-none-eabi-ld

LDFLAGS =	-nostdlib\
			-nostartfiles\
			-Map=firmware.map\
			-T TM4C123GXL_startup.ld

SOURCES = 

TARGET = main.cpp

firmware.bin: firmware.o
	arm-none-eabi-objcopy -O binary $^ $@

firmware.o: TM4C123GXL_startup.o project.o
	$(LD) $(LDFLAGS) -o $@ $^

TM4C123GXL_startup.o: TM4C123GXL_startup.c

project.o: $(TARGET) $(SOURCES)
	$(CPP) $(CFLAGS) -I. -r -o $@ $^

clean:
	rm firmware.bin firmware.map firmware.o project.o