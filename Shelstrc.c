int _strlen(const char *c);
char *_strcpy(char *ds, const char *sc);
char *_strcat(char *ds, const char *sc);
char *_strncat(char *ds, const char *sc, size_t m);
/**
 * _strlen - function that returns a string
 * @c: pointer
 * Return: length.
 */
int _strlen(const char *c)
{
	int wen = 0;

	if (!c)
		return (wen);
	for (wen = 0; c[wen]; wen++)
		;
	return (wen);
}

/**
 * _strcpy - function to copy string
 * @ds: destination of string to be copied
 * @sc: source of string
 * Return: d always
 */
char *_strcpy(char *ds, const char *sc)
{
	size_t j;

	for (j = 0; sc[j] != '\0'; j++)
		ds[j] = sc[j];
	ds[j] = '\0';
}

/**
 * _strcat - function for strings
 * @ds: destination to string
 * @sc: source of string
 * Return: ds always
 */
char *_strcat(char *ds, const char *sc)
{
	char *dsTemp;
	const char *scTemp;

	dsTemp = ds;
	scTemp =  sc;

	while (*dsTemp != '\0')
		dsTemp++;

	while (*scTemp != '\0')
		*dsTemp++ = *scTemp++;
	*dsTemp = '\0';
	return (ds);
}

/**
 * _strncat - two strings
 * @ds: destination  to string
 * @sc: source string
 * @m: parameter count
 * Return: D's always
 */
char *_strncat(char *ds, const char *sc, size_t m)
{
	size_t ds_wen = _strlen(ds);
	size_t j;

	for (j = 0; j < m && sc[j] != '\0'; j++)
		ds[ds_wen + j] = sc[j];
	ds[ds_wen + j] = '\0';

	return (dst);
}
