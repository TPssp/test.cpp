#include <iostream>
using namespace std;

// 栈区：
// ​由编译器自动分配释放, 存放函数的参数值,局部变量等
// ​注意事项：不要返回局部变量的地址，栈区开辟的数据由编译器自动释放
#if 0
int *func()
{
    int a=10;
    return &a;
}

int main()
{
    int *p = func();
    cout<<*p<<endl;
    return 0;
}
#endif

// 堆区：
// ​ 由程序员分配释放,若程序员不释放,程序结束时由操作系统回收
// ​ 在C++中主要利用new在堆区开辟内存
#if 0
int * func()
{
    int *a = new int(10);
    return a;
}
int main()
{
    int *p = func();
    cout<<*p<<endl;
    return 0;
}
#endif

// 1.3 new操作符
// ​ C++中利用new操作符在堆区开辟数据
// ​ 堆区开辟的数据，由程序员手动开辟，手动释放，释放利用操作符 delete
// ​ 语法： new 数据类型
// ​ 利用new创建的数据，会返回该数据对应的类型的指针

// 示例1： 基本语法
#if 0
int* func()
{
	int* a = new int(10);
	return a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;

	//利用delete释放堆区数据
	delete p;

	//cout << *p << endl; //报错，释放的空间不可访问(不报错，但每次值不一样)

	return 0;
}
#endif

// 示例2：开辟数组
#if 0
int main()
{
    int *arr = new int[10];

    for (int i=0;i<10;i++)
    {
        arr[i]=i+1;
    }

    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<endl;
    }

    //释放数组 delete 后加 []
    delete[] arr;

    return 0;
}
#endif

/* 2 引用

2.1 引用的基本使用
**作用： **给变量起别名

语法： 数据类型 &别名 = 原名

示例：*/
#if 0
int main() {

	int a = 10;
	int &b = a;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	b = 100;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;


	return 0;
}
#endif

// 2.2 引用注意事项
// 引用必须初始化
// 引用在初始化后，不可以改变
// 示例：
#if 0
int main() {

	int a = 10;
	int b = 20;
	//int &c; //错误，引用必须初始化
	int &c = a; //一旦初始化后，就不可以更改
	c = b; //这是赋值操作，不是更改引用

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;


	return 0;
}
#endif

// 2.3 引用做函数参数
// **作用：**函数传参时，可以利用引用的技术让形参修饰实参

// **优点：**可以简化指针修改实参

// 示例：
#if 0
//1. 值传递
void mySwap01(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

//2. 地址传递
void mySwap02(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//3. 引用传递
void mySwap03(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {

	int a = 10;
	int b = 20;

	mySwap01(a, b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap02(&a, &b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap03(a, b);
	cout << "a:" << a << " b:" << b << endl;

	return 0;
}
// 总结：通过引用参数产生的效果同按地址传递是一样的。
// 引用的语法更清楚简单
#endif

// 2.4 引用做函数返回值
// 作用：引用是可以作为函数的返回值存在的

// 注意：不要返回局部变量引用

// 用法：函数调用作为左值

// 示例：

#if 0
//返回局部变量引用
int& test01() {
	int a = 10; //局部变量
	return a;
}

//返回静态变量引用
int& test02() {
	static int a = 20;
	return a;
}

int main() {

	//不能返回局部变量的引用
	// int& ref = test01();
	// cout << "ref = " << ref << endl;
	// cout << "ref = " << ref << endl;

	//在函数返回一个左值时，
    //为了确保返回值可以被当作左值使用，
    //必须将其返回类型声明为引用类型
	int &ref2 = test02();
	cout << "ref2 = " << ref2 << endl;

	test02() = 1000;

	cout << "ref2 = " << ref2 << endl;

	return 0;
}
#endif

// 2.5 引用的本质
// 本质：引用的本质在c++内部实现是一个指针常量

#if 0
//发现是引用，转换为 int* const ref = &a;
void func(int& ref){
	ref = 100; // ref是引用，转换为*ref = 100
}
int main(){
	int a = 10;
    
    //自动转换为 int* const ref = &a; 指针常量是指针指向不可改，也说明为什么引用不可更改
	int& ref = a; 
	ref = 20; //内部发现ref是引用，自动帮我们转换为: *ref = 20;
    
	cout << "a:" << a << endl;
	cout << "ref:" << ref << endl;
    
	func(a);
    cout<<"a:" << a <<endl;
    cout<<"ref:" << ref <<endl;
	return 0;
}
#endif

// 2.6 常量引用
// **作用：**常量引用主要用来修饰形参，防止误操作
// 在函数形参列表中，可以加const修饰形参，防止形参改变实参
#if 0
//引用使用的场景，通常用来修饰形参
void showValue(const int& v) {
    //形参v是一个常量引用，可以读取实参的值但是不能修改实参的值。
	//v += 10;
	cout << v << endl;
}

int main() {

	//int& ref = 10;  引用本身需要一个合法的内存空间，因此这行错误
	//加入const就可以了，编译器优化代码，int temp = 10; const int& ref = temp;
	const int& ref = 10;

	//ref = 100;  //加入const后不可以修改变量
	cout << ref << endl;

	//函数中利用常量引用防止误操作修改实参
	int a = 10;
	showValue(a);

	return 0;
}
#endif


// 3 函数提高
// #3.1 函数默认参数
// 在C++中，函数的形参列表中的形参是可以有默认值的。
// 语法： 返回值类型 函数名 （参数= 默认值）{}

#if 0
//如果某个位置参数有默认值，那么从这个位置往后，从左向右，必须都要有默认值
int func(int a, int b = 10, int c = 10) {
	return a + b + c;
}

//如果函数声明有默认值，函数实现的时候就不能有默认参数
int func2(int a = 10, int b = 10);//这是一个声明
int func2(int a, int b) //写成(int a = 0, int b = 0)，则编译器会认为这两个函数是不同的函数
{
	return a + b;
}

/*Specifically:
int sum(int a, int b = 0); // 函数声明中有默认参数b=0
int sum(int a = 0, int b = 0) { // 函数实现中也有默认参数，会被编译器认为是另一个函数
    return a + b;
}

int main() {
    cout << sum(1, 2) << endl; // 调用sum(int a, int b)，输出3
    cout << sum(1) << endl; // 调用sum(int a = 0, int b = 0)，输出1
    return 0;
}
*/

int main() {

	cout << "ret = " << func(20, 20) << endl;
	cout << "ret = " << func(100) << endl;
    cout<< "ret = " << func2()<< endl;

	return 0;
}
#endif


// 3.2 函数占位参数
// C++中函数的形参列表里可以有占位参数，用来做占位，调用函数时必须填补该位置

// 语法： 返回值类型 函数名 (数据类型){}

// 在现阶段函数的占位参数存在意义不大，但是后面的课程中会用到该技术
#if 1
void func(int a,int)
{
    cout<<"this is func"<<endl;
}
int main()
{
    func(10,10);
}

#endif