all: boot/kernel.efi

QEMU_ARGS=-smp 4 \
					-m 4G \
  				$(QEMU_FLAGS)\
          -drive id=disk0,file=fat:rw:.,format=raw \
          -drive "if=pflash,format=raw,readonly=on,file=../qemu/OVMF_CODE.fd" \
  				-drive "if=pflash,format=raw,file=../qemu/OVMF_VARS.fd"

SRC=$(wildcard src/**.c)
OBJS=$(patsubst src/%.c,obj/%.o, $(SRC))

CFLAGS=-g -Iinclude/efi -Iinclude

boot/kernel.efi: $(OBJS)
	@echo "Link $@"
	@clang -g -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_entry_main -Wl,-subsystem:efi_application -fuse-ld=lld-link $(OBJS) -o boot/kernel.efi

obj/%.o: src/%.c
	@echo "Compiling $@ ($<)"
	@clang $(CFLAGS) -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone -c $< -o $@

clean:
	rm -rf obj
	rm -f boot/kernel.efi
	mkdir obj

run: boot/kernel.efi
	cd boot && qemu-system-x86_64 $(QEMU_ARGS) 2>../qemu/qemu.log

debug: boot/kernel.efi
	cd boot && qemu-system-x86_64 $(QEMU_ARGS) -S -s
         
