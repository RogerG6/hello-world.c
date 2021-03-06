# include <stdio.h>
# include <ctype.h>

# define CHOICE1 8.75
# define CHOICE2 9.33
# define CHOICE3 10.00
# define CHOICE4 11.20
# define CHOICE5 "quit"
# define RATE1 0.15
# define RATE2 0.2
# define RATE3 0.25
# define OT 40
# define OTTR 1.5
# define S_WT 400
# define BREAK1 300
# define BREAK2 450
# define TAX1 BREAK1 * RATE1
# define TAX2 TAX1 + (BREAK2-BREAK1) * RATE2

int main(void)
{
	char choice;
//	int i = 1;
	float s_ph = 10;
	int hour;
	float salary, tax, ni;  //ni Ϊ net income
	
	printf("***************************************************************\n");
	printf("Enter the number corresponding to the desired pay rate or action:\n");
	printf("a) $%.2f                 b) $%.2f\n", CHOICE1, CHOICE2);
	printf("c) $%.2f                d) $%.2f\n", CHOICE3, CHOICE4);
	printf("q) %s\n", CHOICE5);
	printf("***************************************************************\n\n");
	
	do
	{
			while(isspace(choice = getchar()))
				continue;
			switch (choice)
		    {
				case 'a' : s_ph = CHOICE1; break;	
				case 'b' : s_ph = CHOICE2; break;			
				case 'c': s_ph = CHOICE3; break;	
				case 'd': s_ph = CHOICE4; break;	
				case 'q': goto over;	
		    	default: printf("Please enter your choice again!\n");	
			}
	}while(choice < 'a' || choice > 'd');
	
	printf("Please enter the workhours in a week: ");
	scanf("%d", &hour) ;
	if (hour <= OT)
	{
		salary = s_ph * hour;
		
		if (salary <= BREAK1)
			tax = salary * RATE1;
		else
			tax = TAX1 + (salary - BREAK1)*RATE2;
	}
	else
	{
		salary = OT * s_ph + (hour - OT) * OTTR * s_ph;
		
		if (salary <= BREAK2)
			tax = TAX1 + (salary - BREAK1) * RATE2;
		else
			tax = TAX2 + (salary - BREAK2) * RATE3;
		
	}
	ni = salary - tax;
	printf("salary = %f, tax = %f, net income = %f\n", salary, tax, ni);
	
	over: return 0;
}
