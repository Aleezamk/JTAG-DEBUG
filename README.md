# JTAG-DEBUG

## 1. Verilating and Simulating CV32E40P Core using Verilator

## Overview

The goal of this task was to successfully verilate and simulate the `CV32E40P` RISC-V core using Verilator.
The process included:
- Preparing the RTL source list
- Resolving Verilator compilation issues
- Writing a C++ testbench
- Viewing simulation results in GTKWave

## Work

The work started by targeting the top-level module `cv32e40p_top`. A `filelist.f` approach was used for compilation instead of manually listing RTL files in the command. The filelist contained:

- RTL source files
- package files
- vendor/common-cell dependencies
- behavioral models
  
Several issues were encountered and corrected to make it verilator compatible and filelist is made containing only the required files for verilator-based simulation.

### RTL Modifications

During Verilator compilation of the CV32E40P core, multiple errors were encountered related to mixed assignment styles inside generate blocks and unsupported RTL patterns. These were fixed to ensure successful simulation.

For example, all conflicting signals were unified to **sequential logic (`always_ff`) only**, and `assign` statements were removed or replaced with reset logic in `rtl/cv32e40p_cs_registers.sv`.

The command used to verilate is:
```bash
 verilator --cc --exe --build --sv --trace-fst -Wno-fatal --Wno-PINMISSING -DFPU=0 -DZFINX=0 --top-module cv32e40p_top -Irtl/include -Irtl/vendor/pulp_platform_common_cells/src -Irtl/vendor/pulp_platform_common_cells/include -Irtl/vendor/pulp_platform_common_cells/include/common_cells -Ibhv -f filelist.f tb.cpp
```
![alt text](docs/verilate_core_comp.png)

Then run this command:
```bash
./obj_dir/Vcv32e40p_top
gtkwave wave.fst
```
![alt text](docs/gtkwave_core.png)

So, the core cv32e40p is successfully compiled and simulated on verilator and waveforms can be analyzed in gtkwave

## 2. QEMU + GDB Debugging Workflow (RISC-V Bare Metal)
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
