#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
#define lo (o<<1)
#define ro (o<<1)|1
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
* 1）线段树只可以维护可加类信息。所谓可加类信息就是大区间的信息可以由若干子区间的信息合并得到，比如区间和，区间最小值和
* 区间最大值。
* 2）要注意懒惰标记的使用，懒惰标记就是还欠子区间的操作。当有多个懒惰标记时，要提前定义好懒惰标记的下放顺序。
*/
const int maxn = 1e5 + 11;
int ql, qr;
ll v, md;
int num[maxn];
struct node {
	int l, r;
	ll sum;              //定义维护信息
	ll opa, opm;         //定义懒惰标记
};
node a[maxn * 4];

void calc_mult(int o,ll op) {
	a[o].opa = a[o].opa * op % md; a[o].opm = a[o].opm * op % md;
	a[o].sum = a[o].sum * op % md;
}
void calc_add(int o, ll op) {
	a[o].opa = (a[o].opa + op) % md;
	a[o].sum = (a[o].sum + (a[o].r - a[o].l + 1) * op) % md;
}
void pushdown(int o) {
	if (a[o].opm != 1) {
		ll& op = a[o].opm;
		calc_mult(lo, op); calc_mult(ro, op);
		op = 1;
	}
	if (a[o].opa != 0) {
		ll& op = a[o].opa;
		calc_add(lo, op);  calc_add(ro, op);
		op = 0;
	}
}
void pushup(int o) {
	a[o].sum = a[lo].sum + a[ro].sum;
}
void init(int l, int r, int o) {
	a[o].l = l; a[o].r = r; a[o].opa = 0; a[o].opm = 1;
	if (l == r) {
		a[o].sum = num[l];  return;
	}
	int m = l + ((r - l) >> 1);
	init(l, m, lo);
	init(m + 1, r, ro);
	pushup(o);
}
void update_add(int o) {
	if (ql <= a[o].l && a[o].r <= qr) {
		calc_add(o, v);
		return;
	}
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	if (ql <= m) update_add(lo);
	if (qr > m) update_add(ro);
	pushup(o);
}

void update_mult(int o) {
	if (ql <= a[o].l && a[o].r <= qr) {
		calc_mult(o, v);
		return;
	}
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	if (ql <= m) update_mult(lo);
	if (qr > m) update_mult(ro);
	pushup(o);
}

ll query(int o) {
	if (ql <= a[o].l && a[o].r <= qr) return a[o].sum;
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	ll ans = 0;
	if (ql <= m) ans += query(lo);
	if (qr > m) ans += query(ro);
	pushup(o);
	return ans;
}

int main() {
	int n, m;
	read(n, m, md);
	rep(i, 1, n) read(num[i]);
	init(1, n, 1);
	int c;
	rep(i, 1, m) {
		read(c);
		if (c == 1) {
			read(ql, qr, v);
			update_mult(1);
		}
		else if (c == 2) {
			read(ql, qr, v);
			update_add(1);
		}
		else {
			read(ql, qr);
			cout << query(1) % md << endl;
		}
	}
}
