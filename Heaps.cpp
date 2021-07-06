#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define MAXN 500005
	void init(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	}
struct Node{
	int data;
	Node* left;
	Node* right;
	Node(){
		data=0;
		left=nullptr;
		right=nullptr;
	}
};
class MinHeap{
public:
	int size;
	int heap[MAXN];
	MinHeap(){
		this->size=0;
		memset(heap,0,sizeof heap);
	}
	int PARENT(int i){
		return i/2;
	}
	int LEFT(int i){
		return 2*i;
	}
	int RIGHT(int i){
		return 2*i+1;
	}
	void MIN_HEAPIFY(int i){
		int l = LEFT(i);
		int r = RIGHT(i);
		int smallest = i;
		if(l <= size and heap[l] < heap[smallest]){
			smallest = l;
		}
		if(r <= size and heap[r] < heap[smallest]){
			smallest = r;
		}
		if(smallest != i){
			swap(heap[i], heap[smallest]);
		}
	}
	void insertKey(int k){
		heap[++this->size] = k;
		int i=this->size;
		while(i > 1 and heap[PARENT(i)] > heap[i]){
			swap(heap[i],heap[PARENT(i)]);
			i=PARENT(i);
		}
	}
	void decreaseKey(int i, int key){
		heap[i] = key;
		while(i > 1 and heap[PARENT(i)] > heap[i]){
			swap(heap[i],heap[PARENT(i)]);
			i=PARENT(i);
		}
	}
	int extract_MIN(){
		if(this->size==0) return INT_MAX;
		if(this->size==1){
			return heap[this->size--];
		}
		int answer = heap[1];
		heap[1] = heap[this->size--];
		MIN_HEAPIFY(1);
		return answer;
	}
	int get_MIN(){
		if(this->size==0) return INT_MAX;
		return heap[1];
	}
	void deleteKey(int i){
		decreaseKey(i, INT_MIN);
		extract_MIN();
	}
	void BuildHeap(int A[], int n){
		this->size=n;
		for(int i=1;i<=n ;++i) heap[i]=A[i-1];
		for(int i = n/2 ;i >=1 ;--i){
			MIN_HEAPIFY(i);
		}
	}
	void printHeap(){
		for(int i=1;i<=this->size;++i){
			cout<<heap[i]<<" ";
		}
		cout<<endl;
	}
};
class MaxHeap{
public:
	int size;
	int heap[MAXN];
	MaxHeap(){
		this->size=0;
		memset(heap,0,sizeof heap);
	}
	int PARENT(int i){
		return i/2;
	}
	int LEFT(int i){
		return 2*i;
	}
	int RIGHT(int i){
		return 2*i+1;
	}
	void MAX_HEAPIFY(int i){
		int l = LEFT(i);
		int r = RIGHT(i);
		int largest = i;
		if(l <= size and heap[l] > heap[largest]){
			largest = l;
		}
		if(r <= size and heap[r] > heap[largest]){
			largest = r;
		}
		if(largest != i){
			swap(heap[i], heap[largest]);
			MAX_HEAPIFY(largest);
		}
	}
	void insertKey(int k){
		heap[++this->size] = k;
		int i=this->size;
		while(i > 1 and heap[PARENT(i)] < heap[i]){
			swap(heap[i],heap[PARENT(i)]);
			i=PARENT(i);
		}
	}
	void decreaseKey(int i, int key){
		heap[i] = key;
		while(i > 1 and heap[PARENT(i)] < heap[i]){
			swap(heap[i],heap[PARENT(i)]);
			i=PARENT(i);
		}
	}
	int extract_MAX(){
		if(this->size==0) return INT_MIN;
		if(this->size==1){
			return heap[this->size--];
		}
		int answer = heap[1];
		heap[1] = heap[this->size];
		this->size--;
		MAX_HEAPIFY(1);
		return answer;
	}
	int get_MAX(){
		if(this->size==0) return INT_MIN;
		return heap[1];
	}
	void deleteKey(int i){
		decreaseKey(i, INT_MAX);
		extract_MAX();
	}
	void BuildHeap(int A[], int n){
		this->size=n;
		for(int i=1;i<=n ;++i) heap[i]=A[i-1];
		for(int i = n/2 ;i >=1 ;--i){
			MAX_HEAPIFY(i);
		}
	}
	void printHeap(){
		for(int i=1;i<=this->size;++i){
			cout<<heap[i]<<" ";
		}
		cout<<endl;
	}
};
int main(){
	init();
	MinHeap h;
	return 0;
} 