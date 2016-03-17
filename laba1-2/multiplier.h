#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include <systemc.h>
#include "alu.h"
SC_MODULE(multiplier) {
	// input
	sc_in<sc_int<16> > ain, bin;
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
	bool _qn;
	// output to the caller
	sc_out<sc_int<32> > out;
	//alu
	alu ALUA;
	//flag
	sc_signal<bool> oflag, lflag, zflag, enable;
	void p1() {
		//init variable
		_q = ain.read();
		_m = bin.read();
		_a = 0b0000000000000000;
		_qn = 0b00;
		// run the algo for number of bit
		for (int i = 0; i < 16; i++) {
			/*
			for (int j = 15; j >= 0; j--) {
				cout << _a[j];
			}
			cout << " ";
			for (int j = 15; j >= 0; j--) {
				cout << _q[j];
			}
			cout << " ";
			cout << _qn;
			cout << " ";
			*/
			//if q0 == 1
			//a = a+m
			if (_q[0] == 1 && _qn == 0) {
				aa = _a;
				mm = _m;
				control = 1;
				enable.write(!enable);
				sc_start(100, SC_NS);
				/*cout << aa << " - " << mm << " = " << ss << " ";*/
				_a = ss;
			}
			else if (_q[0] == 0 && _qn == 1) {
				aa = _a;
				mm = _m;
				control = 0;
				enable.write(!enable);
				sc_start(100, SC_NS);
				/*cout << aa << " + " << mm << " = " << ss <<" ";*/
				_a = ss;
			}
			/*
			shift
			C  A    Q    M
			1 1011 1001 1011 init
			0 1101 1100 1011 shft
			*/
			//shift q
			/*
			for (int j = 15; j >= 0; j--) {
				cout << _a[j];
			}
			cout << " ";
			for (int j = 15; j >= 0; j--) {
				cout << _q[j];
			}
			cout << " ";
			cout << _qn;
			cout << " ";
			*/
			_qn = _q[0];
			_q = _q >> 1;
			_q[15] = _a[0];
			_a = _a >> 1;
			_a[15] = _a[14];
			/*
			for (int j = 15; j >= 0; j--) {
				cout << _a[j];
			}
			cout << " ";
			for (int j = 15; j >= 0; j--) {
				cout << _q[j];
			}
			cout << " ";
			cout << _qn;
			cout << endl;
			*/
		}
		//combine q and a to the out put
		//						a								q
		//			 [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0][0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
		// out[32] = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,]
		sc_int<32> outi;
		for (int i = 0; i <= 15; i++) {
			outi[i] = _q[i];
		}
		for (int i = 0; i <= 15; i++) {
			outi[16 + i] = _a[i];
		}
		for (int i = 31; i >=0; i--) {
			cout << outi[i];
		}
		cout << endl;
		out.write(outi);
	}
	SC_CTOR(multiplier) : ALUA("ALU") {

		// bind ALU port
		ALUA.ain(aa);
		ALUA.bin(mm);
		ALUA.sum(ss);
		ALUA.enable(enable);
		ALUA.control(control);
		ALUA.zflag(zflag);
		ALUA.oflag(oflag);
		ALUA.lflag(lflag);

		SC_METHOD(p1);
		//add sensitive
		sensitive << ain << bin;
	}
};

#endif
	