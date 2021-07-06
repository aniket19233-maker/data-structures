#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
	void init(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	}
int findMinIndex(int arr[], int n, int i){
	int j = i;
	for(;i<n;++i){
		if(arr[i] < arr[j])
			j = i;
	}
	return j;
}
int findMaxIndex(int arr[], int n, int i){
	int j = i;
	for(;i<n;++i){
		if(arr[i] > arr[j])
			j = i;
	}
	return j;
}
void Selection_Sort(int arr[], int n){
	for(int i=0;i<n;++i){
		int minIdx = findMinIndex(arr, n, i);
		swap(arr[i], arr[minIdx]);
	}
}
void Insertion_Sort(int A[], int n){
	for(int j = 1; j < n; ++j ){
		int key = A[j];
		int i = j-1;
		while(i >= 0 and A[i] > key){
			A[i+1] = A[i];
			i = i - 1; 
		}
		A[i+1] = key;
	}
}
void Bubble_Sort(int arr[], int n){
	for(int i = 0; i < n ; ++i){
		for(int j = n - 1 ; j >=  i+1 ; --j){
			if(arr[j] < arr[j-1]){
				swap(arr[j], arr[j-1]);
			}
		}
	}
}
void Merge(int arr[], int l, int mid, int r){
	int n1 = mid - l + 1;
	int n2 = r - mid;
	int L[n1], R[n2];
	for(int i = 0; i < n1; ++i){
		L[i] = arr[l + i];
	}
	for(int i = 0; i < n2; ++i){
		R[i] = arr[mid + i + 1];
	}
	int i = 0, j = 0;
	for(int k = l; k <= r ;++k ){
		if(i < n1 and j < n2 and L[i] <= R[j]){
			arr[k] = L[i++];
		}else if(i < n1 and j < n2 and L[i] > R[j]){
			arr[k] = R[j++];
		}else if(i < n1 and j == n2){
			arr[k] = L[i++];
		}else if(i == n1 and j < n2){
			arr[k] = R[j++];
		}
	}
}
void Merge_Sort(int arr[], int l, int r){
	if(l < r){
		int mid = l+(r-l)/2;
		Merge_Sort(arr, l, mid);
		Merge_Sort(arr, mid+1, r);
		Merge(arr, l, mid, r);	
	}
}
int Partition(int arr[], int l, int r){
	int pivot = arr[r];
	int i = l - 1;
	for(int j = l; j < r ; ++j ){
		if(arr[j] <= pivot){
			++i;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i+1], arr[r]);
	return i + 1;
}
void Quick_Sort(int arr[], int l, int r){
	if(l < r){
		int q = Partition(arr, l, r);
		Quick_Sort(arr, l, q - 1);
		Quick_Sort(arr, q + 1, r);
	}
}
void Count_Sort(int arr[], int n, int k){
	int B[n+1];
	int C[k+1];
	memset(C, 0, sizeof(C));
	for(int j = 0;j < n ;++j){
		C[arr[j]]+=1;
	}
	for(int i=1; i<=k; ++i){
		C[i]+=C[i-1];
	}
	for(int j = n-1; j>=0; --j){
		B[C[arr[j]]] = arr[j];
		C[arr[j]]-=1;
	}
	for(int i=1;i<=n;++i) arr[i-1] = B[i];
}
int main(){
	init();
	int n = 6;
	int arr[6] = {64, 25, 12, 22, 11, 100};
	Count_Sort(arr, n, 100);
	for(int x : arr) cout<<x<<" ";
	return 0;
}