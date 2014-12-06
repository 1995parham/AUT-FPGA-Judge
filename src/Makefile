OBJ=serial.o common.o main.o command.o
CFLAGS=-Wall

FPGA-Judge: $(OBJ)
	gcc $(CFLAGS) -o FPGA-Judge $(OBJ)
main.o:	main.c common.h command.h
	gcc $(CFLAGS) -c main.c
serial.o: serial.c serial.h common.h
	gcc $(CFLAGS) -c serial.c
common.o: common.h common.c
	gcc $(CFLAGS) -c common.c
command.o: command.h command.c common.h
	gcc $(CFLAGS) -c command.c
.PHONY: clean
clean:
	rm FPGA-Judge $(OBJ)
.PHONY: archive
archive:

