CC = gcc
CFLAGES = -Wall

ifeq ($(DEBUG),1)
        CFLAGS += -g -O0
else
        CFLAGS += -O3
endif

SOURCES = main.c $(wildcard Project*/*.c)

build:
	$(CC) $(CFLAGS) $(SOURCES) -o final.out
DEBUG:
	$(CC) $(CFLAGS) -g O0 $(SOURCES) -o final.out
execute:
	./final.out
clean:
	rm -f *.o final.out
