/*
Author: Nidhi Goswami
Date: 10-04-2026
Description : undcl program is used to convert a word description of a declaration into a C declaration. ensure that the program does not add unnecessary parentheses around parts of the declaration.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "module.h"
#define MAXTOKEN 100
#define MAXPOINTERS 10

enum { NAME, PARENS, BRACKETS };


int32_t gettoken(void);
int32_t tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char out[1000]; /* output string */

/* undcl: convert word description to declaration */
void undcl_fun()
{
	int32_t type;
	int32_t index, ch;
	int32_t pcount;
	char temp[MAXTOKEN];
	char p[MAXPOINTERS]; /* space for 9 pointers */
	while (gettoken() != EOF){
		strcpy(out, token);		
		pcount = 0;
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS){
				strcat(out, token);
			} else if (type == '*'){
				pcount++;
				while ((ch = getch_function()) == '*' || ch == ' '){
					if (ch == '*'){
						if (pcount < (MAXPOINTERS - 1))
							pcount++;
						else
							break;
					}
				}
				ungetch_function();
				for (index = 0; index < pcount; index++){
					p[index] = '*';
				}
				p[index] = '\0';
				pcount = 0;
				sprintf(temp, "(%s%s)", p, out);
				strcpy(out, temp);
			} else if (type == NAME){
				sprintf(temp, "%s%s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);
			}
		printf("%s\n", out);
	}
}

/* gettoken: return next token.
 * I have getch() and ungetch() included from the header
 * file getch.h , note that ungetch() in my implementation
 * requires no prameter.
 */
int32_t gettoken(void)
{
	int32_t ch;
	char *p = token;
	while ((ch = getch_function()) == ' ' || ch == '\t');
	if (ch == '('){
		if ((ch = getch_function()) == ')'){
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch_function();
			return tokentype = '(';
		}
	} else if (ch == '['){
		for (*p++ = ch; (*p++ = getch_function()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(ch)) {
		for (*p++ = ch; isalnum(ch = getch_function()); )
			*p++ = ch;
		*p = '\0';
		ungetch_function();
		return tokentype = NAME;
	} else {
		return tokentype = ch;
	}
}


#define BUFF_SIZE 1000
static char line[BUFF_SIZE]; /* buffer for line */
static int32_t buff_p = 0; /* position in buf */
static int32_t readflag = 1;
static int32_t get_line_fun(char *s, int32_t max_length);
/* getch: read a character */
int32_t getch_function(void)
{
	int32_t length = 0;
	do {
		if (readflag == 1){
			/* prime the line array */
			if ((length = get_line_fun(line,BUFF_SIZE)) > 0){
				if(length >= (BUFF_SIZE - 1)){
					printf("ERROR: line buffer exceeded\n");
					return EOF;
				}
			}else{
				return EOF;
			}
			buff_p = 0;
			readflag = 0;
		}
		if (line[buff_p] == '\0')
			readflag = 1; /* need to read a new line */	
	} while (readflag);
	return line[buff_p++];
}
/* ungetch: push character back on input */
void ungetch_function(void)
{
	if (buff_p > 0)
		--buff_p;
}
/*
 * print_source: print out the contents of the line read
 */
void print_source_fun(void)
{
	printf("%s", line);
}
int32_t get_line_fun(char *s, int32_t max_length)
{
	int32_t ch;
	char *start = s; /* save pointer to start of buffer s */
	char *end = s + (max_length - 2); /* point near to end of buffer s */
	while((ch = getchar()) != EOF && ch != '\n' && s < end){
		*s++ = ch;	
	}
	/* store last character read */
	if(ch != EOF)
		*s++ = ch;
	*s = '\0';/* terminate the line */
	return s - start; /* number of characters read */
}
