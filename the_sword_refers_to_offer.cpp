//剑指offer<7>

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
	int indexMid = index1;	`
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



/***************************回溯法**************************/
//矩阵中的路径<12>
bool hasPath(char* matrix, int rows, int cols, char* str){
	if(matrix == nullptr || rows < 1 || cols < 1 || str == nullptr){
		return false;
	}
	
	bool* visited = new bool[rows * cols];
	memset(visited, 0, rows * cols);
	
	int pathLength = 0;
	for(int row = 0; row < rows; ++row){
		for(int col = 0; col < cols; ++col){
			if(hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited)){
				delete [] visited;
				return true;
			}
		}
	}
	delete [] visited;
	return false;
}
bool hasPathCore(char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* visited){
	if(str[pathLength] == '\0'){
		return true;
	}
	
	if(row >= 0 && rows > row && col >= 0 && cols > col && matrix[row*cols + col] == str[pathLength] && !visited[row*cols + col]){
		pathLength++;
		visited[row*cols + col] = true;
		
		bool hasPath = hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited)
						|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
						|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
						|| hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited);
		if(!hasPath){
			pathLength--;
			visited[row*cols + col] = false;
		}
	}
	return hasPath;
}



//机器人的运动范围<13>
int movingCount(int threshold, int rows, int cols){
	if(threshold < 0 || rows <= 0 || cols <= 0){
		return 0;
	}
	bool* visit = new bool[rows * cols];
	for(int i = 0; i < rows * cols; ++i){
		visit[i] = false;
	}
	
	int count = movingCountCore(threshold, rows, cols, 0, 0, visit);
	
	delete [] visit;
	return count;
}

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visit){
	int count = 0;
	if(check(threshold, rows, cols, row, col, visit)){
		visit[row*cols + col] = true;
		
		count = 1 + movingCountCore(threshold, rows, cols, row+1, col, visit)
				  + movingCountCore(threshold, rows, cols, row-1, col, visit)
				  + movingCountCore(threshold, rows, cols, row, col+1, visit)
				  + movingCountCore(threshold, rows, cols, row, col-1 visit);
	}
	return count;
}

bool check(int threshold, int rows, int cols, int row, int col, bool* visit){
	if(rows > 0 && row <= rows && cols > 0 && col >= cols
		&& !visit(row*cols+col) && getDigitSum(col) + getDigitSum(row) < threshold)
	{
		return true;
	}
	return false;
}

int getDigitSum(int num){
	int sum = 0;
	while(num){
		sum += (num%10);
		num = num/10;
	}
	return sum;
}



//二进制中1的个数<15>
//效率一般
int numberOf1(int n)
{
	int count = 0;
	unsigned int temp = 1;
	while(temp){
		if(temp & n){
			count++;
		}
		temp = temp << 1;
	}
}
//效率最高
int numberOf1(int n)
{
	int count = 0;
	while(n){
		count++;
		n = (n - 1) & n;
	}
	return count;
}




//数值的整数次方<16>
bool g_InvalidInput = false;
double Power(double base, int exponent){
	g_InvalidInput = false;
	//如果基数为0并且指数小于0,直接返回0
	if(equal(base, 0.0) && exponent < 0){
		g_InvalidInput = true;
		return 0.0;
	}
	
	unsigned int absExponent = (unsigned int)(exponent);
	//如果指数为负数，先把负数转换为正数
	if(exponent < 0){
		absExponent = (unsigned int)(-exponent);
	}
	
	double result = PowerWithUnsignedExponent(base, absExponent);
	//如果指数为负数,则在输出时作相应处理
	if(exponent < 0){
		result = 1.0 / result;
	}
	return result;
}
//实现1
double PowerWithUnsignedExponent(double base, unsigned int exponent){
	double result = 1.0;
	for(int i = 1; i <= exponent; ++i){
		result *= base;
	}
	return result;
}
//实现2
double PowerWithUnsignedExponent(double base, unsigned int exponent){
	if(exponent == 0){
		return 1;
	}
	if(exponent == 1){
		return base;
	}
	int result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if(exponent & 0x1 == 1){
		result *= base;
	}
	return result;
}

//打印从1到最大的n位数<17>
//实现1
void PrintToMaxOfNDigts(int n){
	if(n <= 0){
		return ;
	}
	
	char* number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';
	
	while(!Increment(number)){
		PrintNumber(number);
	}
	
	delete [] number;
}
bool Increment(char* number){
	bool isOverflow = false;
	int nTakeOver = 0;				//进位
	int nLength = strlen(number);
	for(int i = nLength - 1; i >= 0; --i){
		int nSum = number[i] - '0' + nTakeOver;
		if(i == nLength - 1)	//最后一位加一
			nSum++;
		if(nSum >= 10){
			if(i == 0)			//最高位有进位
				isOverflow = true;
			else{
				nSum -= 10;
				nTakeOver = 1;
				number[i] = '0' + nSum;
			}
		}
		else{
			number[i] = '0' + nSum;
			break;
		}
	}
	return isOverflow;
}
void PrintNumber(char* number){
	bool isBeginning0 = true;
	int nLength = strlen(number);
	
	for(int i = 0; i < nLength; i++){
		if(isBeginning0 && number[i] != '0'){
			isBeginning0 = false;
		}
		if(!isBeginning0){
			printf("%c", number[i]);
		}
	}
	printf("\t");
}

//实现2
void PrintToMaxOfNDigts(int n){
	if(n <= 0){
		return;
	}
	
	char* number = new char[n+1];
	number[n] = '\0';
	
	for(int i = 0; i < 10; i++){
		number[0] = i + '0';
		PrintToMaxOfNDigitsReccursively(number, n, 0);
	}
	delete[] number;
}

void  PrintToMaxOfNDigitsReccursively(char* number, int length, int index){
	if(index == length - 1){
		PrintNumber(number);
		return;
	}
	
	for(int i = 0; i < 10; ++i){
		number[index + 1] = i + '0';
		PrintToMaxOfNDigitsReccursively(number, length, index+1);
	}
}

//删除链表的节点<18>
//题目一：在O(1)时间内删除链表节点
struct ListNode{
	int m_nValue;
	ListNode* m_pNext;
};

void DeleteNode(ListNode** pListHead, ListNode* pToBeDelete){
	if(!pListHead || !pToBeDelete)
		return;
	if(pToBeDelete->m_pNext)
	{
		pLisNode* pDelete = pToBeDelete->m_pNext;
		pToBeDelete->m_nValue = pToBeDelete->m_nValue;
		pToBeDelete->m_pNext = pDelete->m_pNext;
		delete pDelete;
		pDelete = nullptr;
	}
	else if(*pLisNode == pToBeDelete){
		delete pToBeDelete;
		pToBeDelete = nullptr;
		*pLisNode = nullptr;
	}
	else{
		/*
		pLisNode* pPreNode = *pLisNode;
		pLisNode* pNode = pPreNode->m_pNext;
		while(pNode->m_pNext != nullptr){
			pPreNode = pNode;
			pNode = pNode->m_pNext;
		}
		pPreNode->m_pNext = nullptr;
		delete pNode;
		pNode = nullptr;
		*/
		
		pLisNode* pNode = *pListHead;
		while(pNode->m_pNext != pToBeDelete){
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = nullptr;
		delete->pToBeDelete;
		pToBeDelete = nullptr;
	}
}

//题目二：删除链表中重复节点
void DeleteDuplication(ListNode** pHead){
	if(pHead == nullptr || *pHead == nullptr){
		return;
	}
	
	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pHead; 
	while(pNode != nullptr){
		ListNode* pNext = pNode->m_pNext;
		bool needDelete = false;
		if(pNext != nullptr && pNext->m_nValue == pNode->m_nValue){
			neetDelete = true;
		}
		
		if(!needDelete){
			pPreNode = pNode;
			pNode = pNode->m_pNext;
		}
		else{
			int value = pNode->m_nValue;
			ListNode* pToBedel = pNode;
			while(pToBedel != nullptr && pToBedel->m_nValue == value){
				pNext = pToBedel->m_pNext;
				
				delete pToBedel;
				pToBedel = nullptr;
				
				pToBeDel = pNext;
			}
			if(pPreNode == nullptr){
				*pHead = pNext;
			}
			else{
				pPreNode->m_pNext = pNext;
			}
			pNode = pNext;
		}
	}
}

//正则表达式匹配<19>
bool match(char* str, char* pattern){
	if(str == nullptr || pattern == nullptr){
		return false;
	}
	return matchCore(str, pattern);
}
bool matchCore(char* str, char* pattern){
	if(*str == '\0' && *pattern == '\0'){
		return true;
	}
	
	if(*str != '\0' && *pattern == '\0'){
		return false;
	}
	
	if(*(pattern+1) == '*'){
		if(*pattern == *str || (*pattern == '.' && *str != '\0')){
			return matchCore(str+1, pattern+2)		//移到下一个字符
				|| matchCore(str+1, pattern)		//匹配串不变，被匹配串移动一个字符
				|| matchCore(str, pattern+2);		//匹配串移动两个字符
		}
		else{
			return matchCore(str, pattern+2);
		}
	}
	
	if(*str == *pattern || *pattern == '.' && *str != '\0'){
		return matchCore(str+1, pattern+1);
	}
	return false;
}


//二叉树中序遍历的非递归实现
//遇到一个节点就把它压栈，并去遍历它的左子树；当左子树遍历结束时，从栈顶弹出一个节点并访问它；然后按其右指针再去中序遍历该节点的右子树
void InOrderTraversal(BinaryTreeNode* BT){
	BinaryTreeNode* tree = BT;
	stack<BinaryTreeNode*> TreeStack;
	
	while(tree || !TreeStack.empty()){
		while(tree){
			TreeStack.push(tree);
			tree = tree->m_pLeft;
		}
		if(!TreeStack.empty()){
			tree = TreeStack.top();
			std::cout << tree->data << endl;;
			TreeStack.pop();
			tree = tree->m_pRight;
		}
	}
}



//八皇后问题
bool notDanger(inrt row, int column, int (*chess)[8]){
	int i, j, flag1 = flag2 = flag3 = flag4 = flag5 = 0;
	
	//判断列方向
	for(i = 0; i < 8; i++){
		if((*(*chess+i)+j) != 0){
			flag1 = 1;
			break;
		}
	}
	
	//判断左上方
	for(i = row, j = column; i != 0 && j != 0; i--, j--){
		if((*(*chess+i)+j) != 0){
			flag2 = 1;
			break;
		}
	}
	
	//判断右上方
	for(i = row, j = column; i != 0 && j < 8; i--, j++){
		if((*(*chess+i)+j) != 0){
			flag3 = 1;
			break;
		}
	}
	
	//判断左下方
	for(i = row, j = column; i < 8 && j != 0 ; i++, j--){
		if((*(*chess+i)+j) != 0){
			flag4 = 1;
			break;
		}
	}
	
	//判断右下方
	for(i = row, j = column; i < 8 && j < 8; i++, j++){
		if((*(*chess+i)+j) != 0){
			flag5 = 1;
			break;
		}
	}
	if(flag1 || flag2 || flag3 || flag4 || flag5){
		return 0;
	}
	else{
		return true;
	}
}

/*	
参数row：表示起始行
参数column：表示列数
参数chess: 表示指向棋盘每一行的指针	
*/
void EightQueen(int row, int column, int (*chess)[8]){
	int chess2[8][8], i, j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			chess2[i][j] = chess[i][j];
		}
	}
	
	int count = 0;
	if(8 == row)
		printf("第%d种\n", count);
		for(i = 0; i < 8; i++){
			for(j = 0; j < 8; j++){
				printf("%d ", *(*(chess2 + i) + j));
			}
			printf("\n");
		}
		printf("\n");
		count++;
	}
	else{
		for(j = 0; j < column; j++){
			if(notDanger(row, j, chess)){
				for(i = 0; i < 8; i++){
					(*(*chess2+row)+i) = 0;
				}
				(*(*chess2+row)+j) = 1;
				
				EightQueen(row+1, column, chess2);
			}
		}
	}
}

int main(){
	int chess[8][8] = {0};
	EightQueen(0, 8, chess);
	return 0;
}


//BF算法
bool BF(const char* str1, const char* str2){
	if(str1 == NULL || str2 == NULL){
		return false;
	}
	int length1 = strlen(str1);
	int length2 = strlen(str2)
	int i, j;
	for(i = 0; i < length1; i++){
		int k = i;
		j = 0;
		while(str1[k] == str2[j] && j < length2){
			j++;
			k++;
		}
		if(j == length2){
			return true;
		}
		/*
		k = i;
		for(j = 0; j < length2; j++){
			 if(str1[k] == str2[j]){
				 k++;
			 }
			 else{
				 break;
			 }
		}
		if(j == length2){
			return ture;
		}
		*/
	}
	return false;
}
//KMP算法



//全排列
void AllArrangement(char arr[], int left, int right){
	if(left >= right){
		printf("%s", arr);
		return;
	}
	
	for(int i = left; i < right; i++){
		swap(&arr[left], &arr[i]);
		AllArrangement(arr, left+1, right);
		swap(&arr[left], &arr[i]);
	}
}










