CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++

CFLAGS =	-g0\
			-O1\
			-Wall\
			-mthumb\
			-mno-thumb-interwork\
			-mcpu=cortex-m4\
			-mfloat-abi=soft\
			-nostartfiles\
			-fno-rtti\
			-fno-exceptions\
			-specs=nano.specs\
			-static\

LD = arm-none-eabi-ld

LDFLAGS =	-nostdlib\
			-nostartfiles\
			-Map=firmware.map\
			-T TM4C123GXL_RTE.ld

SOURCES =	status.cpp\
			keypad.cpp\
			LCD_driver.cpp\
			calculator.cpp\
			recursive_descent.cpp\

TARGET = main.cpp

firmware.bin: firmware.o
	arm-none-eabi-objcopy -O binary $^ $@

firmware.o: TM4C123GXL_RTE.o project.o
	$(LD) $(LDFLAGS) -o $@ $^

TM4C123GXL_RTE.o: TM4C123GXL_RTE.c

project.o: $(TARGET) $(SOURCES)
	$(CPP) $(CFLAGS) -r -o $@ $^

clean:
	rm firmware.bin firmware.map *.o

flash:
	lm4flash -v -S 0x00000000 firmware.bin

debug:
	lm4flash -v -S 0x00000000 firmware.bin
	openocd -f /usr/share/openocd/scripts/interface/ti-icdi.cfg -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg