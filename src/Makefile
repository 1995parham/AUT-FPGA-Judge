OBJ=serial.o common.o
CFLAGS=-Wall

FPGA-Judge: $(OBJ)
	gcc $(CFLAGS) -o FPGA-Judge $(OBJ)
serial.o : serial.c serial.h common.h
	gcc $(CFLAGS) -c serial.c
common.o: common.h common.c
	gcc $(CFLAGS) -c common.c
.PHONY: clean
clean:
	rm FPGA-Judge $(OBJ)
.PHONY: archive
archive:

