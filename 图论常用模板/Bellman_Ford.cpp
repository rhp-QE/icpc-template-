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

struct edge {
	int from, to;
	ll dist;
};
ll d[maxn];
vector<edge> edges;
int n, m;
/*
* 1）可以判断从 s 出发是否可以到达负环
* 2）如果不到达负环：
*       求解从顶点 s 出发到所有点的最短距离
*       边的权值可以为负
* 3）时间复杂度为 VE
*/
bool short_path(int s) {
	fill(d, d + 1 + n, inf);
	d[s] = 0;
	int c = 0;//更新轮次；
	while (true) {
		++c;
		bool update = false;
		for (edge& e : edges) {
			if (d[e.from] != inf && d[e.to] > d[e.from] + e.dist) {
				d[e.to] = d[e.from] + e.dist;
				update = true;
				if (c == n) return true;
			}
		}
		if (!update) break;
	}
	return false;
}

/*
* 1）判断整个图是否含有负环
* 2）只能判断是否含有负环
*/
bool find_negative_loop() {
	mem(d, 0);
	rep(i, i, n) {
		for (edge& e : edges) {
			if (d[e.to] > d[e.from] + e.dist) {
				d[e.to] = d[e.from] + e.dist;
				if (i == n) return true;
			}
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------

//队列优化判断负圈
const int maxn = 1e5 + 11;
struct edge {
    int from, to;
    ll dist;
};
namespace BF {
    int n, m; //点  边
    vector<edge> edges;
    vector<int> G[maxn];
    bool inq[maxn];
    int d[maxn], p[maxn], cnt[maxn];

    void addedge(int from, int to, int dist) {
        edges.push_back(edge{ from,to,dist });
        G[from].push_back((int)edges.size() - 1);
    }
    void init(int k) {
        n = k; for (int i = 1; i <= n; ++i) G[i].clear();
        edges.clear();
    }

    bool negativeC() {
        queue<int> que;
        mem(inq, 0); mem(cnt, 0);
	//求最短路时只需初始化起始点
        rep(i, 1, n) { d[i] = 0; inq[i] = true; que.push(i); }

        while (!que.empty()) {
            int u = que.front(); que.pop();
            inq[u] = false;
            for (const int& e_id : G[u]) {
                const edge& e = edges[e_id];
                if (d[e.to] > d[e.from] + e.dist) {
                    d[e.to] = d[e.from] + e.dist;
                    p[e.to] = e_id;
                    if (!inq[e.to]) {
                        que.push(e.to);
                        inq[e.to] = true;
                        if (++cnt[e.to] > n) return true;
                    }
                }
            }
        }
        return false;
    }
}
