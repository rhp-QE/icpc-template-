
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
const int maxn = 2e6 + 233;
#define DB double
#define pi acos(-1)
struct Complex {
	double x, y;
	Complex operator + (const Complex& t)const {
		return { x + t.x , y + t.y };
	}
	Complex operator - (const Complex& t)const {
		return { x - t.x, y - t.y };
	}
	Complex operator * (const Complex& t)const {
		return { x * t.x - y * t.y , x * t.y + y * t.x };
	}
	Complex() :x(0), y(0){}
	Complex(double x): x(x){}
	Complex(double x,double y) :x(x),y(y){}
	
};
typedef complex<double> E;

E a[maxn], b[maxn];
int n, m;

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
				for (int k = 0; k < i; k++, w =w* wn)
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
	for (int i = 0; i <= n; ++i) a[i] = a[i] * b[i];
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
