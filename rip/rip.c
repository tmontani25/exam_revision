#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void generate_balanced(char *str, int index, int left_rem, int right_rem, int pair, char *buffer, int buffer_index)
{
	if (str[index] == '\0')
	{
		if (left_rem == 0 && right_rem == 0 && pair == 0) // cas ou la combinaison de parentheses est ok
		{
			buffer[buffer_index] = '\0';
			puts(buffer);
		}
		return ;
	}
	if (str[index] == '(')
	{
		if (left_rem > 0)
		{
			buffer[buffer_index] = ' '; // on test en enlevant la parenthese
			generate_balanced(str, index + 1, left_rem - 1, right_rem, pair, buffer, buffer_index + 1);
		}
		buffer[buffer_index] = '('; // on test en laissant la parenthese 2 recursion differentes
		generate_balanced(str, index + 1, left_rem, right_rem, pair + 1, buffer, buffer_index + 1);
	}
	else if (str[index] == ')')
	{
		if (right_rem > 0) // si 
		{
			buffer[buffer_index] = ' '; // on test en enlevant la parenthese 
			generate_balanced(str, index + 1, left_rem, right_rem - 1, pair, buffer, buffer_index + 1);
		}
		if (pair > 0)
		{
			buffer[buffer_index] = ')';
			generate_balanced(str, index + 1, left_rem, right_rem, pair - 1, buffer, buffer_index + 1);
		}
	}
	else
	{
		buffer[buffer_index] = str[index];
		generate_balanced(str, index + 1, left_rem, right_rem, pair, buffer, buffer_index + 1);
	}
}

void remove_invalid_parentheses(char *str)
{
	int	i;
	int	left_rem;
	int	right_rem;
	int	len;

	i = 0;
	left_rem = 0;
	right_rem = 0;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			left_rem++;
		else if (str[i] == ')')
		{
			if (left_rem > 0)
				left_rem--;
			else
				right_rem++;
		}
		i++;
	}
	char	buffer[len + 1];  // Declare buffer based on the length of the input string
	generate_balanced(str, 0, left_rem, right_rem, 0, buffer, 0);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		puts("Usage: ./rip <parentheses_string>");
		return (1);
	}
	remove_invalid_parentheses(argv[1]);
	return (0);
}