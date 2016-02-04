#include <stdio.h> /* for atof() */
#include <stdlib.h> 
#include <math.h>
#define MAXOP 100		/* max size of operand or operator */
#define NUMBER '0'		/* signal that a number was found */
#define SIN 	1000
#define EXP	1001
#define POW	1002
 	
int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
main()
{
	int type;
	double op2, op1;
	char s[MAXOP];
	while( (type = getop(s)) != EOF) 
	{
		switch (type) 
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+' :
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-' :
				op2 = pop();
				push (pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case SIN:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				op1 = pop();
				if(op1 == 0 && op2 < 0)
					printf("error: zero pow\n");
				else
					push(pow(op1, op2));
				break;
			case '\n':
				printf ("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}


#define MAXVAL 100 /* maximum depth of val stack */
int sp = 0;		/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n",f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else 
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:
get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	while( (s[0]=c=getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
	{
		if(c == 's')
		{
			int c2, c3;
			c2 = getch();
			c3 = getch();
			if(c2 != 'i' || c3 != 'n')
			{
				ungetch(c2);
				ungetch(c3);
				return -1;
			}
			else
				return SIN;	
		}
		else if(c == 'e')
		{
			int c2, c3;
                        c2 = getch();
                        c3 = getch();
                        if(c2 != 'x' || c3 != 'p')
                        {
                                ungetch(c2);
                                ungetch(c3);
                                return -1;
                        }
                        else
                                return EXP;
		}
		else if(c == 'p')
                {
                        int c2, c3;
                        c2 = getch();
                        c3 = getch();
                        if(c2 != 'o' || c3 != 'w')
                        {
                                ungetch(c2);
                                ungetch(c3);
                                return -1;
                        }
                        else
                                return POW;
                }
		else
			return c; /* not a number */
	}
	i = 0;
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}


#define BUFSIZE 100
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void)  /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

