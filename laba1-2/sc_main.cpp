//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "adder.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_uint<4> > ain, bin, sum;
	sc_signal<bool> ci, co, oflag, zflag,as;

	sc_clock clk("clk", 10, SC_NS, 0.5);   // Create a clock signal

	add_sub DUT("add_sub");                 // Instantiate Device Under Test
	DUT.ain(ain);                       // Connect ports
	DUT.bin(bin);
	DUT.ci(ci);
	DUT.sum(sum);
	DUT.zflag(zflag);
	DUT.oflag(oflag);
	DUT.co(co);
	as.write(true);	
	DUT.as(as);

	stim STIM("stimulus");              // Instantiate stimulus generator
	STIM.clk(clk);
	STIM.ain(ain);
	STIM.bin(bin);
	STIM.ci(ci);

	check CHECK("checker");             // Instantiate checker
	CHECK.clk(clk);
	CHECK.ain(ain);
	CHECK.bin(bin);
	CHECK.ci(ci);
	CHECK.sum(sum);
	CHECK.co(co);
	CHECK.zflag(zflag);
	CHECK.oflag(oflag);

	sc_start(100, SC_NS);               // Run simulation

	return 0;                           // Return OK, no errors.
}
