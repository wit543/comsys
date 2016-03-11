#include <systemc.h>

#include "adder.h"
#include "multiplier.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_uint<16> > ain, bin, sum;
	sc_signal<sc_uint<32> > out;
	sc_signal<bool> ci, co;
	sc_signal<bool> zflag, oflag, lflag;
	sc_signal<bool> as;
	sc_clock clk("clk", 10, SC_NS, 0.5);   // Create a clock signal

	//trace
	sc_trace_file *fp;
	fp = sc_create_vcd_trace_file("add_sub_wave");
	fp->set_time_unit(1, SC_PS);
	sc_trace(fp, ain, "ain");
	sc_trace(fp, bin, "bin");
	sc_trace(fp, sum, "sum");
	sc_trace(fp, ci, "ci");
	sc_trace(fp, co, "co");
	sc_trace(fp, zflag, "zflag");
	sc_trace(fp, oflag, "oflag");
	sc_trace(fp, lflag, "lflag");
	sc_trace(fp, clk, "clk");


	//bind multoplier
	multiplier mul("multiplier");
	mul.ain(ain);
	mul.bin(bin);
	mul.out(out);

	//test 1: 3*4
	ain.write(4);
	bin.write(3);
	sc_start(100, SC_NS);               // Run simulation

	cout << ain << "*" << bin << "=" << out << endl;

	//test 2: 2*3
	ain.write(2);
	bin.write(3);
	sc_start(100, SC_NS);               // Run simulation

	cout << ain << "*" << bin << "=" << out << endl;

	//test 3: 5*3
	ain.write(5);
	bin.write(3);
	sc_start(100, SC_NS);               // Run simulation

	cout << ain << "*" << bin << "=" << out << endl;


	return 0;                           // Return OK, no errors.
}