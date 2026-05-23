#include "Vdm_top.h"
#include "verilated.h"
#include "verilated_fst_c.h"

vluint64_t main_time = 0;

double sc_time_stamp() {
    return main_time;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    // Enable tracing
    Verilated::traceEverOn(true);

    Vdm_top* dut = new Vdm_top;

    VerilatedFstC* tfp = new VerilatedFstC;
    dut->trace(tfp, 99);
    tfp->open("wave.fst");

    // -------------------------
    // RESET
    // -------------------------
    dut->clk_i = 0;
    dut->rst_ni = 0;

    dut->eval();

    for (int i = 0; i < 5; i++) {
        dut->clk_i = !dut->clk_i;
        dut->eval();
        tfp->dump(main_time++);
    }

    dut->rst_ni = 1; // release reset

    // -------------------------
    // RUN CYCLES
    // -------------------------
    for (int i = 0; i < 50; i++) {
        dut->clk_i = 0;
        dut->eval();
        tfp->dump(main_time++);

        dut->clk_i = 1;
        dut->eval();
        tfp->dump(main_time++);
    }

    // -------------------------
    // FINISH
    // -------------------------
    tfp->close();
    delete dut;

    return 0;
}
