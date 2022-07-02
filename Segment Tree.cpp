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

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

class SegMentTree{
public:
	int n;
	int *tree;
	SegMentTree(int e){
		this->n = 4*e+1;
		this->tree = new int[this->n];
		for(int i=0;i<this->n;++i) tree[i]=0;
	}
	void buildTree(int arr[], int s, int e, int i){
		if(s > e) return;
		if(s==e){
			this->tree[i] = arr[s];
			return ;
		}
		int mid = s+(e-s)/2;
		buildTree(arr, s, mid, 2*i);
		buildTree(arr, mid+1, e, 2*i+1);
		int l = this->tree[2*i];
		int r = this->tree[2*i+1];
		this->tree[i] = min(l, r);
	}
	//Range min query 
	int query(int i, int s, int e, int qs, int qe){
		//No overlap
		if(qs>e or qe<s) return INT_MAX;
		//complete overlap
		if(qs<=s and e<=qe){
			return tree[i];
		}
		//partial overlap; 
		int mid = s + (e-s)/2;
		int left = query(2*i, s, mid, qs, qe);
		int right = query(2*i+1, mid+1, e, qs, qe);
		return min(left, right);
	}
	void updateNode(int i, int s, int e, int index, int val){
		if(index < s or index > e) return;
		if(s==e){
			tree[i]= val;return;
		}
		int mid = s+(e-s)/2;
		updateNode(2*i, s, mid, index, val);
		updateNode(2*i+1, mid+1, e, index, val);
		tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	void updateRange(int i, int s, int e, int rs, int re, int inc){
		if(re < s or rs > e) return;
		if(s==e){
			tree[i]+= inc;return;
		}
		int mid = s+(e-s)/2;
		updateRange(2*i, s, mid, rs, re, inc);
		updateRange(2*i+1, mid+1, e, rs, re, inc );
		tree[i] = min(tree[2*i], tree[2*i+1]);
	}
};

int main(){
	init();
	int n;
	cin>>n;
	int arr[n];
	for(int i=0;i<n;++i) cin>>arr[i];
	SegMentTree segt(n);
	segt.buildTree(arr, 0, n-1, 1);
	int l, r;
	cin>>l>>r;
	cout<<segt.query(1, 0, n-1, l, r)<<'\n';	
	segt.updateRange(1, 0, n-1,0, n-1, 2);
	cin>>l>>r;
	cout<<segt.query(1, 0, n-1, l, r);
	return 0;
}