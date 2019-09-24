#pragma once
#include <iostream>
#include <vector>


/*
* 测试排序算法
*/
//template <typename T>
//void test_sort_algorithm(T &arr) {
//	vector<T(*)(T, size_t)> fun;
//	fun.push_back(bubble_sort);
//	//T res = (*fun[0])(arr, arr.size);
//	//for (auto i : res)
//	//	cout << i << " ";
//	//cout << endl;
//}

/*
* 交换两元素
*/
template <typename T>
void Swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

/* 
* 冒泡排序
* 时间复杂度：O(n^2) 
* 最差复杂度：O(n^2)
* 最好复杂度：O(n)
* 空间复杂度：O(1)
* 稳定性：稳定
*/
template <typename T>
T bubble_sort(T &arr, size_t arr_size) {
	for (size_t i = 0; i < arr_size - 1; ++i) {
		bool have_sorted = true; // 标记序列是否有序，有序则提前跳出循环

		for (size_t j = 0; j < arr_size - i -1; ++j) {
			if (arr[j + 1] < arr[j]) { // 若<改为<=，则算法变为不稳定的
				Swap(arr[j], arr[j + 1]);

				have_sorted = false;
			}
		}
		if (have_sorted)
			break;
	}

	return arr;
}

/*
* 选择排序
* 时间复杂度：O(n^2)
* 最差复杂度：O(n^2)
* 最好复杂度：O(n^2)
* 空间复杂度：O(1)
* 稳定性：不稳定
*/
template <typename T>
T select_sort(T &arr, size_t size) {
	for (size_t i = 0; i < size - 1; ++i) {
		size_t tmp = i;
		for (size_t j = i + 1; j < size; ++j) {
			if (arr[j] < arr[tmp]) {
				tmp = j;
			}
		}
		//本轮第一个数为最小数，则不用交换
		if (tmp != i) Swap(arr[tmp], arr[i]);
	}
	return arr;
}

/*
* 插入排序
* 时间复杂度：O(n^2)
* 最差复杂度：O(n^2)
* 最好复杂度：O(n)
* 空间复杂度：O(1)
* 稳定性：稳定
*/
template <typename T>
T insert_sort(T &arr, int size) {
	for (int i = 1; i < size; ++i) {
		int tmp = i;
		// 每次将当前数插入到合适的位置，因此需要将有序的序列往后挪，以腾出位置
		for (int j = i - 1; j >= 0 && arr[tmp] < arr[j]; --j) {
			Swap(arr[tmp], arr[j]);
			tmp = j;
		}
	}
	return arr;
}

/*
* 希尔排序，优化版插入排序，每轮以不同步长进行插排，最后一轮步长为1
* 时间复杂度：跟步长有关，O(n^1.3)
* 最差复杂度：O(n^2)
* 最好复杂度：O(n)
* 空间复杂度：O(1)
* 稳定性：不稳定
*/
template <typename T>
T shell_sort(T &arr, int size) {
	// 初始化步长
	int gap = 1;
	while (gap <= size) {
		gap = 3 * gap + 1;
	}

	// 每轮递减步长进行插排
	while (gap >= 1) {
		for (int i = gap; i < size; ++i) {
			int tmp = i;
			for (int j = i - gap; j >= 0 && arr[tmp] < arr[j]; --j) {
				Swap(arr[tmp], arr[j]);
				tmp = j;
			}
		}
		gap = (gap - 1) / 3;
	}
	return arr;
}

/*
* 归并排序调用函数，合并两个有序的序列arr[left, mid]和arr[mid+1, right]
*/
template <typename T>
void _merge_two_arr(T &arr, int left, int mid, int right, T &tmp) {
	int i = left;
	int j = mid + 1;
	int idx = left;

	// 循环将小的数放到tmp中
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) { // 此处的等号保证排序稳定性
			tmp[idx++] = arr[i++];
		}
		else {
			tmp[idx++] = arr[j++];
		}
	}

	while (i <= mid) tmp[idx++] = arr[i++]; // 将剩余的左半序列放进tmp
	while (j <= right) tmp[idx++] = arr[j++]; // 将剩余的右半序列放进tmp

	// 把tmp里的有序序列复制到原序列中
	for (i = left; i <= right; ++i) {
		arr[i] = tmp[i];
	}
}

/*
* 归并排序调用函数，递归地切分序列并合并
*/
template <typename T>
void _merge_sort_rec(T &arr, int left, int right, T &tmp) {
	if (left == right) return;
	int mid = (left + right) >> 1;
	_merge_sort_rec(arr, left, mid, tmp); // 分成左半部分
	_merge_sort_rec(arr, mid + 1, right, tmp); // 分成左半部分
	_merge_two_arr(arr, left, mid, right, tmp); // 合并有序的两部分
}

/*
* 归并排序
* 时间复杂度：O(nlogn)
* 最差复杂度：O(nlogn)
* 最好复杂度：O(nlogn)
* 空间复杂度：O(n)
* 稳定性：稳定
*/
template <typename T>
T merge_sort(T &arr, int size) {
	T tmp(arr); // 创建一个临时变量
	_merge_sort_rec(arr, 0, size - 1, tmp);
	return arr;
}

/*
* 快速排序调用函数，将比base小的数放base左边，比base大的放base右边
*/
template <typename T>
int _quick_sort_division(T &arr, int left, int right) {
	T::value_type base = arr[left];
	while (left < right) {
		// 先从右往左，碰到第一个比base小的就将其放在left位置
		while (left < right && arr[right] >= base)
			--right;
		arr[left] = arr[right];

		// 再从左往右，碰到第一个比base大的就将其放在right位置
		while (left < right && arr[left] <= base)
			++left;
		arr[right] = arr[left];
	}
	arr[left] = base; // 循环出来之后left=right，且此位置为上一个left或right位置的元素，
	return left; // 返回切分后的基准点
}

/*
* 快速排序调用函数，递归地将序列以基准点base分成左右两部分，且左部元素都比base小，右部元素都比base大
*/
template <typename T>
void _quick_sort_rec(T &arr, int left, int right) {
	if (left < right) {
		int base_idx = _quick_sort_division(arr, left, right);
		_quick_sort_rec(arr, left, base_idx - 1);
		_quick_sort_rec(arr, base_idx + 1, right);
	}
}

/*
* 快速排序
* 时间复杂度：O(nlogn)
* 最差复杂度：O(n^2)
* 最好复杂度：O(nlogn)
* 空间复杂度：O(n)
* 稳定性：不稳定
*/
template <typename T>
T quick_sort(T &arr, int size) {
	_quick_sort_rec(arr, 0, size - 1);
	return arr;
}



