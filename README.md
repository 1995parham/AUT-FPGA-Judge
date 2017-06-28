# AUT-FPGA-Challenge

## Introduction
This repository contains serial tools and some documentation about FPGA competition.
Trax game impelementation can be found at [OpenTrax](https://github.com/1995parham/OpenTrax)
and simple Altera RS232 comminucation
can be found at [AlteraDE2-RS232](https://github.com/1995parham/AlteraDE2-RS232).  
In this repository there is C base program for serial comminucation, in order to use it you must
first download and run NetworkServerPlayer in OpenTrax and then run this program, then
you can connect your FPGA and play with OpenTrax.

## OpenTrax Testing
In `test/` directory, a python based program that can be used to test OpenTrax Net Server Player exists.

## Special Thanks
* [Dr.Bakhshi](http://ceit.aut.ac.ir/~bakhshis/): who helped me with his great ideas.

## Installation
```
cmake .
make
```
