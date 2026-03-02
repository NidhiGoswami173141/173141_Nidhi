CC = gcc
CFLAGES = -Wall

ifeq ($(DEBUG),1)
        CFLAGS += -g -O0
else
        CFLAGS += -O3
endif

SOURCES = src1.c src2.c src3.c main.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o Project1.out
execute:
	./Project1.out
clean:
	rm -f *.o Project1.out
