all:
	arm-none-eabi-g++ main.cpp -mfpu=fpv5-sp-d16 -mcpu=cortex-m7 -Os -fno-exceptions -fno-rtti -std=c++17 -T linker_script.ld -Wl,--gc-sections 
	arm-none-eabi-objcopy -O binary -S a.out a.bin
	arm-none-eabi-size a.out
	arm-none-eabi-objdump -S --disassemble a.out

clean:
	-rm -fR a.out a.bin

flash:
	st-flash write a.bin 0x8000000

bin:
	go run read.go
	