//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ADD_SUB_H
#define ADD_SUB_H

#include <systemc.h>

SC_MODULE(add_sub) {
	sc_in<sc_uint<4> > ain, bin;
	sc_in<bool> ci, as;
	sc_out<sc_uint<4> > sum;
	sc_out<bool> co;
	sc_out<bool> zflag, oflag, lflag;
	bool co0, co1, co2, co3;
	bool coi0, coi1, coi2, coi3;
	sc_uint<4> sum_s, sum_f;

	// 1-bit ripple carry fulladder, note the cof reference bool&
	bool fulladder(bool a, bool b, bool cif, bool& cof) {
		bool sumr;
		sumr = (a ^ b) ^ cif;
		cof = (a & b) | ((a ^ b) & cif);
		return sumr;
	}


	void p1() {
		oflag.write(0);
		zflag.write(0);
		sc_uint<4> inb = bin.read();
		inb[0] = inb[0] ^ as;
		inb[1] = inb[1] ^ as;
		inb[2] = inb[2] ^ as;
		inb[3] = inb[3] ^ as;
		sc_uint<4> one;
		one[0] = as;
		sum_s[0] = fulladder(ain.read()[0], inb[0], ci.read(), co0);
		sum_s[1] = fulladder(ain.read()[1], inb[1], co0, co1);
		sum_s[2] = fulladder(ain.read()[2], inb[2], co1, co2);
		sum_s[3] = fulladder(ain.read()[3], inb[3], co2, co3);


		sum_f[0] = fulladder(sum_s[0], one[0], false, coi0);
		sum_f[1] = fulladder(sum_s[1], one[1], coi0, coi1);
		sum_f[2] = fulladder(sum_s[2], one[2], coi1, coi2);
		sum_f[3] = fulladder(sum_s[3], one[3], coi2, coi3);

		sum.write(sum_f);
		co.write(co3);

		oflag.write(co3);
		zflag.write(!(sum_f[0] || sum_f[1] || sum_f[2] || sum_f[3]));
		lflag.write(!co3);
	}

	SC_CTOR(add_sub) {
		SC_METHOD(p1);
		sensitive << ain << bin << ci << as;
	}
};
#endif
