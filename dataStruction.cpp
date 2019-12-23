//线性表----数组描述

/**********************arrayList的实现***********************/
template <typename T>
class linearList{
public:
	virtual ~linearList(){}
	//当且仅当元素为空时返回true
	virtual bool empty() const = 0;
	//返回线性表的元素个数
	virtual int size() const = 0;
	//返回索引为theIndex的元素
	virtual T& get(const int theIndex) const = 0;
	//返回元素theElement第一次出现的索引
	virtual int indexOf(const T& theElement) const = 0;
	//删除索引为theIndex的元素
	virtual void erase(int theIndex) = 0;
	//在theIndex位置插入元素theElement
	virtual void insert(int theIndex, const T& theElement) = 0;
	//把线性表插入输出流
	virtual void output(ostream& out) const = 0;
};


template <class T>
void changeLengthID(T* &a, int oldLength, newLength){
	if(newLength < 0){
		throw illegalParameterValue("new length must be >= 0")
	}
	
	T* temp = new[newLength];
	int number = min(oldLength, newLength);
	copy(a, a+number, temp);
	delete [] a;
	a = temp;
}





template <class T>
class arrayList:public linearList<T>{
public:
	//构造函数、复制构造函数和析构函数
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList(){delete [] element;}
	
	//ADT方法
	bool empty() const {return arrayLength == 0;}
	int size() const {return listSize;}
	T& get(const int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	
	class iterator;
	iterator begin(){return iterator(element);}
	iterator end(){return iterator(element + listSize);}
	
protected:
	//若索引theIndex无效,则抛出异常
	void checkIndex(int theIndex) const;
	
	T* element;			//存储线性表元素的一维数组
	int arrayLength;	//一维数组的容量
	int listSize;		//线性表元素个数
}

template <class T>
arrayList<T>::arrayList(int initialCapacity = 10)
{
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial Capacity = " << initialCapacity << "Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList){
	arrayLength = theList.arrayLength;
	listSize = theList.arrayList;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex >= listSize){
		ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalParameterValue(s.str());
	}
}

template<class T>
int arrayList<T>::indexOf(const T& theElement){
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	if(theIndex == listSize){
		return -1;
	}
	else{
		return theIndex;
	}
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	
	copy(element + theIndex + 1, element + listSize, element + theIndex);
	
	element[--listSize].~T();		//调用析构函数(free(element + listSize - 1);)
	
	//如果数组元素减少时释放一半的数组空间
	if(listSize < arrayLength/4)
	{
		element[arrayLength + arrayLength/2].~T();	
	}
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex < 0  || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " <<< theIndex << "size = " << listSize;
		throw illegalParameterValue(s.str());
	}
	
	if(listSize == arrayLength)
	{
		//数组空间已满,数组长度倍增
		changeLengthID(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void arrayList<T>::output(cout->out) const
{
	copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
	x.outport(out);
	return out;
}

//从[start, end)复制到[to, to + end - start)
template<class iterator>
void copy(iterator start, iterator end, iterator to){
	while(start != end){
		*to = *start;
		start++;
		to++;
	}
}




//类ArrayList的一个迭代器
class iterator
{
public:
	//用C++的typedef实现双向迭代器
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	
	//构造函数
	iterator(T* thePosition = 0){position = thePosition;}
	
	//解引用操作
	T& operator*()const {return *position;}
	T* operator->() const{return &*position;}
	
	//迭代器的值增加 
	iterator& operator++(){++position; return *this;}	//前加
	iterator operator++(int)							//后加
	{
		iterator old = *this;
		++position;
		return old;
	}
	
	//迭代器的值减少
	iterator& operator--(){--position; return *this;}
	iterator operator--(int)
	{
		iterator old = *this;
		--position;
		return old;
	}
	
	//测试是否相等
	bool operator!=(const iterator right) const{return position != right.position;}
	bool operator ==(const iterator right)const{return position == right.position;}
	
protected:
	T* position;		//指向表元素的指针
}





/********************vector的实现****************/
template <typename T>
class vectorList: public linearList<T>
{
public:
	//构造函数、复制构造函数和析构函数
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList(){delete element;}

	//ADT 方法
	bool empty() const {return element->empty();}
	int size() const {return static_cast<int>(element->size());}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	
	//增加的方法
	int capacity() const {return (int)element->capacity();}
	
	//线性表的起始和结束位置的迭代器
	typedef typename vector<T>::iterator iterator;
	iterator begin(){return element->begin();}
	iterator end(){return element->end();}
	
protected:
	void checkIndex(index theIndex) const;
	vector<T>* element;		//存储线性表元素的向量 
}

template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
	if(initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial Capacity = " << initialCapacity << " Must be > 0"
		throw illegalParameterValue(s.str());
	}
	//创建容量为0的向量
	element = new vector<T>;
	//vector容量从0增加到initialCapacity
	element->reserve(initialCapacity);
}

template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
	element = new vector<T>(*theList.element);
}

template<class T>
void vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex< 0 || theIndex > size())
	{
		ostringstream s;
		s << "index = " << theIndex << "size = " << size();
		throw illegalParameterValue(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}





/*******************线性表----链式描述*******************/
template <class T>
struct chainNode{
	//数据成员
	T element;
	chainNode<T>* next;
	
	//方法
	chainNode(){}
	chainNode(const T& const){this->element = element;}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};


template<class T>
class chain:public linearList<T>
{
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain(){};
	
	//抽象数据类型ADT的方法
	bool empty() const{return listSize == 0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theElement);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	
protected:
	void checkIndex(int theIndex) const;

	chainNode<T>* firstNode;
	int listSize;
};

template<class T>
chian<T>::chian(int initialCapacity){
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = NULL;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	//链表theList为空
	if(listSize == 0)
	{
		firstNode = NULL;
		return;
	}
	
	//链表theList非空
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	
	while(sourceNode != NULL){
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;	//链表结束
}

template<class T>
chain<T>::~chian()
{
	while(firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
T&chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	
	chainNode<T>* currentNode = firstNode;
	for(int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const{
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while(currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		index++;
	}
	if(currentNode == NULL)
		return -1;
	else
		return index;
}

template<class T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	
	chianNode<T>* deleteNode;
	if(theIndex == 0){
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else{
		chianNode<T>* pNode = firstNode;
		for(int i = 0; i < index-1; i++)
		{
			pNode = pNode->next;
		}
		deleteNode = pNode->next;
		pNode->next = pNode->next->next;
	}
	listSize--;
	delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex < 0 || theIndex > listSize){
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalParameterValue(s.str());
	}
	
	if(theIndex == 0){
		//在链表头插入
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else{
		//寻找新元素的前驱
		chainNode<T>* pNode = firstNode;
		for(int i = 0; i < theIndex - 1; i++)
		{
			pNode = pNode->next;
		}
		pNode->next = new chainNode<T>(theElement, pNode->next);
	}
	listSize++;
}

template<class T>
void chain<T>::output(ostream& out) const
{
	for(chainNode<T>* currentNode = firstNode; 
					  currentNode != NULL; 
				      currentNode = currentNode->next)
	{
		out << currentNode->element << "  ";
	}
}

template<class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}

class iterator
{
public:
	
}





/****************二叉树的链表描述*******************/
template<typename T>
struct binaryTreeNode{
	T element;
	binaryTreeNode<T> *leftChild, *rightChild;
	
	binaryTreeNode() {leftChild = rightChild = nullptr;}
	binaryTreeNode(const T& theElement){
		element(theElement);
		leftChild = rightChild = nullptr;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild){
		element(theElement);
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

//前序遍历
template<class T>
void preOrder(binaryTreeNode<T>* t){
	if(t != nullptr)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

//中序遍历递归实现
template<class T>
void inOrder(binaryTreeNode<T>* t){
	if(t != nullptr)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}
//中序遍历的非递归实现
void inOrder2(binaryTreeNode<T>* t){
	stack<binaryTreeNode<T>*> InStack;
	binaryTreeNode<T>* node = t;
	while(node || !InStack.empty())
	{
		while(node){
			InStack.push(node);
			node = node->leftChild;
		}
		if(!InStack.empty()){
			node = InStack.top();
			InStack.pop();
			visit(node);
			node = node->rightChild;
		}
	}
}

//后续遍历
template<class T>
void inOrder(binaryTreeNode<T>* t){
	if(t != nullptr)
	{
		inOrder(t->leftChild);
		inOrder(t->rightChild);
		visit(t);
	}
}

//层次遍历，使用队列实现
template<class T>
void leverOrder(binaryTreeNode<T>* t){
	queue<binaryTreeNode<T>*> LeverQueue;
	binaryTreeNode<T>* node = t;
	
	while(node){
		visit(node);
		
		if(node->leftChild){
			LeverQueue.push(node->leftChild);
		}
		if(node->rightChild){
			LeverQueue.push(node->rightChild);
		}
		try{
			node = LeverQueue.front();
		}
		catch(LeverQueue.empty()){
			return;
		}
		LeverQueue.pop();
	}
}

template<class T>
void visit(binaryTreeNode<T>* x)
{
	cout << x->element << " ";
}



/******************抽象数据类型BinaryTree******************/
template<class T>
class binaryTree{
public:
	virtual ~binaryTree(){}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void (*) (T*)) = 0;
	virtual void inOrder(void (*) (T*)) = 0;
	virtual void postOrder(void (*) (T*)) = 0;
	virtual void leverOrder(void (*) (T*)) = 0;
};

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>{
public:
	linkedBinaryTree(){root = nullptr; treeNodeSize = 0;}
	~linkedBinaryTree(){erase();}
	int height(binaryTreeNode<E>*);
	bool empty() const {return treeNodeSize == 0}
	int size() const {return treeNodeSize;}
	void preOrder(void (*theVisit)(binaryTreeNode<E>*)){
		visit = theVisit; preOrder(root);
	}
	void inOrder(void (*theVisit)(binaryTreeNode<E>*)){
		visit = theVisit; inOrder(root);
	}
	void postOrder(void (*theVisit)(binaryTreeNode<E>*)){
		visit = theVisit;
		postOrder(root);
	}
	void leverOrder(void(*)(binaryTreeNode<E> *));
	void erase(){
		postOrder(dispose);
		root = nullptr;
		treeNodeSize = 0;
	}
	
	void preOrderOutput(){
		preOrder(output);
		cout << endl;
	}
	
	int height() const {return height(root);}
	
	
private:
	binaryTreeNode<E>* root;
	int treeNodeSize;
	
	static void (*visit)(binaryTreeNode<E>* );
	static void preOrder(binaryTreeNode<E> *t);
	static void inOrder(binaryTreeNode<E> *t);
	static void postOrder(binaryTreeNode<E>* t);
	static void dispose(binaryTreeNode<E>* t) {delete t};
	
	static void output(binaryTreeNode<E>* t){
		cout << t->element << " ";
	}
};

//私有前序遍历方法
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t)
{
	if(t != nullptr){
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t)
{
	if(t == NULL)
		return 0;
	int hl = height(t->leftChild);
	int hr = height(t->rightChild);
	if(hl > hr)
	{
		return ++hl;
	}
	else
		return ++hr;
}





















































