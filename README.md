# JTAG-DEBUG
# 1. QEMU + GDB Debugging Workflow (RISC-V Bare Metal)
## Overview
This setup demonstrates running a simple RISC-V bare-metal program on QEMU and debugging it using GDB in a step-by-step execution mode. The goal is to observe program execution and register state changes at runtime.
## Prerequisites
RISC-V cross compiler toolchain (riscv64-unknown-elf-gcc)
QEMU with RISC-V support (qemu-system-riscv32)
GDB with RISC-V support (gdb-multiarch)

### Build Process

Compile the program:
```
make all
```

This generates `main.elf` → executable firmware image

### Run QEMU (Debug Mode)

Start QEMU in debug mode:
```
make qemu
```

![alt text](docs/qemu.png)

### Connect GDB

Open a new terminal and start GDB:
```
make gdb
```

Then run the program step-by-step by using **`s`** command and finally see the state of registers
```
info registers
```
![alt text](docs/gdb.png)
