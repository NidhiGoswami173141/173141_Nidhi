CC = gcc

CFLAGS = -Wall

ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

INCLUDES = -Iheader

SOURCES = main.c module_question_choice.c header/header.c $(wildcard */src/*.c)

OUTPUT = main.out

build:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT) -lm

execute:
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
