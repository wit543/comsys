//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

SC_MODULE(adder) {
	sc_in<sc_uint<4> > ain, bin;
	sc_in<bool> ci;
	sc_out<sc_uint<4> > sum;
	sc_out<bool> co;
	sc_out<bool> zflag, oflag;
	bool co0, co1, co2, co3;
	sc_uint<4> sum_s;

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
		sum_s[0] = fulladder(ain.read()[0], bin.read()[0], ci.read(), co0);
		sum_s[1] = fulladder(ain.read()[1], bin.read()[1], co0, co1);
		sum_s[2] = fulladder(ain.read()[2], bin.read()[2], co1, co2);
		sum_s[3] = fulladder(ain.read()[3], bin.read()[3], co2, co3);

		sum.write(sum_s);
		co.write(co3);
		if (co3)
			oflag.write(1);
		if (sum_s[0]==0&& sum_s[1]==0&& sum_s[2]==0&& sum_s[3]==0)
			zflag.write(1);
	}

	SC_CTOR(adder) {
		SC_METHOD(p1);
		sensitive << ain << bin << ci;
	}
};

SC_MODULE(add_sub) {
	sc_in<sc_uint<4> > ain, bin;
	sc_in<bool> ci,as;
	sc_out<sc_uint<4> > sum;
	sc_out<bool> co;
	sc_out<bool> zflag, oflag;
	bool co0, co1, co2, co3;
	bool coi0, coi1, coi2, coi3;
	sc_uint<4> sum_s;

	// 1-bit ripple carry fulladder, note the cof reference bool&
	bool fulladder(bool a, bool b, bool cif, bool& cof) {
		bool sumr;
		sumr = (a ^ b) ^ cif;
		cof = (a & b) | ((a ^ b) & cif);
		return sumr;
	}
	sc_uint<4> xor(sc_in<sc_uint<4>> in) {
		sc_uint<4> out;
		out[0]=in.read()[0]^1;
		out[1]=in.read()[1]^1;
		out[2]=in.read()[2]^1;
		out[3]=in.read()[3]^1;
		return out;
	}
	void sub() {
		sc_uint<4> inverted = xor (bin);
		sc_uint<4> one;
		one[3] = 1;
		bool coj0, coj1, coj2, coj3;
		sum_s[0] = fulladder(inverted[0], one[0], false, coj0);
		sum_s[1] = fulladder(inverted[1], one[1], coj0, coj1);
		sum_s[2] = fulladder(inverted[2], one[2], coj1, coj2);
		sum_s[3] = fulladder(inverted[3], one[3], coj2, coj3);


		sum_s[0] = fulladder(inverted[0], sum_s[0], ci.read(), coi0);
		sum_s[1] = fulladder(inverted[1], sum_s[1], coi0, coi1);
		sum_s[2] = fulladder(inverted[2], sum_s[2], coi1, coi2);
		sum_s[3] = fulladder(inverted[3], sum_s[3], coi2, coi3);

		sum.write(sum_s);
		co.write(coi3);
	}
	void add() {
		sum_s[0] = fulladder(ain.read()[0], bin.read()[0], ci.read(), co0);
		sum_s[1] = fulladder(ain.read()[1], bin.read()[1], co0, co1);
		sum_s[2] = fulladder(ain.read()[2], bin.read()[2], co1, co2);
		sum_s[3] = fulladder(ain.read()[3], bin.read()[3], co2, co3);

		sum.write(sum_s);
		co.write(co3);
		if (co3)
			oflag.write(1);
		if (sum_s[0] == 0 && sum_s[1] == 0 && sum_s[2] == 0 && sum_s[3] == 0)
			zflag.write(1);
	}
	void p1() {
		oflag.write(0);
		zflag.write(0);
		if (as) {
			sub();
		}
		else {
			add();
		}
	}

	SC_CTOR(add_sub) {
		SC_METHOD(p1);
		sensitive << ain << bin << ci;
	}
};
#endif


