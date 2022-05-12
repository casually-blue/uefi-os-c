all: boot/kernel.efi

QEMU_ARGS=-smp 4 \
					-m 4G \
          -enable-kvm \
          -drive id=disk0,file=fat:rw:.,format=raw \
          -drive "if=pflash,format=raw,readonly=on,file=../qemu/OVMF_CODE.fd" \
  				-drive "if=pflash,format=raw,file=../qemu/OVMF_VARS.fd"

OBJS=\
		 obj/main.o \
		 obj/idt.o \

boot/kernel.efi: $(OBJS)
	@echo "Link $@"
	@clang -g -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -fuse-ld=lld-link $(OBJS) -o boot/kernel.efi

obj:
	@mkdir -p obj

obj/%.o: src/%.c obj
	@echo "Compiling $@ ($<)"
	@clang -g -Iinclude/efi -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone -c $< -o $@

clean:
	rm -rf obj
	rm -f boot/kernel.efi

run: boot/kernel.efi
	cd boot && qemu-system-x86_64 $(QEMU_ARGS) 2>../qemu/qemu.log

debug: boot/kernel.efi
	cd boot && qemu-system-x86_64 $(QEMU_ARGS) -S -s
         
