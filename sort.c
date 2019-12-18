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




























