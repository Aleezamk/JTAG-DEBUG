CC = riscv32-unknown-elf-gcc
OBJDUMP = riscv32-unknown-elf-objdump
OBJCOPY = riscv32-unknown-elf-objcopy
GDB = gdb-multiarch
QEMU = qemu-system-riscv32
SIZE = riscv32-unknown-elf-size

CFLAGS = -g -O0 -march=rv32imac -mabi=ilp32 -nostdlib -nostartfiles
LDFLAGS = -T linker.ld

SRC = start.s main.c
ELF = main.elf
HEX = main.hex
ASM = main.s

.PHONY: all qemu run gdb clean size

all: $(ELF) $(ASM) $(HEX)

$(ELF): $(SRC) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $@

$(ASM): $(ELF)
	$(OBJDUMP) -d -S -M no-aliases $< > $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

qemu: $(ELF)
	@echo "Ctrl-A C for QEMU console, then quit to exit"
	$(QEMU) -nographic -serial mon:stdio -machine virt -s -S -bios $(ELF)

run: $(ELF)
	@echo "Running QEMU (no gdb) — Ctrl-A C for console"
	$(QEMU) -nographic -serial mon:stdio -machine virt -bios $(ELF)

gdb: $(ELF)
	@echo "Ctrl-A C for QEMU console, then quit to exit"
	$(GDB) $(ELF) -q -ex "set arch riscv:rv32" -ex "target remote localhost:1234" -ex "load"

size: $(ELF)
	@if command -v $(SIZE) >/dev/null 2>&1; then $(SIZE) $(ELF); else echo "$(SIZE) not found"; fi

clean:
	rm -f $(ELF) $(ASM) $(HEX)
