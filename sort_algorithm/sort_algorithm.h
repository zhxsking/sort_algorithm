#pragma once
#include <iostream>
#include <vector>


/*
* ���������㷨
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
* ������Ԫ��
*/
template <typename T>
void Swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

/* 
* ð������
* ʱ�临�Ӷȣ�O(n^2) 
* ���Ӷȣ�O(n^2)
* ��ø��Ӷȣ�O(n)
* �ռ临�Ӷȣ�O(1)
* �ȶ��ԣ��ȶ�
*/
template <typename T>
T bubble_sort(T &arr, size_t arr_size) {
	for (size_t i = 0; i < arr_size - 1; ++i) {
		bool have_sorted = true; // ��������Ƿ�������������ǰ����ѭ��

		for (size_t j = 0; j < arr_size - i -1; ++j) {
			if (arr[j + 1] < arr[j]) { // ��<��Ϊ<=�����㷨��Ϊ���ȶ���
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
* ѡ������
* ʱ�临�Ӷȣ�O(n^2)
* ���Ӷȣ�O(n^2)
* ��ø��Ӷȣ�O(n^2)
* �ռ临�Ӷȣ�O(1)
* �ȶ��ԣ����ȶ�
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
		//���ֵ�һ����Ϊ��С�������ý���
		if (tmp != i) Swap(arr[tmp], arr[i]);
	}
	return arr;
}

/*
* ��������
* ʱ�临�Ӷȣ�O(n^2)
* ���Ӷȣ�O(n^2)
* ��ø��Ӷȣ�O(n)
* �ռ临�Ӷȣ�O(1)
* �ȶ��ԣ��ȶ�
*/
template <typename T>
T insert_sort(T &arr, int size) {
	for (int i = 1; i < size; ++i) {
		int tmp = i;
		// ÿ�ν���ǰ�����뵽���ʵ�λ�ã������Ҫ���������������Ų�����ڳ�λ��
		for (int j = i - 1; j >= 0 && arr[tmp] < arr[j]; --j) {
			Swap(arr[tmp], arr[j]);
			tmp = j;
		}
	}
	return arr;
}

/*
* ϣ�������Ż����������ÿ���Բ�ͬ�������в��ţ����һ�ֲ���Ϊ1
* ʱ�临�Ӷȣ��������йأ�O(n^1.3)
* ���Ӷȣ�O(n^2)
* ��ø��Ӷȣ�O(n)
* �ռ临�Ӷȣ�O(1)
* �ȶ��ԣ����ȶ�
*/
template <typename T>
T shell_sort(T &arr, int size) {
	// ��ʼ������
	int gap = 1;
	while (gap <= size) {
		gap = 3 * gap + 1;
	}

	// ÿ�ֵݼ��������в���
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
* �鲢������ú������ϲ��������������arr[left, mid]��arr[mid+1, right]
*/
template <typename T>
void _merge_two_arr(T &arr, int left, int mid, int right, T &tmp) {
	int i = left;
	int j = mid + 1;
	int idx = left;

	// ѭ����С�����ŵ�tmp��
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) { // �˴��ĵȺű�֤�����ȶ���
			tmp[idx++] = arr[i++];
		}
		else {
			tmp[idx++] = arr[j++];
		}
	}

	while (i <= mid) tmp[idx++] = arr[i++]; // ��ʣ���������зŽ�tmp
	while (j <= right) tmp[idx++] = arr[j++]; // ��ʣ����Ұ����зŽ�tmp

	// ��tmp����������и��Ƶ�ԭ������
	for (i = left; i <= right; ++i) {
		arr[i] = tmp[i];
	}
}

/*
* �鲢������ú������ݹ���з����в��ϲ�
*/
template <typename T>
void _merge_sort_rec(T &arr, int left, int right, T &tmp) {
	if (left == right) return;
	int mid = (left + right) >> 1;
	_merge_sort_rec(arr, left, mid, tmp); // �ֳ���벿��
	_merge_sort_rec(arr, mid + 1, right, tmp); // �ֳ���벿��
	_merge_two_arr(arr, left, mid, right, tmp); // �ϲ������������
}

/*
* �鲢����
* ʱ�临�Ӷȣ�O(nlogn)
* ���Ӷȣ�O(nlogn)
* ��ø��Ӷȣ�O(nlogn)
* �ռ临�Ӷȣ�O(n)
* �ȶ��ԣ��ȶ�
*/
template <typename T>
T merge_sort(T &arr, int size) {
	T tmp(arr); // ����һ����ʱ����
	_merge_sort_rec(arr, 0, size - 1, tmp);
	return arr;
}

/*
* ����������ú���������baseС������base��ߣ���base��ķ�base�ұ�
*/
template <typename T>
int _quick_sort_division(T &arr, int left, int right) {
	T::value_type base = arr[left];
	while (left < right) {
		// �ȴ�������������һ����baseС�ľͽ������leftλ��
		while (left < right && arr[right] >= base)
			--right;
		arr[left] = arr[right];

		// �ٴ������ң�������һ����base��ľͽ������rightλ��
		while (left < right && arr[left] <= base)
			++left;
		arr[right] = arr[left];
	}
	arr[left] = base; // ѭ������֮��left=right���Ҵ�λ��Ϊ��һ��left��rightλ�õ�Ԫ�أ�
	return left; // �����зֺ�Ļ�׼��
}

/*
* ����������ú������ݹ�ؽ������Ի�׼��base�ֳ����������֣�����Ԫ�ض���baseС���Ҳ�Ԫ�ض���base��
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
* ��������
* ʱ�临�Ӷȣ�O(nlogn)
* ���Ӷȣ�O(n^2)
* ��ø��Ӷȣ�O(nlogn)
* �ռ临�Ӷȣ�O(n)
* �ȶ��ԣ����ȶ�
*/
template <typename T>
T quick_sort(T &arr, int size) {
	_quick_sort_rec(arr, 0, size - 1);
	return arr;
}



