int gcd(int a, int b)
{
	int temp;
	if(a>b)
	{
		while(a%b != 0)
		{
			temp = a;
			a = b;
			b = temp%b;
		}
		return (b);
	}
	else
	{
		while(b%a != 0)
		{
			temp = b;
			b = a;
			a = temp%a;
		}
		return (a);
	}
}