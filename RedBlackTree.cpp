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
enum Color{RED, BLACK};

struct Node{
	int data;
	Node* left;
	Node* right;
	Node* parent;
	bool color;
	Node(int data){
		this->data=data;
		this->left=nullptr;
		this->right=nullptr;
		this->parent = nullptr;
		this->color = RED;
	}
};

class RedBlackTree{
public:
	int N;
	Node* root;
	RedBlackTree(int N){
		this->N = N;
		this->root=nullptr;
	}
	Node* insertKeyInBST(Node* root, Node* node){
		if(root==nullptr){
			root = node;
			return root;
		}
		else if(root->data > node->data){
			root->left = insertKeyInBST(root->left, node);
			root->left->parent = root;
		}else if(root->data < node-> data){
			root->right = insertKeyInBST(root->right, node);
			root->right->parent = root;
		}
		return root;
	}
	void leftRotate(Node* &root, Node* &node){
		Node* node_right = node->right;
		node->right = node_right -> left;
		if(node->right!=nullptr) node->right->parent = node;
		node_right -> parent = node->parent;
		if(node -> parent == nullptr) root = node_right;
		else if(node == node->parent->left) node->parent->left = node_right;
		else node->parent->right = node_right;
		node_right->left = node;
		node->parent = node_right;
	}
	void rightRotate(Node* &root, Node* &node){
		Node* node_left = node->left;
		node->left = node_left ->right;
		if(node->left!=nullptr) node->left->parent = node;
		node_left->parent = node->parent;
		if(node->parent==nullptr) root = node_left;
		else if(node==node->parent->left) node->parent->left = node_left;
		else node->parent->right = node_left;
		node_left->right = node;
		node->parent = node_left; 
	}
	void RBTREE_INSERTION_FIXUP(Node* &root, Node* &node){
		Node* node_parent = nullptr;
		Node* node_grandFather = nullptr;

		while(node!=root and node->color != BLACK and node->parent->color == RED){
			node_parent = node->parent;
			node_grandFather = node->parent->parent;

			if(node_parent == node_grandFather->left){
				Node* node_uncle = node_grandFather->right;
				if(node_uncle!=nullptr and node_uncle->color == RED){
					node_grandFather->color = RED;
					node_parent->color = BLACK;
					node_uncle->color = BLACK;
					node = node_grandFather; 
				}else{
					if(node == node_parent->right){
						leftRotate(root, node_parent);
						node = node_parent;
						node_parent = node->parent;
					}
					rightRotate(root, node_grandFather);
					swap(node_parent->color, node_grandFather->color);
					node = node_parent; 
				}
			}
		 else{
			Node* node_uncle = node_grandFather ->left;
			if(node_uncle!=nullptr and node_uncle->color == RED){
				node_grandFather->color = RED;
				node_parent->color = BLACK;
				node_uncle->color = BLACK;
				node=node_grandFather; 
			}else{
				if(node == node_parent->left){
					rightRotate(root, node_parent);
					node = node_parent;
					node_parent = node->parent;
				}
				leftRotate(root, node_grandFather);
				swap(node_parent->color, node_grandFather->color);
				node = node_parent;
			}
		}
	}
		root->color = BLACK;
	}
	void insertKeyInRBtree( int key){
		Node* node = new Node(key);
		this->root = insertKeyInBST(this->root, node);
		RBTREE_INSERTION_FIXUP(this->root, node);
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
	void levelOrder(Node* root, vector<int> &v){
		if(root==nullptr) return;
		queue<Node* > q;
		q.push(root);
		while(!q.empty()){
			Node* temp = q.front();
			v.push_back(temp->data);
			q.pop();
			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
};
int main(){
	init();
	int N;
	cin>>N;
	RedBlackTree rbt(N);
	for(int i=0;i<N;++i){
		int x;
		cin>>x;
		rbt.insertKeyInRBtree( x);
	}	
	vector<int> v;
	rbt.inOrder(rbt.root, v);
	for(int x : v) cout<<x<<" ";
	cout<<~5<<'\n';
	int a[]={10,20,30};
	cout<<*a+1<<'\n';
	return 0;
}