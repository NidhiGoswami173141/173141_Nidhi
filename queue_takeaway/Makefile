CC = gcc
CFLAGS = -Wall

ifeq ($(DEBUG),1)
        CFLAGS += -g -O0
else
        CFLAGS += -O3
endif

INCLUDES = -Iinclude

SOURCES = main.c src/linkedlist_pq.c include/header.h lib/function.c 

OUTPUT = bin/main.out

build:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)
execute:
	./$(OUTPUT)
clean:
	rm -f $(OUTPUT)
