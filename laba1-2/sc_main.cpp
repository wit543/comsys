#include <systemc.h>

#include "multiplier.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_int<16> > ain, bin;
	sc_signal<sc_int<32> > out;
	sc_clock clk("clk", 10, SC_NS, 0.5);   // Create a clock signal

										   //trace
	sc_trace_file *fp;
	fp = sc_create_vcd_trace_file("add_sub_wave");
	fp->set_time_unit(1, SC_PS);
	sc_trace(fp, ain, "ain");
	sc_trace(fp, bin, "bin");
	sc_trace(fp, clk, "clk");


	//bind multoplier
	multiplier mul("multiplier");
	mul.ain(ain);
	mul.bin(bin);
	mul.out(out);

	
	//test : multiplication table
	/*
	for (int i = 1; i < 13; i++) {
		for (int j = 2; j < 13; j++) {

			ain.write(j);
			bin.write(i);
			sc_start(1000, SC_NS);               // Run simulation
			cout << ain << "*" << bin << " = " << out << " ";
		}
		cout << endl;
	}
	*/

	
	ain.write(-5);
	bin.write(7);
	sc_start(1000, SC_NS);               // Run simulation
	cout << ain << "*" << bin << " = " << out << " ";
	
	return 0;                           // Return OK, no errors.
}
