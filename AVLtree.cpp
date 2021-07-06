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
	int height;
	Node(){
		data=0;
		left=nullptr;
		right=nullptr;
		height=1;
	}
};
class AVLtree{
public:
	int N;
	Node* root;
	AVLtree(int N){
		this->N = N;
		this->root = nullptr;
	}
	int height(Node* node){
		if(node==nullptr) return 0;
		return node->height;
	}
	int BalanceFactor(Node* node){
		if(node==nullptr) return 0;
		return height(node->left) - height(node->right);
	}
	Node* leftRotate(Node* x){	
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		x->height = max(height(x->left),height(x->right))+1;
		y->height = max(height(y->left),height(y->right))+1;
		return y;
	}
	Node* rightRotate(Node* y){
		Node *x = y->left;
		Node* T2 = x->right;
		x->right = y;
		y->left = T2;
		y->height = max(height(y->left),height(y->right))+1;
		x->height = max(height(x->left),height(x->right))+1;
		return x;
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
	Node* insertKeyInAVLtree(Node* root, int key){
		if(root==nullptr){
			Node* node = new Node();
			node->data = key;
			return node; 
		}
		if(key < root->data){
			root->left = insertKeyInAVLtree(root->left, key);
		}else if(key > root->data){
			root->right = insertKeyInAVLtree(root->right, key);
		}else{
			return root;
		}

		root->height = 1+max(height(root->left),height(root->right));
		int bfX = BalanceFactor(root);
		//left left case
		if( bfX > 1 and key < root->left->data){
			return rightRotate(root);
		}
		//right right case
		if( bfX < -1 and key > root->right->data){
			return leftRotate(root);
		}
		//left right case
		if( bfX > 1 and key > root->left->data){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		//right left case
		if( bfX < -1 and key < root->right->data){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	Node* deleteKeyInAVLtree(Node* root, int key){
		if(root==nullptr ) return nullptr;
		if(key < root->data) {
			root->left = deleteKeyInAVLtree(root->left, key);
		}
		else if(key > root->data){
			root->right = deleteKeyInAVLtree(root->right, key);
		}else{
			if(root->left==nullptr and root->right==nullptr){
				return nullptr;
			}else if(root->left == nullptr){
				Node* temp = root -> right;
				root=nullptr;
				return temp;
			}else if(root->right == nullptr){
				Node* temp=root->right;
				root=nullptr;
				return temp;
			}
				Node* minNode = findMinimum(root->right);
				root->data = minNode->data;
				root->right = deleteKeyInAVLtree(root->right, minNode->data); 
		}
		if(root==nullptr) return root;
		root->height = 1 + max(height(root->left),height(root->right));
		int bfX = BalanceFactor(root);
		//left left case
		if(bfX > 1 and BalanceFactor(root->left)>=0){
			return rightRotate(root);
		}
		//left right case
		if(bfX > 1 and BalanceFactor(root->left) < 0){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		//right right case
		if(bfX < -1 and BalanceFactor(root->right) <= 0){
			return leftRotate(root);
		}
		//right left case
		if(bfX < -1 and BalanceFactor(root->right) > 0){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
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
};

int main(){
	init();
	int n;
	cin>>n;
	AVLtree avt(n);
	for(int i=0;i<n;++i){
		int x;
		cin>>x;
		avt.root = avt.insertKeyInAVLtree(avt.root,x);
	}
	vector<int> v;
	avt.preOrder(avt.root, v);
	for(int x:v)cout<<x<<" ";
	cout<<endl;
	v.clear();
	avt.root = avt.deleteKeyInAVLtree(avt.root, 10);
	avt.preOrder(avt.root, v);
	for(int x:v)cout<<x<<" ";
	return 0;
}