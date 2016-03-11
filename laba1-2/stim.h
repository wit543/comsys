//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>

SC_MODULE(stim) {
	sc_in<bool> clk;
	sc_out<sc_uint<16> > ain, bin;
	sc_out<bool> ci, as;

	void ps1() {

	}

	SC_CTOR(stim) {
		SC_THREAD(ps1);                     // Run ps1 only ones
		sensitive << clk.pos();
	}
};
#endif