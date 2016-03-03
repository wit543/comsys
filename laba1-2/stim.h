#ifndef STIM_H
#define STIM_H

#include <systemc.h>

SC_MODULE(stim) {
	sc_in<bool> clk;
	sc_out<sc_uint<16> > ain, bin;
	sc_out<bool> ci, as;

	void ps1() {

		ain.write("0b0000000000000000");
		bin.write("0b0000000000000000");
		as.write(true);
		ci.write(false);
		wait();

		// ain.write("0b0001");
		// bin.write("0b0101");
		// as.write(false);
		// ci.write(false);
		// wait();
		//
		// ain.write("0b0001");
		// bin.write("0b0101");
		// as.write(true);
		// ci.write(false);
		// wait();
		//
		// ain.write("0b0100");
		// bin.write("0b0001");
		// as.write(false);
		// ci.write(false);
		// wait();
		//
		// ain.write("0b0100");
		// bin.write("0b0001");
		// as.write(true);
		// ci.write(false);
		// wait();
		//
		// ain.write("0b0001");
		// bin.write("0b0001");
		// as.write(false);
		// ci.write(false);
		// wait();
		//
		// ain.write("0b0001");
		// bin.write("0b0001");
		// as.write(true);
		// ci.write(false);
		// wait();

		sc_stop();                          // End simulation
	}

	SC_CTOR(stim) {
		SC_THREAD(ps1);                     // Run ps1 only ones
		sensitive << clk.pos();
	}
};

#endif