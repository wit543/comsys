// All systemc modules should include systemc.h header file
#include <systemc.h>
#include "and.h"	

// Hello_world is module name
SC_MODULE (hello_world) {
  SC_CTOR (hello_world) {
    // Nothing in constructor 
  }
  void say_hello() {
    //Print "Hello World" to the console.
    cout << "Hello World.\n";
  }
};

class State0 {
	public:
		void changeState();
		void execute();
};
void State0::changeState() {

}

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
  hello_world hello("HELLO");
  // Print the hello world
  hello.say_hello();
  AND2 and ("and");
  sc_signal <bool> a, b, q;


  and.a(a);
  and.b(b);
  and.q(q);

  sc_trace_file *fp;
  fp = sc_create_vcd_trace_file("wave");
  fp->set_time_unit(100, SC_PS);
  sc_trace(fp, a, "a");
  sc_trace(fp, b, "b");
  sc_trace(fp, q, "q");

  a = true;
  b = true;
  sc_start(100, SC_NS);

  a = false;
  b = false;
  sc_start(100, SC_NS);

  a = true;
  b = false;
  sc_start(100, SC_NS);

  a = false;
  b = true;
  sc_start(100, SC_NS);

  

  sc_close_vcd_trace_file(fp);


	

  return(0);
}

