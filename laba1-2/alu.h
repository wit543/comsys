#ifndef ALU
#define ALU

#include <systemc.h>
#include "adder.h"

SC_MODULE(alu) {
	sc_in<sc_uint<16> > ain, bin;
	sc_signal<bool> ci, as;
	sc_in<sc_uint<4>> control;
	sc_out<sc_uint<16> > sum;
	sc_out<bool> zflag, oflag, lflag;
	sc_signal<bool> co;
	sc_signal<sc_uint<16>> sum_add, sum_sub;
	sc_uint<16> sum_xor, sum_or, sum_nota, sum_stl, sum_and;
	 

	void ADD() {
		add_sub DUT("add_sub");
		DUT.ain(ain);
		DUT.bin(bin);
		DUT.ci(ci);
		as.write(false);
		DUT.as(as);
		DUT.sum(sum_add);
		DUT.co(co);
		DUT.zflag(zflag);
		DUT.oflag(oflag);
		DUT.lflag(lflag);

	}

	void SUB() {
		add_sub adder("add_sub");
		adder.ain(ain);
		adder.bin(bin);
		adder.ci(ci);
		as.write(true);
		adder.as(as);
		adder.sum(sum_sub);
		adder.co(co);
		adder.zflag(zflag);
		adder.oflag(oflag);
		adder.lflag(lflag);
	}
	sc_uint<16> XOR(sc_uint<16> ain, sc_uint<16> bin) {
		return ain ^ bin;
	}

	void AND(/* arguments */) {
		/* code */
		sum_and = ain.read() & bin.read();
	}
	void OR(/* arguments */) {
		/* code */
		sum_or = ain.read() | bin.read();
	}
	void NOTA(/* arguments */) {
		/* code */
		sum_nota = ~ain.read();
	}
	void STL(/* arguments */) {
		/* code */
		add_sub adder("add_sub");
		adder.ain(ain);
		adder.bin(bin);
		adder.ci(ci);
		as.write(true);
		adder.as(as);
		adder.sum(sum_add);
		adder.co(co);
		adder.zflag(zflag);
		adder.oflag(oflag);
		adder.lflag(lflag);
		sum_stl[0] = oflag;

	}

	void run(/* arguments */) {
		ADD();
	}

	SC_CTOR(alu) {
		SC_METHOD(run);
		sensitive << ain << bin << ci << as;
	}



};

#endif