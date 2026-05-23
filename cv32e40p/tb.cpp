#include "Vcv32e40p_top.h"
#include "verilated.h"
#include "verilated_fst_c.h"

vluint64_t sim_time = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vcv32e40p_top *top = new Vcv32e40p_top;

    // Enable waveform tracing
    Verilated::traceEverOn(true);

    VerilatedFstC *tfp = new VerilatedFstC;
    top->trace(tfp, 5);
    tfp->open("wave.fst");

    // Initial values
    top->clk_i = 0;
    top->rst_ni = 0;

    // Required inputs
    top->fetch_enable_i = 1;
    top->pulp_clock_en_i = 1;
    top->scan_cg_en_i = 0;

    top->boot_addr_i = 0x00000000;
    top->mtvec_addr_i = 0x00000000;
    top->dm_halt_addr_i = 0x1A110800;
    top->dm_exception_addr_i = 0x1A110808;
    top->hart_id_i = 0;

    top->instr_gnt_i = 1;
    top->instr_rvalid_i = 1;
    top->instr_rdata_i = 0x00000013; // NOP

    top->data_gnt_i = 1;
    top->data_rvalid_i = 1;
    top->data_rdata_i = 0;

    top->irq_i = 0;
    top->debug_req_i = 0;

    // Reset cycles
    for (int i = 0; i < 10; i++) {
        top->clk_i ^= 1;
        top->eval();
        tfp->dump(sim_time++);
    }

    top->rst_ni = 1;

    // Run simulation
    for (int i = 0; i < 200; i++) {
        top->clk_i ^= 1;
        top->eval();
        tfp->dump(sim_time++);
    }

    tfp->close();

    delete top;
    delete tfp;

    return 0;
}
