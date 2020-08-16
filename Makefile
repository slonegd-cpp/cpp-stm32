all:
	arm-none-eabi-g++ main.cpp -mcpu=cortex-m7 -Os -fno-exceptions -T linker_script.ld -Wl,--gc-sections
	arm-none-eabi-objcopy -O binary a.out a.bin
	arm-none-eabi-size a.out
	arm-none-eabi-objdump --disassemble a.out

clean:
	-rm -fR a.out a.bin

flash:
	st-flash write a.bin 0x8000000

bin:
	od -t x4 a.bin
	