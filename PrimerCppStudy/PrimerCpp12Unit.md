### Primer C++ 第12章动态内存
```
静态内存用来保存局部static对象、类static数据成员以及定义在任何函数之外的变量。
栈内存用来保存定义在函数内的非static对象。
分配在静态或栈中的对象由编译器自动创建和销毁。
```

####    动态内存与智能指针
智能指针的行为类似常规指针，重要的区别是它负责自动释放所指向的对象。
新标准库提供的这两种智能指针区别在于管理底层指针的方式：share_ptr允许多个指针指向同一个对象；unique_ptr则“独占”所指向的对象。
标准库还定义了一个名为weak_ptr的伴随类，它是一种弱引用，指向share_ptr所管理的对象。这三种类型都定义在memory头文件中。

操作 | shared_ptr和unique_ptr都支持的操作
--- | ---
`shared_ptr<T> sp; unique_ptr<T> up;` | 空智能指针，可以指向类型为T的对象
p   |   将p用作一个条件判断，若p指向一个对象，则为true
*p  |   解引用p，获得它指向的对象
`p->mem`  |   等价于(*p).mem
`p.get()` |   返回p中保存的指针。要小心使用，若智能指针释放了其对象，返回的指针所指向的对象也就消失了
`swap(p, q);  p.swap(q);`   |   交换p和q中的指针

操作 | share_ptr所独有的操作
--- | ---
`make_shared<T>(args)`    |    返回一个shared_ptr,指向一个动态分配的类型为T的对象。使用args初始化此对象
`shared_ptr<T>p(q)`   |   p是shared_ptr q 的拷贝；此操作会递增q中的计数器。q中的指针必须能转换为T*
p = q   |   p和q都是shared_ptr,所保存的指针必须能相互转换。此操作会递减p的引用计数，递增q的引用计数；若p的引用计数变为0，则将其管理的原内存释放
`p.unique()` | 若p.use_count()为1，返回true；否则返回false
`p.use_count()` | 返回与p共享对象的智能指针数量；可能很慢，只要用于调试


**share_ptr类**
```
智能指针也是模板。当我们创建一个智能指针时，必须提供指针可以指向的类型。
share_ptr<string> p1; 
share_ptr<list<int>> p1;

make_shared函数
shared_ptr<int> p3 = make_shared<int>(42);  //指向一个值为42的int的shared_ptr
share_ptr<string> p4 = make_shared<string>(10, '9');  //指向一个值为“9999999999”的string
share_ptr<int> p5 = make_shared<int>();               //指向一个值初始化的int，值为0
为了方便还可以使用auto：
auto p6 = make_shared<vector<string>>();

shared_ptr的拷贝与赋值
当进行拷贝或赋值操作时，每个shared_ptr都会记录有多少个其他shared_ptr指向相同的对象：
auto p = make_shared<int>(42);  //p指向的对象只有p一个引用者。
auto q(p);                      //p和q指向相同的对象，此对象有两个引用者。

auto r = make_shared<int>(42);  //r指向的int只有一个引用者
r = q;                          //给r赋值，令它指向另一个地址
                                //递增q指向的对象的引用计数
                                //递减r原来指向的对象的引用计数
                                //r原来指向的对象已没有引用者，会自动释放



```






