### CPP_Lisp2

CPP_Lisp stands for C++ Lisp and is implemented in the C++ language.
I started writing CPP_Lisp because I wanted to make my own Lisp reader, but it failed.
I tried again and managed to succeed with CPP_Lisp2.
CPP_Lisp2 reads the sexp from the keyboard and builds a list structure on the heap.
CPP_Lisp2 has a reference counter-type garbage collector that allows you to retrieve cells that you no longer need.
Garbage collection is still experimental and will be tailored to be useful in the future.

The Lisp reader managed to work, so I got a little greedy and ported the interpreter described in Paul Graham's "The Roots of Lisp".
Now that this works, I'll publish the source code.

### Usage:
make read_test  
./a.out
