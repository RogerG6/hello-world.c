/* Date��2020/3/24
 * 1-23����дһ��ɾ��C���Գ���������ע����䡣Ҫ��ȷ�����������ŵ��ַ������ַ���������C�����У�ע�Ͳ�����Ƕ��
 */
#include <stdio.h>

void echo_quote(int c);
void rcomment(int c);
void in_comment(void);

int main(void)
{
	int c;
	
	while ((c = getchar()) != EOF)
		rcomment(c);
	return 0;
}

void rcomment(int c)
{
	int d;
	
	if (c == '/'){
		if ((d = getchar()) == '*')	// ע�� 
			in_comment();
		else if (d == '/')		// �ݹ� 
			rcomment(d);
		else {					 
			putchar(c);
			putchar(d);
		}
	}
	else if (c == '\'' || c == '"')	// �ַ������ַ������� 
		echo_quote(c);
	else
		putchar(c);
}

void in_comment(void)
{
	int c = getchar();	//pre char
	int d = getchar();	//current char
	
	while (c != '*' || d != '/') {
		c = d;
		d = getchar();
	}
}

void echo_quote(int c)
{
	int d;
	
	putchar(c);
	while ((d = getchar()) != c) {
		putchar(d);
		if (d == '\\')
			putchar(getchar());
	}
	putchar(d);
}

