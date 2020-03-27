**Prime C++ 第9章**

###  顺序容器

####    容器类型
容器类型 | 特点
--- | ---
vector | 可变大小数组；支持快速随机访问；在尾部之外的位置插入或删除元素可能很慢
deque | 双端队列；支持快速随机访问；在头尾位置插入/删除速度很快
list | 双向链表；只支持双向顺序访问；在list中任何位置进行插入/删除操作速度都很快
forward_list | 单向链表；只支持单向顺序访问；在链表任何位置进行插入/删除操作速度都很快
array | 固定大小数组；支持快速访问；不能添加或删除元素
string | 与vector相似的容器，但专门用于保存字符；随机访问快；在尾部插入/删除速度快

####    迭代器


####    容器操作
操作 | 含义
--- | ---
**类型别名** |
iterator | 此容器类型的迭代器类型
const_iterator | 可以获取元素，但不能修改元素的迭代器类型
size_type | 无符号整数类型，足够保存此种容器类型最大可能容器的大小
difference_type | 带符号整数类型，足够保存两个迭代器之间的距离
value_type | 元素类型
reference | 元素的左值类型；与value_type&含义相同
const_reference | 元素的const左值类型（即，const value_type&）
**构造函数** |
C c; | 默认构造函数，构造空容器
C c1(2); | 构造c2的拷贝c1
C c(b,e); | 构造c，将迭代器b和e指定的范围内的元素拷贝到c(array不支持)
C c{a, b, c...} | 列表初始化c
**赋值与swap** | 
c1 = c2 | 将c2中的元素替换为c2中元素
c1 = {a, b, c...} | 将c1中的元素替换为列表中的元素(不适用与array)
a.swap(b) | 交换a和b中的元素
swap(a, b) | 与a.swap(b)等价
**大小** | 
c.size() | c中元素的数目(不支持forward_list)
c.max_size() | c可保持的最大元素数目
c.empty() | 若c中存储的元素，返回false，否则返回true
**添加/删除元素(不适于array)** |
注意：在不同容器中，这些操作的接口都不同 | 
c.insert(args) | 将元素args插入c中
c.emplace(inits) | 使用inits构造c中的一个元素
c.erase(args) | 删除指定元素args
c.clear() | 删除c中的所有元素，返回void
**关系运算符** | 
==，!= | 所有容器都支持等于(不等)运算符
<，<=，>，>= | 关系运算符(无序关联容器不支持)
**获取迭代器** | 
c.bengin(), c.end() | 返回指向c的首元素和尾元素之后位置的迭代器
c.cbegin(), c.cend() | 返回const_iterator
反向迭代器的额外成员(不支持forward_list) | 
reverse_iterator | 按逆序寻址元素的迭代器
const_reverse_iterator | 不能修改元素的逆序迭代器
c.rbegin(), c.rend() | 返回指向c的尾元素和首元素之前位置的迭代器
c.crbegin(), c.crend() | 返回const_reverse_iterator


**begin和end**
```C++
list<string> a = {"love", "and", "peace"};
auto it1 = a.begin(); 		//list<string>::iterator
auto it2 = a.rbegin(); 		//list<string>::reverse_iterator
auto it3 = a.cbegin();		//list<string>::const_iterator
auto it4 = a.crbegin();		//list<string>::const_reverse_iterator
```


