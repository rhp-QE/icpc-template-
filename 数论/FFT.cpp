
#include <bits/stdc++.h>
using namespace std;
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
https://ac.nowcoder.com/acm/contest/11166#question   H 题
*/
const int maxn = 2e6 + 233;
#define DB double
#define pi acos(-1)
typedef complex<double> E;

E a[maxn], b[maxn];
int n, m;
//n,m 分别表示两多项式的最高次
//经过init() 后 m表示两式相乘后的最高次。n为2的幂次，且大于m
namespace TT {
	
	int n, m, L;
	int R[maxn];
	
	void init(int& a, int& b) {
		n = a, m = b;
		m = n + m; for (n = 1; n <= m; n <<= 1)L++;
		for (int i = 0; i < n; i++)R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
		a = n, b = m;
	}

	void fft(E* a, int f)
	{
		for (int i = 0; i < n; i++)if (i < R[i])swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1)
		{
			E wn(cos(pi / i), f * sin(pi / i));
			for (int p = i << 1, j = 0; j < n; j += p)
			{
				E w(1, 0);
				for (int k = 0; k < i; k++, w *= wn)
				{
					E x = a[j + k], y = w * a[j + k + i];
					a[j + k] = x + y; a[j + k + i] = x - y;
				}
			}
		}
	}
}

const int modi = 5e5 + 12;
int main()
{
	int nn, mm;
	read(nn);
	//for (int i = 0; i < maxn; ++i) a[i] = b[i] = 0;
	m = -1;
	int x;
	rep(i, 1, nn) {
		read(x);
		a[x + modi] = 1;
		b[-x + modi] = 1;
		m = max(x, m);
	}
	mm = m;
	m += modi;
	n = modi;
	TT::init(n, m);
	TT::fft(a, 1), TT::fft(b, 1);
	for (int i = 0; i <= n; ++i) a[i]*=b[i];
	TT::fft(a, -1);
	//for (int i = 0; i < 31; ++i) if (((int)(a[i + 2 * modi].real() / n + 0.5)) > 0) cout << i << " ";
	//cout << endl;
	//cout << mm << endl;
	
	int ans;
	for (int i = nn; i <= mm ; ++i) {
		bool ok = 1;
		for (int j = i; j <= mm; j += i) {
			if ((int)(a[j + 2 * modi].real() / n + 0.5) > 0) {
				ok = 0; break;
			}
		}
		if (ok) {
			ans = i; break;
		}
	}
	cout << ans << endl;
}
//-----------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;
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
struct Complex {
	double x, y;
	Complex(double x_ = 0.0, double y_ = 0.0) :x(x_), y(y_) {}
	Complex operator + (Complex P) { return Complex(x + P.x, y + P.y); }
	Complex operator - (Complex P) { return Complex(x - P.x, y - P.y); }
	Complex operator * (Complex P) { return Complex(x * P.x - y * P.y, x * P.y + y * P.x); }
};
const int maxn = (1 << 20) + 3;
#define DB double
#define pi acos(-1)
typedef Complex E;
int ans[maxn];
E a[maxn], b[maxn];
int n, m;
int pre[maxn];
//n,m 分别表示两多项式的最高次
//经过init() 后 m表示两式相乘后的最高次。n为2的幂次，且大于m
char s[maxn], t[maxn];
int f[maxn];
namespace TT {
	//数组扩展后的长度  两原始长度之和  
	int len, num, bit;
	int rev[maxn];
	void init(int a, int b) {  //对长度和R进行初始化
		num = a + b - 1;
		for (len = 1, bit = 0; len < num; len <<= 1) bit++;;
		for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
	void fft(E* a, int type)
	{
		for (int i = 0; i < len; i++)if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < len; i <<= 1)
		{
			E wn(cos(pi / i), type * sin(pi / i));
			for (int p = i << 1, j = 0; j < len; j += p)
			{
				E w(1, 0);
				for (int k = 0; k < i; ++k, w = w * wn)
				{
					E x = a[j + k], y = w * a[j + k + i];
					a[j + k] = x + y; a[j + k + i] = x - y;
				}
			}
		}
		if (type == -1) for (int i = 0; i < len; ++i) a[i].x /= len;
	}
	void FFT(E* a, E* b, int* f, int kk=1)
	{
		fft(a, 1);
		fft(b, 1);
		for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
		fft(a, -1);
		for (int i = 0; i < len; ++i) f[i] += kk * (int)((a[i].x + 0.5));
	}
}
