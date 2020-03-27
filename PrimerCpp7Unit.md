###	Primer C++ 第7章 类
####  类
```C++
Sales_data add(const Sales_data&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);

class Sales_data{
public:
	//构造函数
	/*通过在参数列表后面写上 = default 来要求编译器生成构造函数。 = default 既可以和声明一起出现在类的内部，也可以作为定义出现在类的外部。
	和其他函数一样，如果 = default 在类的内部，则默认构造函数是内联的；如果它在类的外部，则该成员默认情况下不是内联的*/
	Sales_data() = default;
	//构造函数初始值列表
	Sales_data(const std::string& s):bookNo(s){}
	Sales_data(const std::string& s, unsigned num, double price):bookNo(s), units_sold(num), revenue(num*price){}
	Sales_data(Std::istream& in);
	std::string isbn() const{return bookNo;}
    Sales_data& combine(const Sales_data& );
	
private:
    double avg_price() const;
    std::string bookNo;			//ISBN编号
    unsigned units_sold = 0;	//某书的销量
    double revenue = 0.0;		//表示这本书的总销售收入
	
	//友元
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
};


Sales_data::Sales_data(Std::istream& in){
	//read(in, *this);
	double price = 0;
	in >> bookNo >> units_sold >> price;
	revenue = price * this->units_sold;
}

//在类外部定义成员函数
online double Sales_data::avg_price() const{
	if(units_sold){
		return revenue/units_sold;
	}
	else
		return 0;
}
//定义一个返回this对象的函数
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

//输入的交易信息包括ISBN、售出总数和售出价格
std::istream &read(std::istream& in, Sales_data& item){
	double price = 0;
	in >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;	
}
std::ostream &print(std::ostream& out, const Sales_data& item){
	out << "编号为" << item.isbn() << "的书，每本售价是" << item.units_sold << "元，总销售收入是" 
	<< item.revenue << "元，平均价格是" << item.avg_price();
	return out;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs){
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

```

**顶层const**
```C++
用名词顶层const表示指针本身是一个常量，而用名词底层const表示指针所指的对象是一个常量。
```

**const 成员函数**
```C++
紧跟参数列表之后的const关键的作用是修改隐式this指针的类型。
从const成员函数返回*this
一个const成员函数如果以引用的形式返回*this，那么它的返回类型将是常量引用。
```

**构造函数**
```C++
类可以包含多个构造函数，和其他重载函数差不多，不同的构造函数之间必须在参数数量或参数类型上有所区别。
不同于其他成员函数，构造函数不能被声明成从const的。
构造函数的初始值有时必不可少
	如果成员是const或者是引用的话，必须将其初始化。当成员属于某种类类型且该类型没有定义默认构造函数时，也必须将这个成员初始化。
	如果成员是const、引用，或者属于某种未提供默认构造函数的类类型，我们必须通过构造函数初始值列表为这些成员提供初值。
成员初始化的顺序
	成员的初始化顺序与它们在类定义中的出现顺序一致。构造函数初始值列表中初始值的前后位置关系不会影响实际的初始化顺序。
	注意：如果使用一个成员来初始化另外一个成员的话，这时候顺序就很关键。为了安全，尽量避免使用某些成员初始化其他成员。
```
	
使用struct 和 class 定义类的唯一区别就是默认的访问权限。
	

**友元**
```C++
类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的函数声明。
友元不是类的成员也不受它所在区域访问控制级别的约束。
类之间的友元关系
如果一个类指定了友元类，则友元类的成员函数可以访问此类包括非公有成员在内的所有成员。
```

**定义一个类型成员(别名)**
```C++
typedef std::string::size_type pos;
using pos = std::string::size_type;
```

**内联函数online**
```C++
内联函数可避免函数调用的开销
```

**可变数据成员**
```C++
一个可变数据成员永远不会是const，即使它是const对象的成员。
通过在变量的声明中使用mutable关键字。
```

**类的声明**
```C++
class 类名;			//有时也称为前向声明
```

**关键字explicit: 防止隐式转换**
```C++
关键字 explicit 只对一个实参的构造函数有效。需要多个实参的构造函数不能用于执行隐式转换，所以无需将这些构造函数指定为explicit的。只能在类内声明构造函数时使用 explicit 关键字，在类外部定义时不应重复。
```

**常量表达式**
```C++
常量表达式是指值不会改变并且在编译过程中就能得到计算结果的表达式。
```

**constexpr变量**
```C++
C++11新标准规定，允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式。
声明为 constexpr 的变量一定是一个常量，而且必须用常量表达式初始化：
	constexpr int mf = 20;			//20是常量表达式
	constexpr int limit = mf + 1;	//mf + 1 是常量表达式
	constexpr int sz = size();		//只有当size是一个constexpr函数时才是一条正确的声明语句
```

**constexpr 函数**
```C++
constexpr函数是指能用于常量表达式的函数。
constexpr函数必须遵循：函数的返回类型及所有形参的类型都得是字面值类型，而且 函数体中必须有且只有一条return语句。
```

**类的静态成员**
```C++
类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。
静态成员函数不与任何对象绑定在一起，它们不包含this指针。作为结果，静态成员函数不能声明成const的，而且我们也不能在static函数体内使用this指针。
静态数据成员不属于类的任何一个对象，所以它们并不是在创建类的时候被定义的。这意味着它们不是由类的构造函数初始化的。而且一般来说，我们不能在类的内部初始化静态成员。

class Account{
public:
	void calculate(){amount += amount * interesRate;}
	static double rate(){return interestRate;}
	static void rate(double);
private:
	std::string owner;
	double amount;
	static double interestRate;
	static double initRate();
	//静态数据成员的类内初始化
	static constexpr int period = 30;
	double daily_tbl[pariod];
};
//在类外定义静态成员时，不能重复static关键字，该关键字只出现在类内部的声明语句
void Account::rate(double newRate){
	interestRate = newRate;
}

//定义并初始化一个静态成员
double Account::interestRate = initRate();
```
静态成员能用于某些场景，而普通成员不能
```C++
静态成员独立于任何对象。
静态成员可以是不完全类型。静态数据成员的类型可以是它所属的类类型。二非静态数据成员则受到限制，只能声明它所属类指针或引用：
class Bar{
public:
	//...
private:
	static Bar mem1;	//正确：静态成员可以是不完全类型
    Bar *mem2;			//正确：指针成员可以是不完全类型
	Bar mem3;			//错误：数据成员必须是完全类型
};

静态成员和普通成员的另一个区别是我们可以使用静态成员作为默认实参：
class Screen{
public:	
	Screen clear(char = bkground);
private:
	static const char bkground;
};

非静态数据成员不能作为默认实参，因为它的值本身数据对象的一部分，这么做的结果是无法真正提供一个对象以便从中获取成员的值，最终将引发错误。
```

**单例模式**
```C++
class simplePattern{
private:
	simplePattern(){}
	simplePattern(const simglePattern& ){}
	static simplePattern* simgle;
public:
	static simplePattern* getInstance(return simple;)
};
simplePattern simplePattern::simgle = new simplePattern;
```


**调试帮助**
```C++
assert预处理宏
	assert宏使用一个表达式作为它的条件：assert(expr);首先对expr求值，如果表达式为假(0)，assert输出信息并终止程序的执行。如果表达式为真(非0),assert什么也不做。
NDEBUG预处理变量
	```
	void print(const int ia[], size_t size){
	#ifndef NDEBUG
		cerr << __func__ << ":array size is " << size << endl;
	#endif
	}
	```
	__func__ 是编译器定义的一个局部静态变量，用于存放函数的名字
	__FILE__ 存放文件的字符串字面值
	__LINE__ 存放当前行号的整形字面值
	__TIME__ 存放文件编译器时间的字符串字面值
	__DATE__ 存放文件编译日期的字符串字面值
```


```C++
//令成员函数作为友元
class Windows{
public:
	void clear();
}；
class Screen{
	friend void Windows::clear();
private:
	std::string name;
};

void Windows::clear(){
	//TODO
	name = '';
}
```







