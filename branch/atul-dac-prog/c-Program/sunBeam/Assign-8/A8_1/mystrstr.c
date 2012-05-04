
char * mystrstr(char *p1,char *p2)
{
	char *p3 = p2;
	char *p4 = p1;
	int flag;;
	while(*p1 != '\0')
	{
		flag = 0;
		while(*p2 == *p1 && *p1 != '\0')
		{
			if(flag==0)
				p4 = p1;
			p1++;
			p2++;
			flag++;
		}
		if(*p2 == '\0')
			return 	p4;
		else
			p2 = p3;
		p1++;
	}
	return 0;
}