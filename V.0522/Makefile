BOOT=kernel.asm
KERNEL=kernel.c
MODULE=module/module.c
ISOFILE=img/TrinityOS.iso
ISO_VOLUME_NAME=TrinityOS
LINKER=linker.ld
KERNEL_OUT=kernel/boot/TrinityOS.bin
ISO_OUT=img/TrinityOS.iso

files=build/kernel.o build/boot.o build/ModuleList.o build/strcopy.o build/module.o

all: build

build: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	gcc -w -fcompare-debug-second -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o
	gcc -w -fcompare-debug-second -m32 -ffreestanding -c kernel/ModuleList.c -o build/ModuleList.o
	gcc -w -fcompare-debug-second -m32 -ffreestanding -c lib/LibC/strcopy.c -o build/strcopy.o
	gcc -w -fcompare-debug-second -m32 -ffreestanding -c ${MODULE} -o build/module.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} $(files)
	grub-file --is-x86-multiboot kernel/boot/kernel.bin
	grub-mkrescue -o img/TrinityOS.iso build/

#build_debug: clean
#	mkdir -p build
#	nasm -f elf32 ${BOOT} -o build/boot.o
#	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o -ggdb
#	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o

run: build
	qemu-system-i386 -kernel ${KERNEL_OUT} -monitor stdio

#run-iso: iso
#	qemu-system-i386 -cdrom ${ISO_OUT} -monitor stdio

debug: build_debug
	qemu-system-i386 -kernel ${KERNEL_OUT} -s -S &
	gdb -x .gdbinit

iso: build
#	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} $(files)
#	grub-file --is-x86-multiboot kernel/boot/kernel.bin
	grub-mkrescue -o img/TrinityOS.iso kernel/
	qemu-system-i386 -boot d -cdrom img/TrinityOS.iso -m 512

clean:
	rm -rf build
