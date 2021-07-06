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
	Node(){
		data=0;
		left=nullptr;
		right=nullptr;
	}
};

class BinaryTree{
public:
	int N;
	Node* root;
	BinaryTree(int N){
		this->N = N;
		this->root=nullptr;
	}
	int countNodes(Node* root){
		if(root==nullptr) return 0;
		return 1+ countNodes(root->left)+countNodes(root->right);
	}
	void insertNode(Node* node,int val){
		if(node==nullptr){
			node = new Node();
			node->data = val;
			this->root=node;
			return ;
		}
		queue<Node*> q;
		q.push(node);
		while(q.size()>0){
			Node* tmp = q.front();
			q.pop();
			if(tmp->left==nullptr){
				tmp->left = new Node;
				tmp->left->data = val;
				return ;
			}
			if(tmp->right == nullptr){
				tmp->right = new Node;
				tmp->right->data = val;
				return ;
			}
			q.push(tmp->left);
			q.push(tmp->right);
		}
	}	
	Node* findParentNodewithKey(Node* node, int key){
		if(node==nullptr)return nullptr;
		queue<Node*> q;
		q.push(node);
		while(q.size()>0){
			Node* tmp = q.front();
			q.pop();
			if(tmp->left!=nullptr){
				q.push(tmp->left);
				if(tmp->left->data==key){
					return tmp;
				}
			}
			if(tmp->right != nullptr){
				q.push(tmp->right);
				if(tmp->right->data==key){
					return tmp;
				}
			}
			
		}
		return nullptr;
	}
	Node* findRightMostLeafNode(Node* node){
		if(node==nullptr) return nullptr;
		else if(node->right!=nullptr){
			return findRightMostLeafNode(node->right);
		}else if(node->left!=nullptr){
			return findRightMostLeafNode(node->left);
		}else if(node->left==nullptr and node->right==nullptr){
			return node;
		}else{
			return nullptr;
		}
	}
	void deleteKey(Node* node, int key){
		if(node==nullptr) return;
		Node* tmp = findParentNodewithKey(this->root,key);
		Node* rtLNode = findRightMostLeafNode(this->root);
		int x= rtLNode->data;
		rtLNode = findParentNodewithKey(this->root,x);
		if(tmp==nullptr){
			if(this->root!=nullptr and this->root->data==key){
				if(rtLNode!=nullptr and rtLNode->left!=nullptr and rtLNode->left->data==x) rtLNode->left=nullptr;
				if(rtLNode!=nullptr and rtLNode->right!=nullptr and rtLNode->right->data==x) rtLNode->right=nullptr;
				if(rtLNode!=nullptr) this->root->data = x;
				else this->root=nullptr;
			}
			return;
		}
		Node* t;
		if(tmp->left!=nullptr and tmp->left->data==key) t = tmp->left;
		if(tmp->right!=nullptr and tmp->right->data==key) t = tmp->right;
		if(rtLNode->left!=nullptr and rtLNode->left->data==x) rtLNode->left=nullptr;
		else rtLNode->right=nullptr;
		if(rtLNode!=nullptr)t->data = x;
	}
	void printTree(Node* root){
		if(root==nullptr) return;
		printTree(root->left);
		cout<<root->data<<' ';
		printTree(root->right);
	}
	void preOrder(Node* root){
		if(root==nullptr) return;
		cout<<root->data<<' ';
		preOrder(root->left);
		preOrder(root->right);
	}
	void postOrder(Node* root){
		if(root==nullptr) return;	
		postOrder(root->left);
		postOrder(root->right);
		cout<<root->data<<' ';
	}
	void InOrder(Node* root){
		if(root==nullptr) return;
		InOrder(root->left);
		cout<<root->data<<' ';
		InOrder(root->right);
	}
	void BFSorderTraversal(Node* root){
		if(root==nullptr) return;
		queue<Node*> q;
		q.push(root);
		while(q.size()>0){
			Node* temp = q.front();
			q.pop();
			cout<<temp->data<<" ";
			if(temp->left!=nullptr) q.push(temp->left);
			if(temp->right!=nullptr) q.push(temp->right);
		}
	}
	void MorrisInorderTraversal(Node* root){
		Node* current;
		Node* pred;
		if(root == nullptr) return;
		current = root;
		while(current != nullptr){
			if(current->left == nullptr){
				cout<<current -> data <<" ";
				current =  current -> right;
			}else{
				pred = current -> left;
				while( pred -> right != nullptr and pred -> right != current){
					pred = pred -> right;
				}
				if(pred -> right == nullptr){
					pred -> right = current;
					current = current -> left;
				} 
				else{
					pred -> right = nullptr;
					cout<<current -> data<<" ";
					current = current ->right;
				}
			}
		}
	}
	int sumOfTree(Node* root){
			if(root == nullptr) return 0;
			int SumOfLeftTree = sumOfTree(root->left);
			int SumOfRightTree = sumOfTree(root->right);
			return root->data + SumOfLeftTree + SumOfRightTree;
	}
	int Rtindex;
	void Post_fromPreIn(int in[], int pre[], int s, int e, int n, map<int, int> &mp, vector<int> &v){
		if(s>e) return;
		int Possible_root_of_subtree = mp[pre[Rtindex++]];
		Post_fromPreIn(in, pre, s, Possible_root_of_subtree-1,n,mp, v);
		Post_fromPreIn(in, pre, Possible_root_of_subtree+1,e,n,mp, v);
		v.push_back(in[Possible_root_of_subtree]);
	}
	vector<int> postOrder_from_PreInMain(int in[], int pre[], int n){
		map<int, int> mp;
		for(int i=0;i<n;++i){
			mp[in[i]]=i;
		}
		Rtindex=0;
		vector<int> v;
		Post_fromPreIn(in, pre, 0, n-1, n, mp, v);
		return v;
	}	
	vector<Node*> PossibleInorderTrees(int in[], int s, int e){
		vector<Node*> tree;
		if(s>e){
			tree.push_back(nullptr);
			return tree;
		}
		for(int i=s;i<=e;++i){
			vector<Node*> lSubtree = PossibleInorderTrees(in,s,i-1);
			vector<Node*> rSubtree = PossibleInorderTrees(in, i+1, e);	
			for(int j=0;j<lSubtree.size();++j){
				for(int k=0;k<rSubtree.size();++k){
					Node* node = new Node;
					node->data = in[i];
					node->left = lSubtree[j];
					node->right = rSubtree[k];
					tree.push_back(node);
				}
			}
		}
		return tree;
	}
	vector<vector<int>> BFS_Spiral_traversal(Node* root){
		vector<vector<int>> res;
		queue<Node*> q;
		if(root!=nullptr){
			q.push(root);
			while(q.size()>0){
				int count=q.size();
				vector<int> v;
				while(count--){
					Node* node = q.front();
					v.push_back(node->data);
					q.pop();
					if(node->left!=nullptr){
						q.push(node->left);
					}
					if(node->right!=nullptr){
						q.push(node->right);
					}
				}
				res.push_back(v);
			}
			for(int i=0;i<res.size();++i){
				if((i&1)==0){
					reverse(res[i].begin(),res[i].end());
				}
			}
		}	
		return res;	
	}
	void Diag_Traversal_Helper(Node* root, int d, map<int, vector<int>> &mp){
		if(root==nullptr) return;
		mp[d].push_back(root->data);
		if(root->right!=nullptr)
			Diag_Traversal_Helper(root->right, d, mp);
		if(root->left!=nullptr)
			Diag_Traversal_Helper(root->left, d+1, mp);
	}
	vector<vector<int>> DiagonalTraversalBinaryTree(Node* root){
		vector<vector<int>> res;
		map<int, vector<int>> mp;
		Diag_Traversal_Helper(root, 0, mp);
		for(auto it = mp.begin();it!=mp.end();it++){
			vector<int> v;
			for(int x : mp[it->first]){
				v.push_back(x);
			}
			if(v.size()>0) res.push_back(v);
		}
		return res;
	}
	void findLeftBoundary(Node* root , vector<int> &v){
		if(root==nullptr) return;
		if(root->left!=nullptr){
			v.push_back(root->data);
			findLeftBoundary(root->left, v);
		}else if(root->right!=nullptr){
			v.push_back(root->data);
			findLeftBoundary(root->right, v);
		}
	}
	void findRightBoundary(Node* root , vector<int> &v){
		if(root==nullptr) return;
		if(root->right!=nullptr){
			findRightBoundary(root->right, v);
			v.push_back(root->data);
		}else if(root->right!=nullptr){
			findRightBoundary(root->left, v);
			v.push_back(root->data);
		}
	}
	void findLeaves(Node* root, vector<int> &v){
		if(root==nullptr)
			return ;
		findLeaves(root->left, v);
		if(root->left==nullptr and root->right==nullptr) v.push_back(root->data);
		findLeaves(root->right, v);
	}
	vector<vector<int>> findBoundaryTraversal(Node *root){
		vector<int> lbdry, rbdry, lvs;
		vector<vector<int>> res;
		if(root!=nullptr){
		findLeftBoundary(root->left, lbdry);
		findLeaves(root->left, lvs);
		findLeaves(root->right, lvs);
		findRightBoundary(root->right,rbdry);
		vector<int> rt;
		rt.push_back(root->data);
		res.push_back(rt);
		res.push_back(lbdry);
		res.push_back(lvs);
		res.push_back(rbdry);
		}
		return res;
	}

	//O(n^2) approach needs to be updated to O(n)
	void modifyTreeToPreOrder(Node* root){
		if(root==nullptr) return;
		modifyTreeToPreOrder(root->left);
		modifyTreeToPreOrder(root->right);
		if(root->left!=nullptr){
			if(root->right!=nullptr){
				Node* temp=root->left;
				while(temp->right!=nullptr){
						temp=temp->right;
					}
				temp->right = root->right;
				root->right=root->left;
				root->left=nullptr;
			}else{
				root->right = root->left;
				root->left=nullptr;
			}
		}
	}

	int ModifyTreeToSumTree(Node* root){
		if(root==nullptr) return 0;
		int oldValue = root->data;
		int leftSubtreeSum = ModifyTreeToSumTree(root->left);
		int rightSubtreeSum = ModifyTreeToSumTree(root->right);
		root->data = leftSubtreeSum + rightSubtreeSum;
		return root->data + oldValue;
 	}

 	bool CheckPrePostInOfBT(int in[], int pre[], int post[], int n){
 		vector<int> possPost = postOrder_from_PreInMain(in, pre, n);
 		if(possPost.size() != n) return 0; 
 		for(int i = 0;i < n;++i ) {
 			if(!(possPost[i]==post[i])) return 0;
 		}
 		return 1;
 	}

 	int MaximumPathSumBetween2Leaves(Node* root, int &res){
 		if(root==nullptr) return 0;
 		if(root->left==nullptr and root->right ==nullptr){
 			return root->data;
 		}

 		int lSubtreeBranchMaxSum = MaximumPathSumBetween2Leaves(root->left,res);
 		int rSubtreeBranchMaxSum = MaximumPathSumBetween2Leaves(root->right,res);
 		if(root->left !=nullptr and root->right !=nullptr){
 			res = max(res, lSubtreeBranchMaxSum+rSubtreeBranchMaxSum+root->data);
 			return max(lSubtreeBranchMaxSum, rSubtreeBranchMaxSum) + root->data;
 		}
 		return ((root->left==nullptr)?rSubtreeBranchMaxSum+ root->data:lSubtreeBranchMaxSum+ root->data) ;
 	}

 	int maximumSpiralOrderTraversalSum(Node* root){
 		vector<vector<int>> v = BFS_Spiral_traversal(root);
 		vector<int> res;
 		for(vector<int> a: v){
 			for(int x : a){
 				res.push_back(x);
 			}
 		}
 		if(v.size()==0) return INT_MIN;
 		int curr=res[0];
 		int maxsum = res[0];
 		for(int i=1;i<res.size();++i){
 			curr = max(res[i], curr+res[i]);
 			maxsum = max(maxsum,curr);
 		}
 		return maxsum;
 	}

 	Node* LCA(Node* root, int x, int y){
 		if(root==nullptr) return nullptr;
 		if(root->data==x||root->data==y) return root;

 		Node* LeftLCA = LCA(root->left,x,y);
 		Node* rightLCA = LCA(root->right,x,y);
 		if(LeftLCA !=nullptr and rightLCA !=nullptr) return root;
 		return (LeftLCA !=nullptr? LeftLCA:rightLCA);
 	}

 	int MaxDepthOrHeight(Node* root){
 		if(root==nullptr) return 0;
 		if(root->left==nullptr and root->right==nullptr) return 0;
 		return max(MaxDepthOrHeight(root->left), MaxDepthOrHeight(root->right))+1;
 	}

 	int DiameterOfTreeUsingHeight(Node* root, int &ans){
 		if(root==nullptr) return 0;
 		int leftHeight = DiameterOfTreeUsingHeight(root->left, ans);
 		int rightHeight = DiameterOfTreeUsingHeight(root->right, ans);
 		ans = max(ans, 1+leftHeight+rightHeight);
 		return 1+max(leftHeight, rightHeight);
 	}

 	void bottomViewOfBinaryTreeHelper(Node* root, int hd, int level, map<int, pair<int, int>> &mp,vector<int> &v){
 		if(root==nullptr) return ;
 		if(mp.find(hd)==mp.end()){
 			mp[hd] = {root->data, level};
 		}else{
 			if(mp[hd].second <= level){
 				mp[hd].first = root->data;
 				mp[hd].second = level;
 			}
 		}
 		bottomViewOfBinaryTreeHelper(root->left, hd-1,level+1,mp,v);
 		bottomViewOfBinaryTreeHelper(root->right, hd+1,level+1,mp,v);
 	}

 	vector<int> bottomViewOfBinaryTreeMain(Node* root){
 		map<int, pair<int, int>> mp;
 		vector<int> v;
 		bottomViewOfBinaryTreeHelper(root, 0, 0, mp, v);
 		for(auto it = mp.begin();it!=mp.end();++it){
 			v.push_back(it->second.first);
 		}
 		return v;
 	}
 	bool isCompleteBinaryTree(Node* root, int i, int n){
 		if(root==nullptr) return 1;
 		if(i > n) return 0;
 		return isCompleteBinaryTree(root->left,2*i,n) and isCompleteBinaryTree(root->right,2*i+1,n);
 	}
 	bool MaxHeapcheckerHelper(Node* root){
 		if(root==nullptr)return 1;
 		if(root->left==nullptr and root->right==nullptr) return 1;
 		if(root->right==nullptr) return root->data >= root->left->data;
 		else{
 			if(root->data >= root->left->data and root->data >= root->right->data){
 				return MaxHeapcheckerHelper(root->left) and MaxHeapcheckerHelper(root->right);
 			}else{
 				return 0;
 			}
 		} 
 	}
 	bool isMaxHeap(Node* root){
 		int n = countNodes(root);
 		return isCompleteBinaryTree(root,1,n) and MaxHeapcheckerHelper(root);
 	}
};

int main(){
	init();
	int N;
	cin>>N;
	BinaryTree bt(N);
	for(int i=0;i<N;++i){
		int x;
		cin>>x;
		bt.insertNode(bt.root,x);
	}
	// int in[] = { 4, 2, 5, 1, 3, 6 };
 //    int pre[] = { 1, 2, 4, 5, 3, 6 };
	// bt.postOrder_from_PreInMain(in, pre, 6);
	// int inorder[] = {4, 5, 7};
	// vector<Node*> v = bt.PossibleInorderTrees(inorder, 0, 2);
	// for(int i=0;i<v.size();++i){
	// 	bt.preOrder(v[i]);
	// 	cout<<endl;
	// }
	// vector<vector<int>> vt = bt.findBoundaryTraversal(bt.root);
	// for(vector<int> &a:vt){
	// 	for(int x : a){
	// 		cout<<x<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<bt.maximumSpiralOrderTraversalSum(bt.root)<<'\n';
	cout<<bt.isMaxHeap(bt.root)<<'\n';
}