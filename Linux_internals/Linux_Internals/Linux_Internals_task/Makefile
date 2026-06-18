#CC = gcc

#CFLAGS = -Wall

#ifeq ($(DEBUG),1)
 #       CFLAGS += -g -O0
#else
 #       CFLAGS += -O3
#endif


#INCLUDES = -Iinclude


#SOURCES = main.c question_choice.c $(wildcard src/*.c)


#OUTPUT = main.out


#build:
#	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)


#execute:
#	./$(OUTPUT) $(ARGS)

#execute_input:
#	./$(OUTPUT) < $(FILE)

#execute_input_output:
#	./$(OUTPUT) < $(FILE) > $(OUT)

#clean:
#	rm -f $(OUTPUT)
CC = gcc

CFLAGS = -Wall -g

INCLUDES = -Iinclude


SOURCES = main.c question_choice.c $(wildcard src/*.c)


OUTPUT = main.out


build:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)


execute:
	./$(OUTPUT) $(ARGS)


clean:
	rm -f $(OUTPUT)
