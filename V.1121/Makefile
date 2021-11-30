BOOT=kernel.asm
KERNEL=kernel.c
ISOFILE=img/TrinityOS.iso
ISO_VOLUME_NAME=TrinityOS
LINKER=linker.ld
KERNEL_OUT=kernel/boot/TrinityOS.bin
ISO_OUT=img/TrinityOS.iso

all: build
build: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o
	grub-mkrescue -o img/TrinityOS.iso build/
build_debug: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o -ggdb
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o
run: build
	qemu-system-i386 -kernel ${KERNEL_OUT} -monitor stdio
run-iso: iso
	qemu-system-i386 -cdrom ${ISO_OUT} -monitor stdio
debug: build_debug
	qemu-system-i386 -kernel ${KERNEL_OUT} -s -S &
	gdb -x .gdbinit
iso: build
	mkdir -p build/iso/boot/grub
	cp kernel/boot/grub/grub.cfg build/iso/boot/grub
	cp ${KERNEL_OUT} build/iso/boot/grub
	grub-mkrescue -o ${ISO_OUT} build/iso
	rm -rf build/iso
clean:
	rm -rf build
