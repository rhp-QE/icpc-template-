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
* 1�������жϴ� s �����Ƿ���Ե��︺��
* 2����������︺����
*       ���Ӷ��� s ���������е����̾���
*       �ߵ�Ȩֵ����Ϊ��
* 3��ʱ�临�Ӷ�Ϊ VE
*/
bool short_path(int s) {
	fill(d, d + 1 + n, inf);
	d[s] = 0;
	int c = 0;//�����ִΣ�
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
* 1���ж�����ͼ�Ƿ��и���
* 2��ֻ���ж��Ƿ��и���
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

int main() {

}