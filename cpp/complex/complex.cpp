#include <stdio.h>
#include<iostream.h>

class Complex
{
private:
	int real;
	int imag;
public:
	static int cnt;
	Complex();
	Complex(int r, int i);
	Complex operator=(Complex& c);
	Complex operator++();
	Complex operator++(int);
	Complex operator--();
	Complex operator--(int);
	Complex operator-(Complex c1);
	Complex operator+(Complex b);
	void input();
	void display();
	void setReal(int r);
	int getReal();
	int getImag();
	void setImag(int i);
	Complex product(Complex a);

	friend Complex operator+(Complex c ,int n);
	friend Complex operator+(int n,Complex c);
	friend ostream& operator<<(ostream& out,Complex& c);
	friend istream& operator>>(istream& in,Complex& c);
};
Complex::Complex()
{
	this->real=0;
	this->imag=0;
	cnt++;
}
Complex::Complex(int r, int i)
{
	this->real=r;
	this->imag=i;
	cnt++;
}
ostream& operator<<(ostream& out,Complex& c)
{
	out<<"Real : "<<c.real<<"  Imaginary : "<<c.imag<<endl;
	return out;
}
istream& operator>>(istream& in,Complex& c)
{
	in>>c.real>>c.imag;
	return in;
}
Complex Complex::operator=(Complex& c)
{
	this->real = c.real;
	this->imag = c.imag;
	return c;
}

Complex Complex::operator++()/*Pre*/
{
	real++;
	imag++;
	return *this;/*This gives new copy of object and return it*/
}
Complex Complex::operator++(int)/*Post*/
{
	Complex temp = *this;
	real++;
	imag++;
	return temp;
}
Complex Complex::operator--()/*Pre*/
{
	real--;
	imag--;
	return *this;/*This 1st dcr then  return new copy of object */
}
Complex Complex::operator--(int)/*Post*/
{
	Complex temp = *this;
	real--;
	imag--;
	return temp;
}
Complex Complex::operator-(Complex c1)
{
	Complex temp;
	temp.real = real - c1.real;
	temp.imag = imag - c1.imag;
	return temp;
}
void Complex::input()
{
	printf("\nEnter real and imag : ");
	scanf("%d%d", &real, &imag);
}
void Complex::display()
{
	printf("\nreal = %d   imag = %d\n", this->real, this->imag);
}
Complex Complex::operator+(Complex b)
{
	Complex c;
	c.real = this->real + b.real;
	c.imag = this->imag + b.imag;
	return c;
}	
void Complex::setReal(int r)
{
	real = r;
}
int Complex::getReal()
{
	return real;
}
int Complex::getImag()
{
	return imag;
}
void Complex::setImag(int i)
{
	imag = i;
}
Complex Complex::product(Complex a)
{
	Complex  c;
	c.real = (this->real * a.real) - (this->imag * a.imag);
	c.imag = (this->imag * a.real) + (this->real * a.imag);
	return c;
}
int Complex::cnt = 0;

Complex subtract(Complex a, Complex b)
{
	Complex c;
	c.setReal( a.getReal() - b.getReal() );
	c.setImag( a.getImag() - b.getImag() );
	return c;
}
		
Complex operator+(Complex c ,int n)
{
	Complex temp;
	temp.real = c.real + n;
	temp.imag = c.imag;
	return temp;
}
Complex operator+(int n,Complex c )
{
	Complex temp;
	temp.real = c.real + n;
	temp.imag = c.imag;
	return temp;
}

void main()
{
	Complex c2(5,3),c3(15,10);
	printf("\nCount is %d \n",Complex::cnt);
	/*c1.input();
	c2.input();
	c1.display();
	c2.display();
	c3 = c1.sum(c2);
	printf("\nSum is : ");
	c3.display();
	c3 = subtract(c1,c2);
	printf("\nSubtraction is : ");
	c3.display();
	c3 = c1.product(c2);
	printf("\nProduct is : ");
	c3.display();*/
	Complex c1(12,10);
	//c3 = --c1;
	//c3 = c2 = c1;
/*	c1.display();
	c2.display();
	c3.display();*/
	//cin>>"Enter for c1";
	cin>>c1;
	//cin>>"Enter for c2";
	cin>>c2;
	cout<<c1<<c2<<endl;

}
