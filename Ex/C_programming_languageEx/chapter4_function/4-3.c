/* Date：2020/2/16
 * 4-3: 在有了基本框架后，对计算器程序进行扩充就比较简单了。
 *  	在该程序中加入取模(%)运算符，并注意考虑负数的情况 
 */ 
#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXVAL 100 
#define BUFSIZE 100
#define abs(x) (x > 0 ? (x) : (-x))

void ungetch(int c);
int getch(void);
int getop(char s[]);
double pop(void);
void push(double x);
double atof(char s[]);


/* 栈 */ 
double val[MAXVAL];
int sp = 0;

/* 用于ungetch的缓冲区 */ 
char buf[BUFSIZE];
int bufp = 0;

char s[100];
int err = 0;	/* 检测除法错误 */ 

void main(void)
{
	char c;
	double op2;
	
	int j;
	while ((c = getop(s)) != EOF)
	{
		switch(c)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+'   :
				push(pop() + pop());
				break;
			case '*'   :
				push(pop() * pop());
				break;
			case '-'   :
				op2 = pop();
				push(pop() - op2);
				break;
			case '/'   :
				op2 = pop();
				if (op2 != 0) 
					push(pop() / op2);
				else
				{
					err = 1; 
					printf("error: zero divisor\n");
				}
				break;
			case '%':
				op2 = pop();
				if (op2 != 0) 
					push((int)pop() % (int)op2);
				else
				{
					err = 1; 
					printf("error: zero divisor\n");
				}
				break;				
			case '\n'   :
				if (!err)
				{
					printf("result = %.8g\n", pop());
					err = 0;
				}
				break;
			default	   :
				err = 1;
				printf("error: unknown command %s\n", s);
				break;
		}
#if 0
		printf("s = %s, c = %c, sp = %d, val[]= ", s, c, sp);
		for (j = 0; j < 5; j++)
			printf("%g ", val[j]);
		putchar('\n');
#endif
	}
	
	return;
}

void push(double x)
{
	if (sp < MAXVAL) 
		val[sp++] = x;
	else
		printf("error: stack full, can't push %g\n", x);
}

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

int getop(char s[])
{
	int i, c;
	
	/* 跳过空白 */ 
	while ((c = getch()) == ' ' || c == '\t')	
		;
	
	i = 0;
	/* 非数字 */ 
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
		
	/* 负数 */ 
	if (c == '-') 
	{		
		if (isdigit(c = getch()) || c == '.')
			s[i++] = '-';
		else
		{
			if (c != EOF)
			{		
				ungetch(c) ;
				return '-';
			}
		}	
	}
	
	
	/* 整数 */
	if (isdigit(c))
	{
		do
			s[i++] = c;
		while (isdigit(c = getch()));
	}
			
	/* 小数 */ 
	if (c == '.')
	{
		do
			s[i++] = c;
		while (isdigit(c = getch()));
	}
	
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	
	return NUMBER;
}

int getch(void)
{
	return (bufp > 0 ? buf[--bufp] : getchar());
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}



double atof(char s[])
{
	double base, pow;
	int i, sign, exp;
	
	/* 路过空白 */ 
	for (i = 0; isspace(s[i]); i++)
		;
		
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	
	for (base = 0.0; isdigit(s[i]); i++)
	{
		base = 10.0 * base + (s[i] - '0');
		//printf("sign = %d, base = %g\n", sign, base);
	}	
	
	if (s[i] == '.')
		i++;
	
	for (pow = 1.0; isdigit(s[i]); i++)
	{
		base = 10.0 * base + (s[i] - '0');
		pow *= 10.0;
		//printf("base = %g\n", base);
	}
	base = sign * base / pow;		/* 底数 */ 

#if 1	
	/* 指数 */ 
	if (s[i] == 'e' || s[i] == 'E')
	{
		sign = (s[++i] == '-' ? -1 : 1);
		if (s[i] == '-' || s[i] == '+')
			i++;
		
		for (exp = 0; isdigit(s[i]); i++)
			exp = 10 * exp + (s[i] - '0');
		
		if (sign == -1)
			while (exp-- > 0)
				base /= 10;
		else
			while (exp-- > 0)
				base *= 10;
	}
#endif	
	return base;
}


