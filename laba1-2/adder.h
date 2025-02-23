//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

SC_MODULE(add_sub) {
	// input
	sc_in<sc_uint<16> > ain, bin;
	// carry in, boolean to tell that it should be add or subtract
	sc_in<bool> ci, as;
	// output
	sc_out<sc_uint<16> > sum;
	// carry out
	sc_out<bool> co;
	// flag
	sc_out<bool> zflag, oflag, lflag;

	//sum in each part
	sc_uint<16> sum_s, sum_f;

	// 1-bit ripple carry fulladder, note the cof reference bool&
	bool fulladder(bool a, bool b, bool cif, bool& cof) {
		bool sumr;
		sumr = (a ^ b) ^ cif;
		cof = (a & b) | ((a ^ b) & cif);
		return sumr;
	}


	void p1() {
		// init flag
		oflag.write(0);
		zflag.write(0);
		/*
			sum = A+inv(B)+ 1
		*/
		//inverse(b)
		sc_uint<16> inb = bin.read();
		/*
			b = b xor as
			if(as==1)
				b = b xor 1 get reverse
			else
				b = b xor 0 get the same value
		*/
		for (int i = 0; i < 16; i++) {
			inb[i] = inb[i] ^ as;
		}
		//A+inv(B)
		bool temp0 = false;
		bool temp1 = ci.read();
		for (int i = 0; i < 16; i++) {
			temp0 = temp1;
			sum_s[i] = fulladder(ain.read()[i], inb[i], temp0, temp1);
		}

		bool tempi0 = false;
		bool tempi1 = false;
		// (A+inv(B))+1
		sc_uint<16> one;
		one[0] = as;
		for (int i = 0; i < 16; i++) {
			tempi0 = tempi1;
			sum_f[i] = fulladder(sum_s[i], one[i], tempi0, tempi1);
		}

		// write out
		sum.write(sum_f);
		co.write(temp1);

		//check flag
		oflag.write(temp1);
		zflag.write(!(sum_f[0] || sum_f[1] || sum_f[2] || sum_f[3] || sum_f[4] || sum_f[5] || sum_f[6] || sum_f[7] || sum_f[8] || sum_f[9] || sum_f[10] || sum_f[11] || sum_f[12] || sum_f[13] || sum_f[14] || sum_f[15]));
		lflag.write(!temp1);
	}

	SC_CTOR(add_sub) {
		SC_METHOD(p1);
		sensitive << ain << bin << ci << as;
	}
};
#endif