#include "shell.h"

/*
 * _strchr - locate character in string
 * @str: The string to be searched
 * @c: The character to search for
 * Return: a pointer to the first occurrence
 * of the character c in the string str,
 * or NULL if the character is not found.
 */

char *_strchr(char *str, char c)
{
	int i = 0;

	while (str[i] != '\0') { 
		if (str[i] == c)
			return &str[i]; 
		i++;
	}

	if (str[i] == c)
		return &str[i];

	return NULL;
}


/*
 * _strtok - extract tokens from strings
 * @str: The string to be searched
 * @seps: The string containing the delimiters
 * Return: a pointer to the next token found in str,
 * or NULL if there are no more tokens.
 */

char *_strtok(char *str, char *seps)
{
	static char *pNext = NULL;
	char *pRet = NULL;
	int i = 0;

	if (str != NULL)
		pNext = str;
	
	if (pNext == NULL)
		return NULL;

	pRet = pNext;

	while (pNext[i] != '\0') {
		if (_strchr(seps, pNext[i]) != NULL) {
			pNext[i] = '\0';
			pNext = &pNext[i+1];
			return pRet;
		}
		i++;
	}

	if (pNext[i] == '\0') {
		pNext = NULL;
		return pRet;
	}

	return NULL;
}
