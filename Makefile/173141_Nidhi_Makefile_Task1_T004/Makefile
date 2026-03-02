##############################################################################################
#AUthor : Nidhi Goswami
#Date : 5-2-2026
#Description:  Makefile for link all  .c file and for complilation and execution and clean 
##############################################################################################


CC = gcc
CFLAGS = -Wall
LDFLAGS =

ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

SOURCES = src1.c src2.c src3.c
BINS = bin/bin1 bin/bin2 bin/bin3

all: build

build: mod1 mod2 mod3
bin:
	mkdir -p bin

mod1:
	$(CC) $(CFLAGS) src1.c -o bin/bin1

mod2:
	$(CC) $(CFLAGS) src2.c -o bin/bin2

mod3:
	$(CC) $(CFLAGS) src3.c -o bin/bin3

run1: mod1
	./bin/bin1

run2: mod2
	./bin/bin2

run3: mod3
	./bin/bin3

clean:
	rm -f $(BINS)

