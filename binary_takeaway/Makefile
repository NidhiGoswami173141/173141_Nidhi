CC = gcc
CFLAGS = -Wall

ifeq ($(DEBUG),1)
        CFLAGS += -g -O0
else
        CFLAGS += -O3
endif

INCLUDES = -Iinclude

SOURCES = main.c question_choice.c include/header.h lib/function.c src/playgame.c

OUTPUT = bin/main.out

build:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)
execute:
	./$(OUTPUT)
clean:
	rm -f $(OUTPUT)
