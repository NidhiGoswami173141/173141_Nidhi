CC = gcc
CFLAGS = -Wall

MODULES = 7




ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif


MODULE = 173141_Nidhi_Dennis_Ritchee_Module$(MODULES)_T006

SOURCES = main.c module_questions_choice.c $(wildcard */src/*.c)

INCLUDES = -Iinclude

OUTPUT = $(MODULE)/bin/main.out

OBJS = main.o module_questions_choice.o $(wildcard $(MODULE)/src/*.o)

build:
	mkdir -p $(MODULE)/bin
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT) -lm

object:
	mkdir -p $(MODULE)/obj
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -c $(OBJS)
	mv *.o $(MODULE)/obj/
execute:
	./$(OUTPUT) $(ARGS)

clean:
	rm -f $(OUTPUT)

