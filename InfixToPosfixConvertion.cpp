/*
Nama: Serafino Kyrios Gunawan
NIM: 2802420126
Tugas: Infix To Posfix Convertion
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int operand(char expression)
{
	return (expression >= '0' && expression <= '9') || (expression >= 'a' && expression <= 'z') || (expression >= 'A' && expression <= 'Z');
}

int operatr(char c)
{
	if (c == '^')
	{
		return 3;
	}
    else if (c == '/' || c == '*')
    {
    	return 2;
	}
    else if (c == '+' || c == '-')
    {
    	return 1;
	}
    else
    {
    	return -1;
	}
}

void infix_to_posfix_convertion(char* expression)
{
	int length = strlen(expression);
	char result[length + 1];
	char stack[length];
	int j = 0;
	int top = -1;
	
	for(int i = 0 ; i < length ; i++)
	{
		char c = expression[i];
		
        if (operand(c))
        {
        	result[j++] = c;
		}
        else if (c == '(')
        {
        	stack[++top] = c;
		}
        else if (c == ')')
		{
            while (top != -1 && stack[top] != '(')
			{
                result[j++] = stack[top--];
            }
            if (top != -1)
            {
            	top--;
			}
        }
        else
		{
            while (top != -1 && operatr(c) <= operatr(stack[top]))
			{
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
	}
	
    while (top != -1)
	{
        result[j++] = stack[top--];
    }

    printf("Postfix Expression: %s\n", result);
}

int main()
{
	printf("Enter your Infix Here: ");
	char expression[100];
	scanf("%[^\n]", expression);
	getchar();
	
	infix_to_posfix_convertion(expression);
	
	return 0;
}
