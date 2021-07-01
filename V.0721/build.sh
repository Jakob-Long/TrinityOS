nasm -f elf32 kernel.asm -o OBJ/kasm.o
gcc -m32 -c kernel.c -o OBJ/kc.o
gcc -m32 -c test.cpp -o OBJ/cp.o
gcc -m32 -c Userland/userland.c -o OBJ/userland.o
ld -m elf_i386 -T link.ld -o kernel/boot/kernel.bin OBJ/kasm.o OBJ/kc.o OBJ/cp.o OBJ/userland.o
grub-file --is-x86-multiboot kernel/boot/kernel.bin
grub-mkrescue -o img/TrinityOS.iso kernel/
#qemu-system-i386 -kernel kernel/boot/kernel.bin
