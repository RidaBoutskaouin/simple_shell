#include "shell.h"


/*
 * isValidNumber - Checks if a string is a valid number
 * @str: The string to be checked
 * Return: 1 if the string is a valid number, 0 otherwise
*/

int isValidNumber(const char *str)
{
	if ((*str >= '0' && *str <= '9'))
	{
		str++;
		while (*str)
		{
			if (*str < '0' || *str > '9')
				return 0;
			str++;
		}
		return 1;
	}
	return 0;
}