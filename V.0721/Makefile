files = OBJ/kasm.o OBJ/kc.o OBJ/userland.o OBJ/sleep.o OBJ/add.o

output: $(files)
	ld -m elf_i386 -T link.ld -o kernel/boot/kernel.bin $(files)
	grub-file --is-x86-multiboot kernel/boot/kernel.bin
	grub-mkrescue -o img/TrinityOS.iso kernel/
	qemu-system-i386 -kernel kernel/boot/kernel.bin

header:
	gcc -m32 -c kernel.c -o OBJ/kc.o


clean:
	rm OBJ/*.o

OBJ/kasm.o: kernel.asm kernel.c
	nasm -f elf32 kernel.asm -o OBJ/kasm.o

OBJ/kc.o: kernel.c
	gcc -m32 -c kernel.c -o OBJ/kc.o
	
OBJ/cp.o: test.cpp
	gcc -m32 -c test.cpp -o OBJ/cp.o

OBJ/userland.o: Userland/userland.c
	gcc -m32 -c Userland/userland.c -o OBJ/userland.o

OBJ/sleep.o: Lib/LibC/sleep.c
	gcc -m32 -c Lib/LibC/sleep.c -o OBJ/sleep.o

OBJ/add.o: Lib/LibTest/Scripts/add.c
	gcc -m32 -c Lib/LibTest/Scripts/add.c -o OBJ/add.o

OBJ/print.o: Lib/LibC/print.c
	gcc -m32 -c Lib/LibC/print.c -o OBJ/print.o