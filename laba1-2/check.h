//------------------------------------------------------------------
// 4-bits adder checker module
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;

SC_MODULE(check) {
	sc_in<bool> clk;
	sc_in<sc_uint<16> > ain, bin;
	sc_in<bool> ci, as;
	sc_in<sc_uint<32> > sum;
	sc_in<bool> co;
	sc_in<bool> zflag, oflag, lflag;

	sc_uint<5> sumc;

	void pc1() {
	}

	SC_CTOR(check) {
		SC_METHOD(pc1);
		sensitive << clk.pos();
		dont_initialize();
	}
};
#endif