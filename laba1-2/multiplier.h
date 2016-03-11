#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <systemc.h>
#include "alu.h"
SC_MODULE(multiplier) {
	// input
	sc_in<sc_uint<16> > ain, bin;
	/*
		signal to alu
		this:alu
		aa = ain
		mm = bin
		ss = sum
	*/
	sc_signal<sc_uint<16> > aa, mm, ss;
	// control the alu
	sc_signal<sc_uint<4> > control;
	// local var to store the value
	sc_uint<16> _q, _m, _a;
	// carry in/out
	bool c;
	// output to the caller
	sc_out<sc_uint<32> > out;
	//alu
	alu ALUA;
	//flag
	sc_signal<bool> oflag, lflag, zflag;
	void p1() {
		//init variable
		_q = ain.read();
		_m = bin.read();
		_a = 0b0000000000000000;
		c = 0b00;
		// run the algo for number of bit
		for (int i = 0; i < 16; i++) {
			//if q0 == 1
			//a = a+m
			if (_q[0]) {
				aa = _m;
				mm = _a;
				_a = ss;
				c = oflag;
			}
			//shift
			//shift q
			_q = _q >> 1;
			// shift last bit of a to first bit of q
			_q[15] = _a[0];
			//shift a
			_a = _a >> 1;
			//shift carry to first bit of a
			_a[15] = c;
			c = false;
		}
		//combine q and a to the out put
		//						a								q
		//			 [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0][0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
		// out[32] = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,]
		sc_uint<32> outi;
		for (int i = 0; i < 15; i++) {
			outi[i] = _q[i];
		}
		for (int i = 0; i < 15; i++) {
			outi[16 + i] = _a[i];
		}
		out.write(outi);
	}
	SC_CTOR(multiplier) : ALUA("ALU") {
		SC_METHOD(p1);
		// bind ALU port
		ALUA.ain(aa);
		ALUA.bin(mm);
		ALUA.sum(ss);
		control.write(0);
		ALUA.control(control);
		ALUA.zflag(zflag);
		ALUA.oflag(oflag);
		ALUA.lflag(lflag);

		//add sensitive
		sensitive << ain << bin << aa << mm << ss << out;
	}
};

#endif