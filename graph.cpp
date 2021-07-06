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
int random(int min, int max) { //range : [min, max]
   static bool first = true;
   if (first){  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

class GraphAdj{
public:
	int vertices;
	int edges;
	vector<int> *adjL;
	GraphAdj(int n){
		this->vertices = n;
		this->edges = 0;
		this->adjL = new vector<int>[n];
	}
	GraphAdj(int n, int e){
		this->vertices = n;
		this->edges = e;
		this->adjL = new vector<int>[n];
	}
	void addEdge(int x, int y){
		adjL[x].push_back(y);
	}
	void printGraph(){
		for(int i = 0;i<vertices;++i){
			for(int x:adjL[i]){
				cout<<i+1<<" "<<x+1<<'\n';
			}
		}
	}
	vector<vector<int>> bfs(int start){
		vector<vector<int>> res;
		vector<bool> visited(vertices, 0);
		queue<int> q;
		visited[start] = 1;
		q.push(start);
		while(!q.empty()){
			int count = q.size();
			vector<int> t;
			while(count--){
				int top = q.front(); q.pop();
				t.push_back(top);
				for(int x : adjL[top]){
					if(!visited[x]){
						visited[x] = 1;
						q.push(x);
					}
				}
			}
			res.push_back(t);
		}
		return res;
	}
	void dfsSource(int s, vector<bool> &visited, vector<int> &v){
		visited[s]=1;
		v.push_back(s);
		for(int x :adjL[s]){
			if(!visited[x])
				dfsSource(x, visited, v);
		}
	}
	void dfsAll(vector<int> &v){
		vector<bool> visited(vertices, 0);
		for(int i=0;i<vertices;++i){
			if(!visited[i])
				dfsSource(i, visited, v);
		}
	}
	void dfsTimeStamps(int s, int &time, vector<int> &in, vector<int> &out, vector<bool> &visited){
		visited[s]=1;
		in[s] = ++time;
		for(int x :adjL[s]){
			if(!visited[x])
				dfsTimeStamps(x, time, in, out, visited);
		}
		out[s] = ++time;
	}
	int findMotherVertex(){
		vector<int> v;
		vector<bool> visited(vertices, 0);
		int ans = 0;
		for(int i =0;i<vertices;++i){
			if(!visited[i]){
				dfsSource(i, visited, v);
				ans = i;
			}
		}
		v.clear();
		fill(visited.begin(), visited.end(), 0);
		dfsSource(ans, visited, v);
		for(int i = 0; i<vertices ;++i){
			if(!visited[i]) 
				return -1; 
		}
		return ans;
	}
	int MinNumEdges_or_ShortPthBw2Vert(int src, int dest){
		vector<bool> visited(vertices, 0);
		vector<int> dist(vertices, 0);
		queue<int> q;
		dist[src] = 0;
		visited[src] = 1;
		q.push(src);
		while(!q.empty()){
			int top = q.front(); q.pop();
			for(int x : adjL[top]){
				if(!visited[x]){
					dist[x] = dist[top] + 1;
					q.push(x);
					visited[x] = 1;
				}
			}
		}
		return dist[dest];
	}
	bool findDirCycleHelper(int s, vector<bool>& visited, vector<bool> &recStack){
		visited[s]=1;
		recStack[s]=1;
		for(int x: adjL[s]){
			if((!visited[x]) and findDirCycleHelper(x, visited, recStack)){
				return 1;
			}else if(recStack[x]){
				return 1;
			}
		}
		recStack[s]=0;
		return 0;
	}
	bool findDirCycle(){
		vector<bool> visited(vertices, 0), recStack(vertices, 0);
		for(int i=0;i<vertices;++i)
			if(!visited[i] and findDirCycleHelper(i, visited, recStack))
				return 1;
		return 0;
	}
	bool findUnDirCycleHelper(int s, vector<bool>& visited, int par){
		visited[s]=1;
		for(int x: adjL[s]){
			if(visited[x] and x!=par){
				return 1;
			}
			if((!visited[x]) and findUnDirCycleHelper(x, visited, s)){
				return 1;
			}
		}
		return 0;
	}
	bool findUnDirCycle(){
		vector<bool> visited(vertices, 0);
		for(int i=0;i<vertices;++i){
			if(!visited[i] and findUnDirCycleHelper(i, visited, -1)){
				return 1;
			}
		}
		return 0;
	}
	void topSortHelper(int s, vector<bool> &visited, stack<int> &st){
		visited[s] = 1;
		for(int x : adjL[s]){
			if(!visited[x]){
				topSortHelper(x, visited, st);
			}
		}
		st.push(s);
	}
	vector<int> topSort(){
		vector<bool> visited(vertices, 0);
		vector<int> v;
		stack<int> st;
		for(int i=0;i<vertices;++i){
			if(!visited[i]){
				topSortHelper(i, visited, st);
			}
		}
		while(!st.empty()){
			v.push_back(st.top()); st.pop();
		}
		return v;
	}
	int findUnDirCycleNLengthHelper(int s, int par, int n, vector<bool> &visited){
		visited[s]=1;
		int count = 0;
		if(n==0){
			visited[s] = 0;
			if(find(adjL[s].begin(),adjL[s].end(), par)!= adjL[s].end()){
				count++;
			}
			return count;
		}
		for(int x : adjL[s]){
			if(!visited[x]){
				count+=findUnDirCycleNLengthHelper(x, par, n-1, visited);
			}
		}
		visited[s] = 0;
		return count;
	}
	int findUnDirCycleNLength(int n){
		vector<bool> visited(vertices, 0);
		int count = 0;
		for(int i=0;i<vertices-(n-1);++i){
			count+=findUnDirCycleNLengthHelper(i, i, n-1, visited);
			visited[i]=1;
		}
		return count/2;
	}
	pair<int, vector<int>> BestFirstSearch(int src, int dest, vector<vector<int>> &dist){
		int cost = 0;
		vector<bool> visited(vertices, 0);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({0, src});
		visited[src] = 1;
		vector<int> v;
		while(!pq.empty()){
			pair<int, int> p = pq.top(); pq.pop();
			cost+=p.first;
			v.push_back(p.second);
			if(p.second==dest) break;
			for(int x : adjL[p.second]){
				if(!visited[x]){
					visited[x]=1;
					pq.push({dist[p.second][x],x});
				}
			}
		}
		return {cost, v};	
	}
	vector<int> KahnsTopSort(){
		vector<int> indegree(vertices, 0), res;
		for(int i=0;i<vertices;++i){
			for(int x : adjL[i])
				indegree[x]++;
		}
		queue<int> q;
		int count = 0;
		for(int i = 0; i < vertices; ++i){
			if(indegree[i]==0){
				q.push(i);
			}
		}
		while(!q.empty()){
			int top = q.front(); q.pop();
			res.push_back(top);
			for(int x : adjL[top]){
				if(--indegree[x] == 0)
					q.push(x);
			}
			count++;
		}
		if(count != vertices) {
			// cout<<"Cycle!!!!!!\n";
			return {};
		}
		return res;
	}
	void AlienDictionary(vector<string> &words, int MaxChar){
		GraphAdj g(MaxChar);
		int n = words.size();
		string word1, word2;
		for(int i = 0;i<n-1;++i){
			word1 = words[i], word2 = words[i+1];
			for(int j = 0 ; j<min(word1.size(), word2.size()); ++j){
				if(word1[j] != word2[j]){
					g.addEdge(word1[j]-'a', word2[j]-'a'); break;
				}
			}
		}
		vector<int> v = g.topSort();
		for(int x : v) cout<<(char)('a' + x)<<" ";
	}
	vector<pair<int, int>> PrimsMST(map<pair<int, int>, int> &mp){
		vector<bool> visited(vertices, 0);
		vector<int> parent(vertices, -1), dist(vertices, INT_MAX);
		priority_queue<pair<int, int> , vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({0, 0});
		while(!pq.empty()){
			pair<int, int> minKey = pq.top(); pq.pop();
			if(!visited[minKey.second]){
				visited[minKey.second] = 1;
				for(int x : adjL[minKey.second]){
					if(!visited[x] and dist[x] > mp[{minKey.second, x}]){
						dist[x] = mp[{minKey.second, x}];
						pq.push({dist[x], x});
						parent[x] = minKey.second;
					}
				} 
			}
		}
		vector<pair<int, int>> v;
		for(int i=1;i<vertices;++i){
			// cout<<parent[i]<<" "<<i<<'\n';
			v.push_back({parent[i], i});
		}
		return v;
	}
	vector<pair<int, int>> dijkstra(int s, map<pair<int, int>, int> &mp){
		vector<int> dist(vertices, INT_MAX);
		dist[s] = 0;
		priority_queue<pair<int, int> , vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({0, s});
		while(!pq.empty()){
			pair<int, int> p = pq.top(); pq.pop();
			for(int x : adjL[p.second]){
				if(dist[p.second]!=INT_MAX and dist[p.second] + mp[{p.second, x}] < dist[x]){
					dist[x] = dist[p.second] + mp[{p.second, x}];
					pq.push({dist[x], x});
				}
			}
		}
		vector<pair<int, int>> v;
		for(int i=0;i<vertices;++i){
			// cout<<parent[i]<<" "<<i<<'\n';
			v.push_back({i, dist[i]});
		}
		return v;
	}
	vector<pair<int, int>> BellmanFord(int s, vector<vector<int>> &edge){
		vector<int> dist(vertices, INT_MAX);
		dist[s] = 0;
		for(int i = 1; i< vertices; ++i){
			for(int j = 0; j < edges; ++j){
				int st = edge[j][0];
				int dst = edge[j][1];
				int wt = edge[j][2];
				if(dist[st]!=INT_MAX and dist[st] + wt < dist[dst]){
					dist[dst] = dist[st] + wt;
				}
			}
		}
		for(int j=0;j<edges;++j){
			int st = edge[j][0];
			int dst = edge[j][1];
			int wt = edge[j][2];
			if(dist[st]!=INT_MAX and dist[st]+wt<dist[dst]){
				cout<<"Negative Cycle\n";
				return {};
			}
		}
		vector<pair<int, int>> v;
		for(int i=0;i<vertices;++i){
			v.push_back({i, dist[i]});
		}
		return v;
	}
	int shortPathKedgeDirWtdG(int s, int d, map<pair<int, int>, int> &mp, int k){
		if(k==0 and s==d) return 0;
		if(k==1 and mp.find({s, d}) != mp.end())	return mp[{s, d}];
		if (k<=0) return INT_MAX;
		int ans = INT_MAX;
		for(int i = 0 ; i < vertices; ++i){
			if(s!=i and d!=i and mp.find({s, i})!=mp.end()){
				int spt = shortPathKedgeDirWtdG(i, d, mp, k-1);
				if(spt!=INT_MAX){
					ans = min(ans, spt+mp[{s, i}]);
				}
			}
		}	
		return ans;
	}
	//UNION FIND ALGORITHM
	void makeSet(vector<int> &parent, vector<int> &rank){
		for(int i=0;i<parent.size();++i){
			parent[i] = i;
			rank[i] = 0;
		}
	}
	//find Function
	int get(int k, vector<int> &parent){
		if(parent[k]!=k){
			parent[k] = get(parent[k], parent);
		}
		return parent[k];
	}
	//Union function
	void Union(int a, int b, vector<int> &parent, vector<int> &rank){
		int x = get(a, parent);
		int y = get(b, parent);
		if(x==y) return;
		if(rank[x]>rank[y]){
			parent[y] = x;
		}else if(rank[x] < rank[y]){
			parent[x] = y;
		}else{
			parent[x] = y;
			rank[y]++;
		}
	}
	struct comp{
		template <typename T>
		bool operator()(const T& l, const T& r){
			return l.second <= r.second;
		}
	};
	vector<pair<pair<int, int>, int>> KruskalAlgo(map<pair<int, int>, int> &mp){
		vector<pair<pair<int, int>, int>> mst;
		vector<int> parent(this->vertices);
		vector<int> rank(this->vertices);
		makeSet(parent, rank);
		set<pair<pair<int, int>, int>, comp> S(mp.begin(), mp.end());
		while(mst.size()!=this->vertices-1){
			pair<pair<int,int>, int> p = *S.begin();
			S.erase(S.begin());
			int x = get(p.first.first, parent);
			int y = get(p.first.second, parent);		
			if(x!=y){
				mst.push_back(p);
				Union(x, y, parent, rank);
			}
		}
		return mst;
	}

};

class GraphMat{
public:
	int vertices;
	int edges;
	vector<vector<int>> adjMat;
	GraphMat(int n){
		this->vertices = n;
		this->edges = 0;
		this->adjMat.resize(n, vector<int>(n, 0));
	}
	GraphMat(int n, int e){
		this->vertices = n;
		this->edges = e;
		this->adjMat.resize(n, vector<int>(n, 0));
	}
	void addEdge(int x, int y){
		this->adjMat[x][y]=1;
	}
	void printGraph(){
		for(int i = 0;i<vertices;++i){
			for(int j=0;j<vertices;++j){
				if(adjMat[i][j])
					cout<<i+1<<" "<<j+1<<'\n';
			}
		}
	}
	vector<vector<int>> bfs(int start){
		vector<vector<int>> res;
		vector<bool> visited(vertices, 0);
		queue<int> q;
		visited[start] = 1;
		q.push(start);
		while(!q.empty()){
			int count = q.size();
			vector<int> t;
			while(count--){
				int top = q.front(); q.pop();
				t.push_back(top);
				for(int i = 0; i < adjMat[top].size(); ++i){
					if(!visited[i] and adjMat[top][i]){
						visited[i] = 1;
						q.push(i);
					}
				}
			}
			res.push_back(t);
		}
		return res;
	}
	void dfsSource(int s, vector<bool> &visited, vector<int> &v){
		visited[s]=1;
		v.push_back(s);
		for(int i = 0 ;i < vertices; ++i){
			if(!visited[i] and adjMat[s][i])
				dfsSource(i, visited, v);
		}
	}
	void dfsAll(vector<int> &v){
		vector<bool> visited(vertices, 0);
		for(int i=0;i<vertices;++i){
			if(!visited[i])
				dfsSource(i, visited, v);
		}
	}
	int findMotherVertex(){
		vector<int> v;
		vector<bool> visited(vertices, 0);
		int ans = 0;
		for(int i =0;i<vertices;++i){
			if(!visited[i]){
				dfsSource(i, visited, v);
				ans = i;
			}
		}
		v.clear();
		fill(visited.begin(), visited.end(), 0);
		dfsSource(ans, visited, v);
		for(int i = 0; i<vertices ;++i){
			if(!visited[i]) 
				return -1; 
		}
		return ans;
	}
	int MinNumEdges_or_ShortPthBw2Vert(int src, int dest){
		vector<bool> visited(vertices, 0);
		vector<int> dist(vertices, 0);
		queue<int> q;
		dist[src] = 0;
		visited[src] = 1;
		q.push(src);
		while(!q.empty()){
			int top = q.front(); q.pop();
			for(int i=0;i<adjMat[top].size();++i){
				if(!visited[i] and adjMat[top][i]){
					dist[i] = dist[top] + 1;
					q.push(i);
					visited[i] = 1;
				}
			}
		}
		return dist[dest];
	}
	bool findDirCycleHelper(int s, vector<bool>& visited, vector<bool> &recStack){
		visited[s]=1;
		recStack[s]=1;
		for(int x=0; x < adjMat[s].size();++x){
			if((!visited[x] and adjMat[s][x]) and findDirCycleHelper(x, visited, recStack)){
				return 1;
			}else if(adjMat[s][x] and recStack[x]){
				return 1;
			}
		}
		recStack[s]=0;
		return 0;
	}
	bool findDirCycle(){
		vector<bool> visited(vertices, 0), recStack(vertices, 0);
		for(int i=0;i<vertices;++i)
			if(!visited[i] and findDirCycleHelper(i, visited, recStack))
				return 1;
		return 0;
	}
	bool findUnDirCycleHelper(int s, vector<bool>& visited, int par){
		visited[s]=1;
		for(int x=0; x < adjMat[s].size();++x){
			if(visited[x] and adjMat[s][x] and x!=par){
				return 1;
			}
			if((!visited[x]) and adjMat[s][x] and findUnDirCycleHelper(x, visited,s)){
				return 1;
			}
		}
		return 0;
	}
	bool findUnDirCycle(){
		vector<bool> visited(vertices, 0);
		for(int i=0;i<vertices;++i){
			if(!visited[i] and findUnDirCycleHelper(i, visited, -1)){
				return 1;
			}
		}
		return 0;
	}
	void topSortHelper(int s, vector<bool> &visited, stack<int> &st){
		visited[s] = 1;
		for(int x = 0; x < adjMat[s].size(); ++x){
			if(!visited[x] and adjMat[s][x]){
				topSortHelper(x, visited, st);
			}
		}
		st.push(s);
	}
	vector<int> topSort(){
		vector<bool> visited(vertices, 0);
		vector<int> v;
		stack<int> st;
		for(int i=0;i<vertices;++i){
			if(!visited[i]){
				topSortHelper(i, visited, st);
			}
		}
		while(!st.empty()){
			v.push_back(st.top()); st.pop();
		}
		return v;
	}
	int findUnDirCycleNLengthHelper(int s, int par, int n, vector<bool> &visited){
		visited[s]=1;
		int count = 0;
		if(n==0){
			visited[s] = 0;
			if(adjMat[s][par]){
				count++;
			}
			return count;
		}
		for(int x = 0; x < adjMat[s].size(); ++x){
			if(!visited[x] and adjMat[s][x]){
				count+=findUnDirCycleNLengthHelper(x, par, n-1, visited);
			}
		}
		visited[s] = 0;
		return count;
	}
	int findUnDirCycleNLength(int n){
		vector<bool> visited(vertices, 0);
		int count = 0;
		for(int i=0;i<vertices-(n-1);++i){
			count+=findUnDirCycleNLengthHelper(i, i, n-1, visited);
			visited[i]=1;
		}
		return count/2;
	}
	bool findNegCycleFloydWarshall(vector<vector<int>> &dist){
		for(int k = 0;k < vertices; ++k){
			for(int i = 0; i < vertices ; ++i){
				for(int j = 0; j < vertices; ++j){
					if(dist[i][k] + dist[k][j] < dist[i][j]){
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		for(int i=0;i<vertices;++i){
			if(dist[i][i] < 0) return 1;
		}
		return 0;
	}
	vector<int> KahnsTopSort(){
		vector<int> indegree(vertices, 0), res;
		for(int i=0;i<vertices;++i){
			for(int x = 0 ; x < vertices ; ++x)
				if(adjMat[i][x])
					indegree[x]++;
		}
		queue<int> q;
		int count = 0;
		for(int i = 0; i < vertices; ++i){
			if(indegree[i]==0){
				q.push(i);
			}
		}
		while(!q.empty()){
			int top = q.front(); q.pop();
			res.push_back(top);
			for(int x = 0; x < adjMat[top].size(); ++x){
				if(adjMat[top][x])
					if(--indegree[x] == 0)
						q.push(x);
			}
			count++;
		}
		if(count != vertices) {
			// cout<<"Cycle!!!!!!\n";
			return {};
		}
		return res;
	}
	pair<int, vector<int>> BestFirstSearch(int src, int dest, vector<vector<int>> &dist){
		int cost = 0;
		vector<bool> visited(vertices, 0);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({0, src});
		visited[src] = 1;
		vector<int> v;
		while(!pq.empty()){
			pair<int, int> p = pq.top(); pq.pop();
			cost+=p.first;
			v.push_back(p.second);
			if(p.second==dest) break;
			for(int x = 0; x < vertices; ++x){
				if(!visited[x] and adjMat[p.second][x]){
					visited[x]=1;
					pq.push({dist[p.second][x],x});
				}
			}
		}
		return {cost, v};	
	}
};

int main(){
	init();
	int n , m;
	cin>>n>>m;
	vector<int> parent(n);
	vector<int> rank(n);
	GraphAdj g(n);
	g.makeSet(parent, rank);
	while(m--){
	    string s;
	    cin>>s;
	    int x;
	    cin>>x;
	    int y;
	    cin>>y;
	    x--;
	    y--;
	    if(s=="union"){
	        g.Union(x, y, parent, rank);
	    }else{
	        int a = g.get(x, parent);
	        int b = g.get(y, parent);
	        if(a==b){
	            cout<<"YES\n";
	        }else cout<<"NO\n";
	    }
	}
	return 0;
}
// 0 0
// 1 4
// 2 12
// 3 19
// 4 21
// 5 11
// 6 9
// 7 8
// 8 14
