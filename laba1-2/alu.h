#ifndef ALU
#define ALU

#include <systemc.h>
#include "adder.h"

SC_MODULE(alu) {
	sc_in<sc_uint<16> > ain, bin;
	sc_signal<bool> ciS, asa,asb, coS;
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
			sum_and[i] = ain.read()[i] & bin.read()[i];
	}
	void OR(/* arguments */) {
		/* code */
		for (int i = 0; i < 16; i++)
			sum_or[i] = ain.read()[i] | bin.read()[i];
	}
	void NOTA(/* arguments */) {
		/* code */
		for (int i = 0; i < 16; i++)
			sum_nota[i] = ~ain.read()[i];
	}

	void run(/* arguments */) {
		AND();
		OR();
		NOTA();
		sum_xor =XOR(ain.read(),bin.read());
		sum_stl[0] = lflagB;
		if (control.read() == 0) {
			sum.write(sum_add);
			lflag.write(lflagA);
			oflag.write(oflagA);
			zflag.write(zflagA);
		}
		if (control.read() == 1) {
			sum.write(sum_sub);
			lflag.write(lflagB);
			oflag.write(oflagB);
			zflag.write(zflagB);
		}
		if (control.read() == 2) {
			sum.write(sum_xor);
		}
		if (control.read() == 3) {
			sum.write(sum_and);
		}
		if (control.read() == 4) {
			sum.write(sum_or);
		}
		if (control.read() == 5) {
			sum.write(sum_nota);
		}
		if (control.read() == 6) {
			sum.write(sum_stl);
			lflag.write(lflagB);
		}
	}

	SC_CTOR(alu): DUT("add") ,SUBB("sub"){

		DUT.ain(ain);
		DUT.bin(bin);
		DUT.ci(ciA);
		asa.write(false);
		DUT.as(asa);
		DUT.sum(sum_add);
		DUT.co(coA);
		DUT.zflag(zflagA);
		DUT.lflag(lflagA);
		DUT.oflag(oflagA);


		SUBB.ain(ain);
		SUBB.bin(bin);
		SUBB.ci(ciS);
		asb.write(true);
		SUBB.as(asb);
		SUBB.sum(sum_sub);
		SUBB.co(coS);
		SUBB.zflag(zflagB);
		SUBB.oflag(oflagB);
		SUBB.lflag(lflagB);
		SC_METHOD(run);
		sensitive << control;
	}



};

#endif