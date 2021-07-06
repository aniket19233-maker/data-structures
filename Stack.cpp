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

struct Node{
	int data;
	Node* next;
	Node(){
		this->data=0;
		this->next = nullptr;
	}
	Node(int data){
		this->data = data;
		this->next = nullptr;
	}
};

class StackLL{
public:
	int size;
	Node* root;
	StackLL(){
		this->size = 0;
		this->root = nullptr;
	}
	int getSize(){
		return this->size;
	}
	void pop(){
		if(this->size > 0){
			this->root = this->root->next;
			this->size--;
		}
	}
	void push(int data){
		if(this->size==0){
			this->root=new Node(data);
		}else{
			Node* node = new Node(data);
			Node* temp =this->root;
			this->root = node;
			this->root->next = temp;
		}
		this->size++;
	}
	int top(){
		if(this->size > 0){
			return this->root->data;
		} 
		return INT_MIN;
	}
	void printStack(){
		Node* temp = this->root;
		while(temp!=nullptr){
			cout<<temp->data<<" ";
			temp = temp->next;
		}
	}
};

class StackArr{
public:
	int size;
	vector<int> stack;
	StackArr(){
		this->size = 0;
	}
	int getSize(){
		return this->size;
	}
	void pop(){
		if(this->size>0){
			stack.pop_back();
			this->size--;
		}
	}
	void push(int data){
		this->size++;
		stack.push_back(data);
	}
	int top(){
		if(this->size > 0) return stack[size-1];
		else return INT_MIN;
	}
	void printStack(){
		for(int x : stack) cout<<x<<" ";
	}
};

int main(){
	init();
	int N;
	cin>>N;
	StackLL st;
	while(N--){
		int x;
		cin>>x;
		if(x==1){
			int a;cin>>a;
			st.push(a);
		}else if(x==2){
			cout<<st.top()<<'\n';st.pop();
		}else{
			cout<<st.top()<<'\n';
		}
	}
	return 0;
}