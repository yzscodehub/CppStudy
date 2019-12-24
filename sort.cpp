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
//堆化
void heapify(int tree[], int n, int i){
	if(i >= n){
		return;
	}
	int lc = 2 * i + 1;
	int r2 = 2 * i + 2;
	int max = i;
	if(lc < n && tree[max] < tree[lc]){
		max = lc;
	}
	if(rc < n && tree[max] < tree[rc]){
		max = rc;
	}
	
	if(i != max){
		swap(&tree[i], &tree[max]);
		heapify(tree, n, max);
	}
}
//构建堆
void build_heap(int tree[], int n){
	int last_node = n - 1;
	int last_node_parent = (last_node - 1) / 2;
	for(int i = last_node_parent; i >= 0; --i){
		heapify(tree, n, i);
	}
}

void swap(int *num1, int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
//堆排序
void heap_sort(int tree[], int n){
	build_heap(tree, n);
	for(int i = n - 1; i >= 0; i++){
		swap(&tree[i], &tree[0]);
		heapify(tree, i, 0);
	}
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























