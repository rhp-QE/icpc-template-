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
/*
* 网络流Dinic O(EV)
*/
const int maxn = 1e5 + 11;//最大顶点数
struct edge {
	int from, to, rev;
	ll cap;
};
int s, t;
vector<edge> edges;
vector<int> G[maxn];
int level[maxn];
int iter[maxn];
void add(int from, int to, ll cap) {
	edges.push_back(edge{ from,to,(int)edges.size() + 1,cap });
	G[from].push_back((int)edges.size() - 1);
	edges.push_back(edge{ to,from,(int)edges.size() - 1,0 });
	G[to].push_back((int)edges.size() - 1);
}
void bfs(int s) {
	mem(level, -1);
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int v = que.front(); que.pop();
		for (int e_id : G[v]) {
			edge& e = edges[e_id];
			if (e.cap <= 0 || level[e.to] >= 0) continue;
			level[e.to] = level[e.from] + 1;
			que.push(e.to);
		}
	}
}

ll dfs(int v, ll f) {
	if (v == t) return f;
	for (int& i = iter[v]; i < G[v].size(); ++i) {
		edge& e = edges[G[v][i]];
		if (e.cap <= 0 || level[v] >= level[e.to]) continue;
		ll d = dfs(e.to, min(f, e.cap));
		if (d <= 0) continue;
		e.cap -= d;
		edges[e.rev].cap += d;
		return d;
	}
	return 0;
}

ll max_flow() {
	ll flow = 0;
	while (true) {
		bfs(s);
		if (level[t] < 0) return flow;
		mem(iter, 0);
		ll d;
		while ((d = dfs(s, inf)) > 0) flow += d;
	}
}

int main() {
	int n, m;
	read(n, m, s, t);
	int a, b;
	ll c;
	rep(i, 1, m) {
		read(a, b, c);
		add(a, b, c);
	}
	cout << max_flow() << endl;
}