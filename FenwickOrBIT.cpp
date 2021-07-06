	#include <bits/stdc++.h>
	using namespace std;

		void init(){
			ios_base::sync_with_stdio(false);
			cin.tie(NULL);
			cout.tie(NULL);
		#ifndef ONLINE_JUDGE
			freopen("input.txt","r",stdin);
			freopen("output.txt","w",stdout);
		#endif
		}

class BinaryIndexTree{
public:
	int N;
	int *tree;
	BinaryIndexTree(int N){
		this->N=N;
		this->tree = (int*)malloc((N+1)*sizeof(int));
	}
	int findSum(int Idx){
		int sum=0;
		// Idx+=1;
		while(Idx > 0){
			sum+=tree[Idx];
			Idx-=(Idx & (-Idx ));
		}
		return sum;
	}
	void updateAtIdx(int Idx, int val){
		// Idx+=1;
		int MaxIdx = this->N;
		while(Idx <= MaxIdx){
			tree[Idx]+=val;
			Idx+=(Idx & (-Idx ));
		}
	}
	void BuildTree(int arr[]){
		memset(tree,0,sizeof(tree));
		for(int i=0;i<N;++i)
			updateAtIdx(i+1,arr[i]);
	}
	int findValueAtIDX(int Idx){
		int sum = tree[Idx];
		if( Idx > 0){
			int z = 
			Idx - (Idx & -Idx); // Index till when to stop
			Idx--;
			while(Idx != z){
				sum-=tree[Idx];
				Idx -= (Idx & -Idx);
			}
		} 
		return sum;
	}

	int rangeSum(int l, int r){
		return findSum(r)-findSum(l-1);
	}
};

int main(){
	init();
	int N;
	cin>>N;
	int arr[N]={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
	BinaryIndexTree bit(N);
	//tree works with 1 based indexing 
	// with array we work with 0 based indexing
	bit.BuildTree(arr);
	//sum from arr[0...5]
	cout<<bit.findSum(6)<<'\n';
	arr[3]+=6;
	bit.updateAtIdx(3,6);
	cout<<bit.findSum(6)<<'\n';
	return 0;	
}