void strdel(char *str, char ch ,char *p)
{
	int i=0;
	while(*str != '\0')
	{

		if(*str == ch)
		{
			str++;
			continue;
		}
		p[i] = *str;
		str++;
		i++;
	}
	p[i] = '\0';
}