
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
#define l(o) (o<<1)
#define r(o) (o<<1)|1
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rrep(i,a,b) for(int i=a;i>=b;--i)
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
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n;
/*
* sa[i]: 排名为i的后缀
* 有了sa数组以后就可以用二分法查找字符串
* sa的计算  nlogn
* 每次查找  mlogn   n是文本串，m是模板串
* 对于文本串很长，模板串短的问题，效率会显著提高
*/
void build_sa(int m) {
	//所有字符的取值范围在 0~m-1 之间
	//必要时构建字符到数字间的一对一映射
	int i, * x = t, * y = t2;
	rep(i, 0, m - 1) c[i] = 0;
	rep(i, 0, n - 1) c[x[i] = s[i]]++;
	rep(i, 1, m - 1) c[i] += c[i - 1];
	rrep(i, n - 1, 0) sa[--c[x[i]]] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int p = 0;
		rep(i, n - k, n - 1) y[p++] = i;
		rep(i, 0, n - 1) if (sa[i] >= k) y[p++] = sa[i] - k;
		rep(i, 0, m - 1) c[i] = 0;
		rep(i, 0, n - 1)  c[x[y[i]]]++;
		rep(i, 1, m - 1) c[i] += c[i - 1];
		rrep(i, n - 1, 0) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1; x[sa[0]] = 0;
		rep(i, 1, n - 1)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		if (p >= n) break;
		m = p;
	}
}

int main() {
	scanf("%s", s);n = strlen(s);
	build_sa(256);
	
	rep(i, 0, n - 1) cout << sa[i] << endl;

}