 int fact(int p)
 {
	int a;
	if(p == 0)
		return 1;	
	a = p * fact(p - 1);
	return(a);
 }