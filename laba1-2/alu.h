#ifndef ALU
#define ALU

#include <systemc.h>
#include "adder.h"

SC_MODULE(alu) {
	sc_in<sc_uint<16> > ain, bin;
	sc_signal<bool> ciS, as, coS;
	sc_signal<bool> ciA, coA;
	sc_in<sc_uint<4>> control;
	sc_out<sc_uint<16> > sum;
	sc_out<bool> zflag, oflag, lflag;
	sc_signal<bool> zflagA, oflagA, lflagA;
	sc_signal<bool> zflagB, oflagB, lflagB;
	sc_signal<sc_uint<16>> sum_add, sum_sub;
	sc_uint<16> sum_xor, sum_or, sum_nota, sum_stl, sum_and;
	add_sub DUT,SUBB;

	sc_uint<16> XOR(sc_uint<16> ain, sc_uint<16> bin) {
		return ain ^ bin;
	}

	void AND(/* arguments */) {
		/* code */
		for (int i = 0; i < 16;i++)
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

	void run(/* arguments */) {
		
	}

	SC_CTOR(alu): DUT("add") ,SUBB("sub"){

		DUT.ain(ain);
		DUT.bin(bin);
		DUT.ci(ciA);
		as.write(false);
		DUT.as(as);
		DUT.sum(sum_add);
		DUT.co(coA);
		DUT.zflag(zflagA);
		DUT.lflag(lflagA);
		DUT.oflag(oflagA);

		SUBB.ain(ain);
		SUBB.bin(bin);
		SUBB.ci(ciS);
		as.write(true);
		SUBB.as(as);
		SUBB.sum(sum_sub);
		SUBB.co(coS);
		SUBB.zflag(zflagB);
		SUBB.oflag(oflagB);
		SUBB.lflag(lflagB);
		SC_METHOD(run);
		sensitive << ain << bin << ciA << as << control;
	}



};

#endif