#################################################################################
#Author : Nidhi Goswami
#Date : 5-2-2026
#Description: linke all .c file and execute and bulit and clean command in this
#################################################################################
CC = gcc
CFLAGS = -Wall

ifeq ($(DEBUG),1)
        CFLAGS += -g -O0
else
        CFLAGS += -O3
endif


SOURCES = src1.c src2.c src3.c main.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o main.out
execute:
	./main.out

clean:
	rm -f *.o main.out
