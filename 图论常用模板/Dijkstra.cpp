#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
#define l(o) (o<<1)
#define r(o) (o<<1)|1
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define mem(a,b) memset(a,b,sizeof(a))
#define inf 1LL<<60
typedef long long ll;
using namespace std;
template<class A>void read(A& a) {
	a = 0; int c = getchar(), f = 0;
	for (; !isdigit(c); c = getchar()) f |= c == '-';
	for (; isdigit(c); c = getchar()) a = a * 10 + (c ^ 48);
	if (f) a = -a;
}
template<class A, class ...B>
void read(A& a, B&...b) { read(a); read(b...); }
//------------------------------------------------------------
const int maxn = 1e5 + 11;

struct node {
	int u; ll dist;
	bool operator>(const node& rhs)const {
		return dist > rhs.dist;
	}
};

struct edge {
	int from, to; ll dist;
};
vector<edge> edges;
vector<int> G[maxn];//图（边号）
ll dist[maxn];//距离
int path[maxn];//路径 (边号)
bool vis[maxn];//是否从该点松弛过
int n, m, s, t;
//顶点数  边数  起始点  终点
void init() {
	//顶点编号为 1~n
	edges.clear();
	rep(i, 1, n) G[i].clear();
	fill(dist + 1, dist + 1 + n, inf);
	mem(vis, 0);
}
void addedge(int from, int to, ll dist) {//添加单向边
	edges.push_back(edge{ from,to,dist });
	G[from].push_back((int)edges.size() - 1);
}
void diji() {
	priority_queue<node, vector<node>, greater<node>> que;
	dist[s] = 0;
	que.push(node{ s,0 });
	while (!que.empty()) {
		node curnode = que.top(); que.pop();
		if (vis[curnode.u]) continue;
		vis[curnode.u] = true;
		for (int e_id : G[curnode.u]) {
			edge& e = edges[e_id];
			if (dist[e.to] > dist[e.from] + e.dist) {
				dist[e.to] = dist[e.from] + e.dist;
				path[e.to] = e_id;
				que.push(node{ e.to,dist[e.to] });
			}
		}
	}
}

int main() {
	read(n, m, s, t);
	init();
	int a, b; ll c;
	rep(i, 1, m) {
		read(a, b, c);
		addedge(a, b, c);
	}
	diji();
}

