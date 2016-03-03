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
	sc_in<sc_uint<16> > sum;
	sc_in<bool> co;
	sc_in<bool> zflag, oflag, lflag;

	sc_uint<5> sumc;

	void pc1() {

		if (as) {
			sumc = ain.read() - bin.read() + ci.read();

			int lflagNum = sum.read() - (lflag * 16);
			if (lflagNum == -16) {
				lflagNum = 0;
			}
			cout << "sub " << ain.read() << " - " << bin.read() << " + " << ci.read() << " = " << lflagNum;

			if (sumc(3, 0) == sum.read()) {
				cout << " Passed" << endl;
			}
			else {
				cout << " Failed, expected sum=" << sumc(3, 0) << " co=" << sumc[4] << endl;
			}
		}
		else {
			sumc = ain.read() + bin.read() + ci.read();

			cout << "fulladder " << ain.read() << " + " << bin.read() << " + " << ci.read() << " = " << sum.read() + co.read() * 16;;
			if (sumc(3, 0) == sum.read() && co == sumc[4]) {
				cout << " Passed" << endl;
			}
			else {
				cout << " Failed, expected sum=" << sumc(3, 0) << " co=" << sumc[4] << endl;
			}
		}

		if (zflag.read() == true) { // something like this.
			cout << "zero value" << endl;
		}
		if (oflag.read() == true && !lflag.read() == true) { // something like this.
			cout << "overflow" << endl;
		}
		if (lflag.read() == true && zflag.read() == false) {
			cout << "a less than b " << endl;
		}

	}

	SC_CTOR(check) {
		SC_METHOD(pc1);
		sensitive << clk.pos();
		dont_initialize();
	}
};
#endif