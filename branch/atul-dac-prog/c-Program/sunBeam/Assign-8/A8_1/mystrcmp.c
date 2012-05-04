int mystrcmp(char *p, char *q)
{
	while(*p == *q  && *p != '\0')
	{
		p++;
		q++;
	}
	  return (*p - *q);
}