CC = gcc
CFLAGS = -Wall

ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

SOURCES_1 = $(wildcard Project1/*.c)
SOURCES_2 = $(wildcard Project2/*.c)

build:
	$(CC) $(CFLAGS) $(SOURCES_1) -o Project1.out
	$(CC) $(CFLAGS) $(SOURCES_2) -o Project2.out
execute:
	./Project1.out
	./Project2.out
clean:
	rm -f *.o Project1.out
	rm -f *.o Project2.out
