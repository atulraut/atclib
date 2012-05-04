#include<stdio.h>
#include<iostream.h>
#include<string.h>
class string		/* Declaration of class */
{
private :
		int len;
		char *buff;
public :
	string();
	string(char *);
	string(string& aa);
	int getlength();
	void display();
	string operator=(string& s1);
	void input();
	~string();
};
string::string()			/*Implementation of class*/
{
	len = 0;
	buff = new char[len + 1];
	strcpy(buff, "");
}
string::string(char *str)	/*Parameterized Constructor*/
{
	len = strlen(str);
	buff = new char[len + 1];
	strcpy(buff, str);
}
string::string(string& str)
{
	len = str.len;
	buff = new char[len + 1];
	strcpy(buff, str.buff);
}
string::~string()
{
	delete[] buff; 	
}
string string::operator=(string& s1)
{
	 len = s1.len;
	 delete[] buff;
	 buff = new char[len+1]; 
	 strcpy(buff, s1.buff);
	 return s1;
}
		
int string::getlength()
{
	return len;
}
void string::input()
{
	char str[80];
	cout<<"Input String"<<endl;
	cin>>str;
	len = strlen(str);
	delete[] buff;
	buff = new char[len +1];
	strcpy(buff, str);
}
void string::display()
{
	cout<<buff<<endl;
}
void main()			/* Main function using class */
{
//	int val;	
	string s1("Atuloiyuiouio");
	string s2("ooppooppoopoo");
	string s3("");
	//s1.display();
	//s2.display();
//	string s2(s1);
/*al = s2.getlength();
	cout<<"Length of string is = ";
	cout<<val<<endl;*/
	s3 = s2 = s1;
	s1.display();
	s2.display();
	s3.display();
}