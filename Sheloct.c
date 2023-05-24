char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t m);
/**
 * _strchr - string finder
 * @str: string to be found
 * @c: parameter
 * Return: character parameter
 */
char *_strchr(char *str, char c)
{
	int dex;

	for (dex = 0; str[dex]; dex++)
	{
		if (str[dex] == c)
			return (str + dex);
	}
	return (NULL);
}

/**
 *  _strspn - function for substrings
 *  @str: string to be found
 *  @accept: measurable string
 *  Return: b always
 */
int _strspn(char *str, char *accept)
{
	int dex, b = 0;

	while (*str)
	{
		for (dex = 0; accept[dex]; dex++)
		{
			if (*str == accept[dex])
			{
				b++;
				break;
			}
		}
		str++;
	}
	return (b);
}

/**
 * _strcmp - checks two strings
 * @str1: string 1
 * @str2: string 2
 * Return: 0 always
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - checks two strings
 * @str1: string 1
 * @str2: string 2
 *  @m: parameter
 * Return: 0 always
 */
int _strncmp(const char *str1, const char *str2, size_t m)
{
	size_t j;

	for (j = 0; str1[j] && str2[j] && j < m; j++)
	{
		if (str1[j] > str2[j])
			return (str1[j] - str2[j]);
		else if (str1[j] < str2[j])
			return (stt1[j] - str2[j]);
	}
	if (j == m)
		return (0);
	else
		return (-15);
}
