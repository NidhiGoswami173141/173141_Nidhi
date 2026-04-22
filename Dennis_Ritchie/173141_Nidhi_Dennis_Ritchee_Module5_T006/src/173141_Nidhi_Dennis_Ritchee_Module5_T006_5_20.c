/*
Author: Nidhi Goswami
Date : 10-4-2026
Description :
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSYMBL (1 << 7)
#define MAXMSG (1 << 10)
#define MAXCHBUF (1 << 1)
#define MAXTKBUF (1 << 1)
#define MAXBOILER (1 << 4)

enum { STORE, QUAL, TYPE, VAR, BRACKETS };
enum { OK = 0, ERROR };
enum { NO = 0, YES };

int declaration(char *dec, int ispara);
int dcl(char *name, char *out, int allowanon);
int dirdcl(char *name, char *out, int allowanon);
int args(char *out);

int get_token(void);
void ungettoken(int ttype, char *tk);
int ws(void);
int name(char *p);
int brackets(char *p);
int oparens(char *p);
int contains(char **names, int count, char *name);

void nextdef(void);
int get_ch(void);
void unget_ch(int c);

int tokentypee;
char tokenn[MAXSYMBL];

int chbuf[MAXCHBUF];
int chbufp = 0;

int ttbuf[MAXTKBUF];
char tkbuf[MAXTKBUF][MAXSYMBL];
int tkbufp = 0;

char *types[] = { "void",  "char",   "short",  "int",	  "long",
		  "float", "double", "signed", "unsigned" };
int ntypes = 9;
char *stores[] = { "auto", "register", "static", "extern" };
int nstores = 4;
char *quals[] = { "const", "volatile" };
int nquals = 2;

void handle_arg_type()
{
	char dec[MAXMSG];
	while (get_token() != EOF) {
		if (declaration(dec, NO) != OK) {
			nextdef();
		}
	}
	return 0;
}

int declaration(char *dec, int ispara)
{
	char store[MAXSYMBL + MAXBOILER];
	char qual[MAXSYMBL + MAXBOILER];
	char type[MAXMSG];
	char name[MAXSYMBL];
	char out[MAXMSG];

	store[0] = '\0';
	qual[0] = '\0';
	type[0] = '\0';

	if (tokentypee == STORE) {
		sprintf(store, " in %s storage", tokenn);
		get_token();
	}
	if (tokentypee == QUAL) {
		sprintf(qual, " %s", tokenn);
		get_token();
	}
	if (tokentypee != TYPE) {
		printf("\nerror: Expected a type\n");
		return ERROR;
	}
	do {
		if (type[0] != '\0')
			strcat(type, " ");
		strcat(type, tokenn);
	} while (get_token() == TYPE);
	ungettoken(tokentypee, tokenn);

	do {
		out[0] = '\0';
		if (dcl(name, out, ispara) != OK) {
			return ERROR;
		} else if (tokentypee != ';' && tokentypee != ',' &&
			   tokentypee != ')') {
			printf("\nsytax error, got %d/%c\n", tokentypee,
			       tokentypee);
			return ERROR;
		} else {
			sprintf(dec, "%s:%s%s %s%s", name, qual, out, type,
				store);
			if (!ispara)
				printf("\n%s\n", dec);
		}
	} while (!ispara && tokentypee == ',');
	return OK;
}

int dcl(char *name, char *out, int allowanon)
{
	int ns, rslt;

	for (ns = 0; get_token() == '*';)
		ns++;
	if ((rslt = dirdcl(name, out, allowanon)) != OK)
		return rslt;
	while (ns-- > 0)
		strcat(out, " pointer to");
	return OK;
}

int dirdcl(char *name, char *out, int allowanon)
{
	int rslt;

	if (tokentypee == VAR)
		strcpy(name, tokenn);
	else if (tokentypee == '(') {
		if ((rslt = dcl(name, out, allowanon)) != OK)
			return rslt;
		if (tokentypee != ')') {
			printf("\nerror: missing )\n");
			return ERROR;
		}
	} else if (allowanon) {
		strcpy(name, "<unnamed>");
		allowanon = NO;
		ungettoken(tokentypee, tokenn);
	} else {
		printf("\nerror: expected variable name or (dcl)\n");
		return ERROR;
	}
	while (get_token() == '(' || tokentypee == BRACKETS) {
		if (tokentypee == '(') {
			strcat(out, " function taking");
			if ((rslt = args(out)) != NO) {
				return rslt;
			}
		} else {
			strcat(out, " array");
			strcat(out, tokenn);
			strcat(out, " of");
		}
	}
	return OK;
}

int args(char *out)
{
	char dec[MAXMSG];
	int argcount = 0;
	char *seperator = " argument ";
	int expectarg = YES;

	if (get_token() == ')') {
		/* fun() */
		expectarg = NO;
	} else if (tokentypee == TYPE && strcmp(tokenn, "void") == 0) {
		if (get_token() == ')')
			/* fun(void) */
			expectarg = NO;
		else {
			ungettoken(tokentypee, tokenn);
			tokentypee = TYPE;
			strcpy(tokenn, "void");
		}
	}

	if (expectarg) {
		do {
			if (argcount++ > 0)
				get_token();
			if (declaration(dec, YES) != OK)
				return ERROR;
			strcat(out, seperator);
			strcat(out, dec);
			seperator = " and argument ";
		} while (tokentypee == ',');
	}
	if (tokentypee == ')') {
		if (argcount == 0)
			strcat(out, " no arguments");
		strcat(out, " returning");
	} else {
		printf("\nerror: expected closing parentheses "
		       "after arguments (got %d/%c)\n",
		       tokentypee, tokentypee);
		return ERROR;
	}
	return OK;
}

int get_token(void)
{
	if (tkbufp > 0) {
		--tkbufp;
		tokentypee = ttbuf[tkbufp];
		strcpy(tokenn, tkbuf[tkbufp]);
	} else {
		ws();
		if (!(oparens(tokenn) || brackets(tokenn) || name(tokenn))) {
			tokenn[0] = tokentypee = get_ch();
			tokenn[1] = '\0';
		}
	}
	return tokentypee;
}

void ungettoken(int ttype, char *tk)
{
	if (tkbufp >= MAXTKBUF) {
		printf("ungettoken: too many tokens\n");
	} else {
		ttbuf[tkbufp] = ttype;
		strcpy(tkbuf[tkbufp], tk);
		tkbufp++;
	}
}

int ws(void)
{
	char c;
	int rslt = NO;

	while (isspace(c = get_ch()))
		rslt = YES;
	unget_ch(c);
	return rslt;
}

int name(char *p)
{
	char c, *tkn;
	int rslt = NO;

	tkn = p;
	if (isalpha(c = get_ch()) || c == '_') {
		rslt = YES;
		for (*p++ = c; isalnum(c = get_ch()) || c == '_';)
			*p++ = c;
		*p = '\0';
		if (contains(types, ntypes, tkn))
			tokentypee = TYPE;
		else if (contains(stores, nstores, tkn))
			tokentypee = STORE;
		else if (contains(quals, nquals, tkn))
			tokentypee = QUAL;
		else
			tokentypee = VAR;
	}
	unget_ch(c);
	return rslt;
}

int brackets(char *p)
{
	char c;

	if ((c = get_ch()) == '[') {
		for (*p++ = c; (*p++ = (c = get_ch())) != ']';)
			;
		*p = '\0';
		tokentypee = BRACKETS;
		return YES;
	}
	unget_ch(c);
	return NO;
}

int oparens(char *p)
{
	char c;

	if ((c = get_ch()) == '(') {
		*p++ = tokentypee = '(';
		*p = '\0';
		return YES;
	}
	unget_ch(c);
	return NO;
}

void nextdef(void)
{
	int c;

	while ((c = get_ch()) != ';' && c != EOF)
		;
	if (c == EOF)
		unget_ch(c);
}

int contains(char **names, int count, char *name)
{
	int i;

	for (i = 0; i < count; i++)
		if (strcmp(name, names[i]) == 0)
			return YES;
	return NO;
}

int get_ch(void)
{
	return (chbufp > 0) ? chbuf[--chbufp] : getchar();
}

void unget_ch(int c)
{
	if (chbufp >= MAXCHBUF)
		printf("ungetch: too many characters\n");
	else
		chbuf[chbufp++] = c;
}
