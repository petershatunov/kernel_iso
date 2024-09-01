
build:
	nasm -f elf64 kernel.asm -o kernel.o && \
	nasm -f elf64 header.asm -o header.o && \
	gcc -c hello.c -ffreestanding -o hello.o && \
	ld -T linker.ld -o iso/boot/kernel.bin header.o kernel.o hello.o && \
	grub2-mkrescue /usr/share/grub2/i386-pc -o iso/boot/kernel.iso iso
build-cc:
	nasm -f elf kernel.asm -o kernel.o && \
	nasm -f elf header.asm -o header.o && \
	~/opt/cross/bin/i686-elf-gcc -c hello.c -ffreestanding -o hello.o && \
	~/opt/cross/bin/i686-elf-ld -T linker.ld -o iso/boot/kernel.bin header.o kernel.o hello.o && \
	grub2-mkrescue /usr/share/grub2/i386-pc -o iso/boot/kernel.iso iso

clean:
	rm -f *.o ./iso/boot/*.bin ./iso/boot/*.iso
run:
	qemu-system-x86_64 -cdrom ./iso/boot/kernel.iso



build_:
	nasm -f elf64 kernel.asm -o kernel.o && \
	nasm -f elf64 header.asm -o header.o && \
	ld -T linker.ld -o iso/boot/kernel.bin header.o kernel.o && \
	grub2-mkrescue /usr/share/grub2/i386-pc -o iso/boot/kernel.iso iso
clean_:
	rm -f *.o ./iso/boot/*.bin ./iso/boot/*.iso