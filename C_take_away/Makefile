CC = gcc

CFLAGS = -Wall

ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

MODULE = Take_Away_File_Encryption_System

INCLUDES = -Iinclude

TEST_SOURCES = main.c src/function.c -lcrypto
INTERACTIVE_SOURCES = interactive.c src/function.c

TEST_OUTPUT = bin/main.out
INTERACTIVE_OUTPUT = bin/test.out

build: main test

main:
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SOURCES) -o $(TEST_OUTPUT)

test:
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(INTERACTIVE_SOURCES) -o $(INTERACTIVE_OUTPUT) -lcrypto

execute_main:
	$(CC) $(CFLAGS) $(INCLUDES) -DRUN_TASK=$(TASK) $(TEST_SOURCES) -o $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

execute_test:
	./$(INTERACTIVE_OUTPUT)

object:
	mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c interactive.c src/function.c
	mv *.o obj/

clean:
	rm -rf bin/*.out
	rm -rf obj
