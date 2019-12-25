//冒泡排序
//平均时间复杂度：O(n^2)	最好情况：O(n)	最坏情况：O(n^2)
//辅助空间：O(1)
//稳定性：稳定
void bubbleSort(int arr[], int n)
{
	bool swapState = true;
	int i, j, temp;
	for(i = 0; i < n - 1 && swapState == true; i++){	//循环n-1次
		swapState = false;
		for(j = 0; j < n- i - 1; j++){					//每遍循环需要处理的无序部分
			if(arr[j] > arr[j + 1]){
				swap(&arr[j], &swap[j + 1]);
				swap = true;
			}
		}
	}
}
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
//鸡尾酒排序
void CocktailSort(int arr[], int n){
	bool swapped = true;
	int i, left = 0, right = n-1;
	while(swapped){
		swapped = false;
		for(i = left; i < n-1; i++){	//从左边找一个最大的放到右边
			if(arr[i] > arr[i+1]){
				swap(&arr[i], &arr[i+1]);
				swapped = true;
			}
		}
		right--;
		for(i = right; i > left; i--){	//从右边找一个最小的放到左边
			if(arr[i] < arr[i-1]){
				swap(&arr[i], &arr[i-1]);
				swapped = true;
			}
		}
		left++;
	}
}


//简单选择排序
//平均时间复杂度：O(n^2)	最好情况：O(n^2)	最坏情况：O(n^2)
//辅助空间：O(1)
//稳定性：不稳定
void selectionSort(int arr[], int len){
	int i, j, Min;
	for(i = 0; i < len-1; i++){
		Min = i;
		for(j = i+1; j < len-1; j++){
			if(arr[j] < arr[Min]){
				Min = j;
			}
		}
		if(Min != i){
			swap(&arr[i], &arr[Min]);
		}
	}
}
void selectionSort(vector<int> &arr, int bgn, int end)
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
//平均时间复杂度：O(n^2)	最好情况：O(n)	最坏情况：O(n^2)
//最坏的空间复杂度：O(n)
//辅助空间：O(1)
//稳定性：稳定
void insertSort(int arr[], int n){
	int i, j, key;
	for(i = 1; i < n; i++){
		key = arr[i];
		j = i - 1;
		while(j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}
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
//插入排序的改进：二分插入排序
//平均时间复杂度：O(n^2)	最好情况：O(nlogn)	最坏情况：O(n^2)
//辅助空间：O(1)
//稳定性：稳定

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


//归并排序


























