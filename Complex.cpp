#include <iostream>
#include <cmath>

class Complex{
public:
	Complex(double real = 0.0, double imag = 0.0):m_real(real), m_imag(imag){}
	
public://运算符重载
	//以全局函数的形式重载
	friend Complex operator+(const Complex& c1, const Complex& c2);
	friend Complex operator-(const Complex& c1, const Complex& c2);
	friend Complex operator*(const Complex& c1, const Complex& c2);
	friend Complex operator/(const Complex& c1, const Complex& c2);
	friend bool operator==(const Complex& c1, const Complex& c2);
	friend bool operator!=(const Complex& c1, const Complex& c2);
	friend istream& operator>>(istream& in, Complex& A);
	friend istream& operator<<(istream& in, Complex& A)
	//以成员函数的形式重载
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);
	

public:
	double real() const{return m_real;}
	double imag() const{return m_imag;}
	
private:
	double m_real;
	double m_imag;
}


istream& Complex::operator>>(istream& in, Complex& A){
	in >> A.m_real >> A.m_imag;
	return in;
}
	
ostream& Complex::operator<<(ostream& out, Complex& A){
	out << A.m_real << " + " << A.m_imag << "i";
	return out;
}


//重载new和delete运算符
//以成员函数的形式重载
void* className::operator new(size_t size){
	//TODO
}
void className::operator new(void* ptr){
	//TODo
}

//以全局函数的形式重载
void* operator new(size_t size){
	//TODO
}
void operator new(void* ptr){
	//TODO
}


/*友元函数和友元类
友元函数：在定义类的时候可以将全局函数、其他类的成员函数等定义为类的友元函数，这样在友元函数内部就可以访问该类对象的私有成员了。
友元类：一个类A可以将另一个类B声明为自己的友元，类B的所有成员函数就都可以访问类A对象的私有成员。
注意：	1、友元关系在类之间不能传递。
		2、友元函数不能被继承。*/







































