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
int ql, qr;
ll v, md;
int num[maxn];
struct node {
	int l, r;
	ll sum, opa, opm;
};
node a[maxn*4];

void pushdown(int o) {
	if (a[o].opm != 1) {
		ll& op = a[o].opm;
		a[l(o)].opa = a[l(o)].opa * op % md; a[l(o)].opm = a[l(o)].opm * op % md;
		a[l(o)].sum = a[l(o)].sum * op % md;
		a[r(o)].opa = a[r(o)].opa * op % md; a[r(o)].opm = a[r(o)].opm * op % md;
		a[r(o)].sum = a[r(o)].sum * op % md;
		op = 1;
	}
	if (a[o].opa != 0) {
		ll& op = a[o].opa;
		a[l(o)].opa = (a[l(o)].opa + op) % md; 
		a[l(o)].sum = (a[l(o)].sum + (a[l(o)].r - a[l(o)].l + 1) * op) % md;
		a[r(o)].opa = (a[r(o)].opa + op) % md;
		a[r(o)].sum = (a[r(o)].sum + (a[r(o)].r - a[r(o)].l + 1) * op) % md;
		op = 0;
	}
}
void pushup(int o) {
	a[o].sum = a[l(o)].sum + a[r(o)].sum;
}
void init(int l, int r, int o) {
	a[o].l = l; a[o].r = r; a[o].opa = 0; a[o].opm = 1;
	if (l == r) {
		a[o].sum = num[l];  return;
	}
	int m = l + ((r - l) >> 1);
	init(l, m, l(o));
	init(m + 1, r, r(o));
	pushup(o);
}
void update_add(int o) {
	if (ql <= a[o].l && a[o].r <= qr) {
		a[o].sum = (a[o].sum + v * (a[o].r - a[o].l + 1)) % md;
		a[o].opa = (a[o].opa + v) % md;
		return;
	}
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	if (ql <= m) update_add(l(o));
	if (qr > m) update_add(r(o));
	pushup(o);
}

void update_mult(int o) {
	if (ql <= a[o].l && a[o].r <= qr) {
		a[o].sum = a[o].sum * v % md;
		a[o].opa = a[o].opa * v % md;
		a[o].opm = a[o].opm * v % md;
		return;
	}
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	if (ql <= m) update_mult(l(o));
	if (qr > m) update_mult(r(o));
	pushup(o);
}

ll query(int o) {
	if (ql <= a[o].l && a[o].r <= qr) return a[o].sum;
	pushdown(o);
	int m = a[o].l + ((a[o].r - a[o].l) >> 1);
	ll ans = 0;
	if (ql <= m) ans += query(l(o));
	if (qr > m) ans += query(r(o));
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