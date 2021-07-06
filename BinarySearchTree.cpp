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
struct Node{
	int data;
	Node* left;
	Node* right;
	int lcount;
	Node(){
		data=0;
		left=nullptr;
		right=nullptr;
		lcount=0;
	}
};

class BinarySearchTree{
public: 
	int N;
	Node* root;
	BinarySearchTree(int N){
		this->N = N;
		this->root= nullptr;
	}
	Node* findMinimum(Node* root){
		if(root==nullptr) return root;
		else if(root->left!=nullptr){
			return findMinimum(root->left);
		}else{
			return root;
		}
	}
	Node* findMaximum(Node* root){
		if(root==nullptr) return root;
		else if(root->right!=nullptr){
			return findMaximum(root->right);
		}else{
			return root;
		}
	}
	Node* insertKeyInBST(Node* root, int key){
		if(root==nullptr){
			root = new Node;
			root->data = key;
			return root;
		}
		else if(root->data > key){
			root->left = insertKeyInBST(root->left, key);
			root->lcount++;
		}else{
			root->right = insertKeyInBST(root->right, key);
		}
		return root;
	}
	Node* deleteKeyInBST(Node* root, int key){
		if(root==nullptr) return root;
		if(key < root->data){
			root->left = deleteKeyInBST(root->left, key);  
			root->lcount--;
		}else if(key>root->data){
			root->right = deleteKeyInBST(root->right, key);
		}else{
			if(root->left==nullptr and root->right==nullptr){
				return nullptr;
			}else if(root->left == nullptr){
				Node* temp = root -> right;
				root=nullptr;
				return temp;
			}else if(root->right == nullptr){
				Node* temp=root->left;
				root=nullptr;
				return temp;
			}
				Node* minNode = findMinimum(root->right);
				root->data = minNode->data;
				root->right = deleteKeyInBST(root->right, minNode->data); 
		}
		return root;
	}
	Node* searchKey(Node* root, int key){
		if(root == nullptr ) return nullptr;
		if(root->data == key ) return root;
		else if(root->data < key) return searchKey(root->right, key);
		else return searchKey(root->left, key);
	}
	void preOrder(Node* root, vector<int> &v){
		if(root==nullptr) return;
		v.push_back(root->data);
		preOrder(root->left, v);
		preOrder(root->right, v);
	}
	void inOrder(Node* root, vector<int> &v){
		if(root==nullptr) return;
		inOrder(root->left, v);
		v.push_back(root->data);
		inOrder(root->right, v);
	}
	void postOrder(Node* root, vector<int> &v){
		if(root==nullptr) return;
		postOrder(root->left, v);
		postOrder(root->right, v);
		v.push_back(root->data);
	}
	int DepthOrHeightOfBST(Node* root){
		if(root==nullptr) return 0;
		return max(DepthOrHeightOfBST(root->left),DepthOrHeightOfBST(root->right))+1;
	}
	Node* KthSmallest(Node* root, int& k){
		if(root==nullptr) return nullptr;
		cout<<root->data<<'\n';
		Node *left = KthSmallest(root->left, k);
		if(left!=nullptr)return left;
		--k;
		if(k==0){
			return root;
		}
		return KthSmallest(root->right, k);
	}
	Node* KthSmallestUsingRanks(Node* root, int k){
		if(root==nullptr) return nullptr;
		int leftCount = root->lcount+1;
		if(leftCount == k) return root;
		else if(leftCount > k) return KthSmallestUsingRanks(root->left, k);		
		else return KthSmallestUsingRanks(root->right, k-leftCount);
	}
	bool isBSTpossibleFromPreOrder(int pre[], int n){
		stack<int> s;
		int root = INT_MIN;
		for(int i=0;i<n;++i){
			if(pre[i]<root) return 0;
			while(s.size() > 0 and s.top() < pre[i]){
				root = s.top();
				s.pop();
			}
			s.push(pre[i]);
		} 
		return 1;
	}
	Node* LCA(Node* root, int x, int y){
		if(root==nullptr) return nullptr;
		if(root->data > x and root->data > y){
			return LCA(root->left, x, y);
		}
		if(root->data < x and root->data < y){
			return LCA(root->right, x, y);
		}
		return root;
	}
	bool deadEnd(Node* root, int min, int max){
		if(root==nullptr) return 0;
		if(min >= max) return 1;
		return deadEnd(root->left, min, root->data-1)||
				deadEnd(root->right, root->data+1,max);
	}
	int CountPairsWithSumtoX(Node* root1, Node* root2, map<int, int> &mp, int x){
		if(root1==nullptr or root2==nullptr) return 0;
		int left = CountPairsWithSumtoX(root1->left, root2, mp, x);
		int right = CountPairsWithSumtoX(root1->right, root2, mp, x);
		return (mp.find(x-root1->data)!=mp.end()) + left +right;	
	}
	Node* inOrderSuccessor(Node* root, Node* node){
		if(node->right!=nullptr) {
			return findMinimum(node->right);
		}
		Node* succ=nullptr;
		while(root!=nullptr){
			if(node->data < root->data){
				succ = root;
				root=root->left;
			}else if(node->data > root->data) 
				root=root->right; 
			else break;
		}
		return succ;
	}
	void RangeSum(Node* root, int l, int r, int &s){
		if(root==nullptr) return;
		RangeSum(root->left, l, r, s);
		if(root->data >=l and root->data <=r) s+=root->data;
		RangeSum(root->right, l, r, s);
	}
};
int main(){
	init();
	int N;
	cin>>N;
	BinarySearchTree bst(N);
	for(int i=0;i<N;++i){
		int x;
		cin>>x;
		bst.root = bst.insertKeyInBST(bst.root, x);
	}
	int l, r;
	cin>>l>>r;
	if(l>r) swap(l,r);
	int s = 0;
	bst.RangeSum(bst.root, l, r, s);
	cout<<s<<'\n';
 	return 0;	
}