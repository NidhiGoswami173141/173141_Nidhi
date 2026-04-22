/*
Author: Nidhi Goswami
Date : 8-4-2026
Description : Make dcl recover from input errors.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "module.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

static void dcl(void);
static void dirdcl(void);

static int gettoken(void);
static int tokentype; /* type of last token */
static int oldtoken; /* previous tokentype */
static char token[MAXTOKEN]; /* last token string */
static char name[MAXTOKEN]; /* identifier name */
static char datatype[MAXTOKEN]; /* data type = char, int, etc. */
static char out[1000]; /* output string */
static int parenopen = 0; /* count of open parentheses */
static int parenclose = 0; /* count of unmatched close parentheses */
static int alphaseen = 0; /* track alpha statis for subscript */

void dcl_fun() /* convert declaration to words */
{
	while (gettoken() != EOF) { /* 1st token on line */		
		strcpy(datatype, token); /* pull data type */
		while (tokentype != '\n'){
			out[0] = '\0';
			name[0] = '\0';
			token[0] = '\0';
			parenopen = 0;
			parenclose = 0;
			dcl(); /* parse rest of line */
			if (parenopen > 0) {
				printf("error: missing one or more )\n");
			} 
			if (parenclose > 0) {
				printf("error: missing one or more (\n");
			}
			printf("%s: %s %s\n", name, out, datatype);
		}
	}
}

static void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; ) /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
static void dirdcl(void)
{
	int tempparens;
	if (tokentype == ','){ /* allow multiple declarators on a line */
		tokentype = '\n';
	}
	if (tokentype == '\n'){
		return;
	}
	if (tokentype == '('){ /* ( dcl ) */
		++parenopen;
		dcl();
		if (tokentype == ')'){
			--parenopen;
		} else { 
			if(oldtoken == '(')
				strcat(out, " function returning");
			ungetch_fun();
		}
	} else if (tokentype == NAME){ /* variable name */
		strcpy(name, token);
	} else if (tokentype == PARENS){
		strcat(out, " function returning");
	} else if (tokentype == BRACKETS){
		strcat(out, " array");
		strcat(out, token);
		strcat(out, " of");
	} else if (oldtoken == NAME && tokentype == ')'){
		++parenclose;
		strcat(out, " function returning");
	} else {
		printf("error: expected name or (dcl)\n");
	}
	gettoken();
	while (tokentype == PARENS || tokentype == BRACKETS 
			|| tokentype == '(' || isdigit(tokentype) ||
			tokentype == NAME){
		if (tokentype == PARENS){
			strcat(out, " function returning");
		} else if (tokentype == BRACKETS) {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		} else if (tokentype == '('){
			/* process function with parameters... for now
			 * just ignoring them */
			/* prevents detection of unmatched ) in gettoken() */
			++parenopen; /* don't remove this! */
			tempparens = 1; /* track balanced parentheses */
			strcat(out, " function returning");
			do {
				gettoken();
				if (tokentype == '('){
					++tempparens;
				} else if (tokentype == ')'){
					--tempparens;
				} else if (tokentype == '\n'){
					return;
				}
			} while (tokentype != ')' || tempparens != 0);
			--parenopen;
		} else {
			/* saw NAME or digit: it could be this was part
			 * of a parameter to a function or a subscript
			 * to an array */
			do {
				gettoken();
				if (tokentype == BRACKETS){
					strcat(out, " array");
					strcat(out, token);
					strcat(out, " of");
					break; /* exit do-while */
				}
				if (tokentype == PARENS){
					strcat(out, " function returning");
					break; /* exit do-while */
				}
			} while(tokentype != '\n');
			if (tokentype == '\n')
				return;
		}
		gettoken();
	}
}

/* gettoken: return next token.
 */
static int gettoken(void)
{
	int c;
	int i;
	char *p = token;
	oldtoken = tokentype; /* back up tokentype */
	while ((c = getch_fun()) == ' ' || c == '\t')
		;
	/* remove comments */
	while (c == '/'){
		c = getch_fun();
		if (c == '/'){
			while (c != '\n')
				c = getch_fun();
		}
		if (c == '*'){ /* start of comment */
			do {
				c = getch_fun();
				if (c == '*'){
					c = getch_fun();
					if(c == '/'){
						c = getch_fun();
						break;
					}
				}
			} while (c != '\n');
		}
	}
	/* Assume anything past one of these characters is something
	 * we do not care to process. */
	if (c == ';' || c == '{' || c == '='){
		while (c != '\n')
			c = getch_fun();
	} 
	/* count unmatched closing parentheses */
	if (c == ')' && parenopen == 0){		
		++parenclose;
		return tokentype = PARENS;
	}
	if (c == '('){
		if ((c = getch_fun()) == ')'){
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch_fun();
			return tokentype = '(';
		}
	} else if (c == '['){ /* we sort of know what should be in here */
		alphaseen = 0;
		for (*p++ = c, i = 0; (c = getch_fun()); ++i){
			while (c == ' ' || c == '\t') /* allow for space */
				c = getch_fun();
			if (i == 0 && isalpha(c)){
				*p++ = c;
				alphaseen = 1;
			} else if (isdigit(c) && alphaseen == 0){
				*p++ = c;
			} else if (i > 0 && isalpha(c)){
				printf("error: invalid array subscript\n");
				while (isalnum(c = getch_fun()))
					;
				ungetch_fun();
			} else if (isdigit(c) && alphaseen){
				printf("error: invalid array subscript\n");
				while (isalnum(c = getch_fun()))
					;
				ungetch_fun();
			} else if (c == ']'){
				*p++ = c;
				break;
			} else {
				printf("error: missing ]\n");
				*p++ = ']';
				ungetch_fun();
				break;
			}
		}
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (c == ']'){ /* unmatched closing bracket? */
		printf("error: missing [\n");
		*p++ = '[';
		*p++ = ']';
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c) || c == '_') { /* an _ is a valid char too */
		for (*p++ = c; isalnum(c = getch_fun()) || c == '_'; )
			*p++ = c;
		*p = '\0';
		ungetch_fun();
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}


#define BUFF_SIZE 1000
static char line[BUFF_SIZE]; /* buffer for line */
static int buff_p = 0; /* position in buf */
static int readflag = 1;
static int get_line_fun(char *s, int max_length);
/* getch: read a character */
int getch_fun(void)
{
	int length = 0;
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
void ungetch_fun(void)
{
	if (buff_p > 0)
		--buff_p;
}
/*
 * print_source: print out the contents of the line read
 */
void print_source(void)
{
	printf("%s", line);
}
/*
 * getline: 
 */
int get_line_fun(char *s, int max_length)
{
	int c;
	char *start = s; /* save pointer to start of buffer s */
	char *end = s + (max_length - 2); /* point near to end of buffer s */
	while((c = getchar()) != EOF && c != '\n' && s < end){
		*s++ = c;	
	}
	/* store last character read */
	if(c != EOF)
		*s++ = c;
	*s = '\0';/* terminate the line */
	return s - start; /* number of characters read */
}
