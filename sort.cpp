//获取整形数组最大值
int getMaxValue(const vector<int> &array)
{
	int max = INT_MIN;
	for(auto val:array)
	{
		if(val > max)
		{
			max = val;
		}
	}
	return max;
}

//冒泡排序
void bubbleSort(vector<int> &arr, int bgn, int end)
{
	bool isLoop = true;
	for(int i = bgn; i <= end && isLoop == true; ++i)
	{
		isLoop = false;
		for(int j = bgn; j <= end - i - 1;  ++j)
		{
			if(arr[j] > arr[j+1])
			{
				swap(&arr[j], &arr[j+1]);
				isLoop = true;
			}
		}
	}
}


//选择排序
void selectSort(vector<int> &arr, int bgn, int end)
{
	for(int i = bgn; i <= end; ++i)
	{
		int indexMin = i;
		for(int j = i+1; j <= end; ++j)
		{
			if(arr[j] < arr[indexMin])
			{
				indexMin = j;
			}
		}
		if(indexMin != i)
		{
			swap(&arr[i], &arr[indexMin]);
		}
	}
}

//快速排序
//实现1
void quickSort(vector<int> &arr, int bgn, int end)
{
	if(bgn >= end)
	{
		return;
	}
	
	int lindex = bgn;
	int rindex = end;
	int std = arr[lindex];
	while(lindex < rindex)
	{
		while(lindex < rindex)
		{
			if(arr[rindex] < std)
			{
				arr[lindex++] = arr[rindex];
				break;
			}
			++rindex;
		}
		while(lindex < rindex)
		{
			if(arr[lindex] > std)
			{
				arr[rindex++] = arr[lindex];
				break;
			}
			++lindex;
		}
	}
	arr[lindex] = std;
	quickSort(arr, bgn, lindex-1);
	quickSort(arr, lindex+1, end);
}
//实现2
int Partition(int data[], int length, int start, int end){
	if(data == nulptr || length <= 0 || start < 0 || end >= length){
		throw new std::exception("Invalid Parameters");
	}
	int index = RandomInRange(start, end);	//生成一个在start和end之间的随机数
	Swap(&data[index], &data[end]);			//交换两个数字
	
	int small = start-1;
	for(index = start; index < end; ++index){
		if(data[index] < data[end]){
			++small;
			if(small != index)
				Swap(&data[index], &data[small]);
		}
	}
	
	++small;
	Swap(&data[small], &data[end]);
	
	return small;
}
void QuickSort(int data[], int length, int start, int end){
	if(start == end){
		return;
	}
	
	int index = Partition(data, length, start, end);
	if(index > start){
		QuickSort(data, length, start, index-1);
	}
	if(index < end){
		QuickSort(data, length, index+1, end);
	}
}





//插入排序
void  insertSort(vector<int> &arr, int bgn, int end)
{
	for(int i = 0; i < end; ++i)
	{
		for(int j = i+1; j > 0; --j)
		{
			if(arr[j] < arr[j-1])
			{
				swap(&arr[j], &arr[j-1]);
			}
			else{
				break;
			}
		}
	}
}

//希尔排序
void  shellSort(int array[], int lenth)
{
	int incre = lenth;
	while(true)
	{
		incre /= 2;
		for(int k = 0; k < incre; ++k)			//根据增量分为若干子序列
		{
			for(int i = k+incre; i < lenth; i += incre)
			{
				for(int j = i; j < k; j -= incre)
				{
					if(array[j] < array[j-incre])
					{
						swap(&array[j], &array[j-incre]);
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

//归并排序

//堆排序


//剑指offer<7>
//重建二叉树
struct BinaryTreeNode{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};
BinaryTreeNode* Construct(int* preorder, int* inorder, int length){
	if(preorder == nullptr || inorder == nullptr || length <= 0){
		return nullptr;
	}
	ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder){
	//前序遍历序列的第一个数字是根节点的值
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;
	
	if(startPreorder == endPreorder){
		if(startInorder == endInorder && startPreorder == startInorder){
			return root;
		}
		else{
			throw std::exception("Invalid input.");
		}
	}
	
	//在中序遍历序列中找到根节点的值
	int* rootInorder = startInorder;
	while(rootInorder <= endPreorder && *rootInorder != rootValue){
		++rootInorder;
	}
	if(rootInorder == endInorder && *rootInorder != rootValue){
		throw std::exception("Invalid input.");
	}
	
	int leftLength = rootInorder - startInorder;
	int* leftPreorderEnd = startPreorder + leftLength;
	if(leftLength > 0){
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if(leftLength < endPreorder - startPreorder){
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}
	return root;
}

//二叉树的下一个节点<8>
BinaryTreeNode* GetNext(BinaryTreeNode* pNode){
	if(pNode == nullptr){
		return nullptr;
	}
	
	BinaryTreeNode* pNext = nullptr;
	//如果该节点有右子树，那它的下一个节点就是其右子树的最左节点
	if(pNode->m_pRight != nullptr){
		BinaryTreeNode* pRight = pNode->m_pRight;
		while(pRight->m_pLeft != nullptr){
			pRight = pRight->m_pLeft;
		}
		pNext = pRight;
	}//如果该节点既没有右子树，并且它还是父节点右子节点，就需要父节点向上遍历，找到一个它父节点的左子树的节点。如果该节点存在，那么这个节点存在，它的父节点就是要找的节点。
	else if(pNode->m_pParent != nullptr){
		BinaryTreeNode* pCurrent = pNode;
		BinaryTreeNode* pParent = pNode->m_pParent;
		while(pParent != nullptr && pCurrent == pParent->m_pRight){
			pCurrent = pParent;
			pParent = pParent->m_pParent;
		}
		pNext = pParent;
	}
	return pNext;
}

//用两个栈实现队列<9>
template <typename T>
class CQueue{
public:
	CQueue();
	~CQueue();
	
	void appendTail(const T& node);
	T deleteHead();
	
private:
	stack<T> stack1;
	stack<T> stack2;
};

template <class T>
void CQueue<T>::appendTail(const T& element){
	stack1.push(element);
}

template <class T>
T CQueue<T>::deleteHead(){
	
	if(stack2.size() <= 0)
	{
		while(stack1.size() > 0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	
	if(stack2.size == 0){
		throw new exception("queue is empty");
	}
	T head = stack2.top();
	stack2.pop();
	
	return head;
}

//两个队列实现一个栈
template <typename T>
class CStack{
public:
	T& top();
	void push(const T&);
	
private:
	queue<T> queue1;
	queue<T> queue2;
};

T& CStack<T>::top(){
	T topData;
	if(queue1.size() == 0 && queue2.size == 0){
		throw new exception("stack is empty");
	}
	else if(queue1.size() > 0 && queue2.size() == 0){
		while(queue1.size() > 1){
			T front;
			front = queue1.front();
			queue1.pop();
			queue2.push_back(front);
		}
		topData = queue1.front();
		queue1.pop();
	}
	else if(queue1.size() == 0 && queue2.size() > 0){
		while(queue2.size() > 1){
			T front;
			front = queue2.front();
			queue2.pop();
			queue1.push_back(front);
		}
		topData = queue2.front();
		queue2.pop();
	}
	
	return topData;
}
void CStack<T>::push(const T& element){
	if(queue1.empty() && queue2.empty()){
		queue1.push_back(element);
	}
	else if(queue1.empty() && !queue2.empty()){
		queue2.push_back(element);
	}
	else if(!queue1.empty() && queue2.empty()){
		queue1.push_back(element);
	}
}

//求斐波那契数列的第n项<10>
//方法1(有严重的效率问题)
long long Fibonacci(unsigned int n){
	if(n >= 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	return Fibonacci(n-1) + Fibonacci(n-2);
}

//方法2
long long Fibonacci(unsigned int n){
	int result[2] = {0, 1};
	if(n < 2){
		return result[n];
	}
	
	long long fibNMinusOne = 1;
	long long fibNMinusTwo = 0;
	long long fibN;
	for(unsigned i = 2; i <= n; i++){
		fibN = fibNMinusOne + fibNMinusTwo;
		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}
	return fibN;
}


void SortAges(int ages[], int length){
	if(ages == nullptr || length <= 0){
		return;
	}
	
	const int MaxAge = 99;
	int countsOfAge[MaxAge+1] = {0};
	
	for(int i = 0; i < length; i++){
		int age = ages[i];
		if(age < 0 || age > MaxAge){
			throw new std::exception("age out of range");
		}
		++countsOfAge[age];
	}
	
	for(int i = 0; i <= MaxAge; i++){
		for(int j = 0; j < countsOfAge[i]; j++){
			age[i*j + j] = i;
		}
	}
}

//旋转数组的最小数字<11>
int Min(int* numbers, int length)
{
	if(numbers == nullptr || length <= 0){
		throw new std::exception("Invalid paremeters");
	}
	
	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while(numbers[index1] >= numbers[index2]){
		if(index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2) / 2;
		
		//如果下标为index1、index2和indexMid指向的三个数字相等则只能顺序遍历
		if(numbers[index1] == numbers[index2]
			&&numbers[indexMid] == numbers[index1]){
			return MinInOrder(numbers, index1, index2);
		}
		if(numbers[index1] <= numbers[indexMid]){
			index1 = indexMid;
		}
		else if(numbers[index2] >= numbers[indexMid]){
			index2 = indexMid;
		}
	}
	return numbers[indexMid];
}
int MinInOrder(int* numbers, int index1, int index2){
	int result = numbers[index1];
	for(int i = index1 + 1; i <= index2; ++i){
		if(result > numbers[i]){
			result = numbers[i];
		}
	}
	return result;
}

//矩阵中的路径
bool hasPath(char* matrix, int rows, int cols, char* str){
	if(matrix == nullptr || rows < 1 || cols < 1 || str == nullptr){
		return false;
	}
	
	bool* visited = new bool[rows * cols];
	memset(visited, 0, rows * cols);
	
	int pathLength = 0;
	for(int row = 0; row < rows; ++row){
		for(int col = 0; col < cols; ++col){
			if()
		}
	}
}




























