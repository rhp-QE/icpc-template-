/*
* ��Ӧ�� UVA11922
*/
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
*  1) split(T,L,R,k) ������� 
*  2) merge(L,R,T)   ����ϲ�
*/

/*
*  ��չ���������
*  ͨ�����±꽨������������dfs�������������˳�������������ʵ�������������Ѻͺϲ���
*  ÿ���ڵ�ά��һ�� size �ֶ� ���Ϳ����ҵ������еĵ� k ��Ԫ��
* 
*  ������Ķ����������ͨ�� �������ǵķ�ʽ ʵ��
*  Ҫע�������ǵ��·�ʱ����һ����˵ÿ���ʵ�һ���µĽڵ㣬��Ҫ�Ը��ڵ�ִ��һ�� pushdown
*/
const int maxn = 1e5 + 11;
int num[maxn];
typedef struct node {
	node* ch[2];
	//val ��ʾ�����ֵ�� size ��ʾ����Ԫ�ظ���
	int val, size;
	bool flip;              //��ת���
	int cmp(int k) {        //�Ƿ�����������
		int k1 = (ch[0] == nullptr ? 0 : ch[0]->size) + 1;
		if (k1 == k) return -1;
		return k1 < k;
	}
	void maintain() {       //ά�����Ĵ�С
		size = 1;
		if (ch[0]) size += ch[0]->size;
		if (ch[1]) size += ch[1]->size;
	}
	int getls() {           //��ȡ��߸���
		if (ch[0] == nullptr) return 1;
		return ch[0]->size + 1;
	}
	void pushdown() {       //��ת����·�
		if (flip) {
			swap(ch[0], ch[1]);
			if (ch[1]) ch[1]->flip ^= 1;
			if (ch[0]) ch[0]->flip ^= 1;
			flip = 0;
		}
	}
	node(int k) {
		val = k; ch[0] = nullptr; ch[1] = nullptr;
	}
	~node() {
		free(ch[0]); free(ch[1]);
	}
}*Splay;

void rotate(Splay &T, int d) {
	//d==0 ������ d==1 ����
	Splay x = T->ch[1 ^ d];
	x->pushdown(); //����·�
	T->ch[1 ^ d] = x->ch[d];
	x->ch[d] = T;
	T->maintain();
	x->maintain();
	T = x;
}

void splay(Splay& T, int k) {//����ʱ��֤ T k ����Ч
	//����k������չ����
	T->pushdown();//����·�
	int d1 = T->cmp(k);//��k�����������������������������
	if (d1 == -1) return;
	if (d1 == 1) k -= T->getls();
	Splay& p = T->ch[d1];
	p->pushdown();//����·�
	int d2 = p->cmp(k);
	if (d2 != -1) {
		int k2 = k;
		if (d2 == 1) k2 -= p->getls();
		splay(p->ch[d2], k2);
		if (d1 == d2) rotate(T, d1 ^ 1);
		else rotate(p, 1 ^ d2);
	}
	rotate(T, 1 ^ d1);
}

void split(Splay& T, Splay& L, Splay& R, int k) {
	if (T == nullptr) return;
	if (k == 0) {
		L = nullptr; R = T; T = nullptr;
		return;
	}
	splay(T, k);
	L = T; R = L->ch[1];
	L->ch[1] = nullptr;
	L->maintain();
	T = nullptr;
}

void merge(Splay& L, Splay& R, Splay& T) {
	if (L == nullptr) {
		T = R; R = nullptr; return;
	}
	else {
		splay(L, L->size);
		T = L; L = nullptr;
		T->ch[1] = R; R = nullptr;
		T->maintain();
	}
}

node* init(int l, int r) {
	if (l > r) return nullptr;
	int m = l + ((r - l) >> 1);
	node* p = new node(num[m]);
	p->size = r - l + 1;
	p->flip = 0;
	p->ch[0] = init(l, m - 1);
	p->ch[1] = init(m + 1, r);
	return p;
}

void dfs(Splay T) {
	if (T == nullptr) return;
	T->pushdown();//����·�
	dfs(T->ch[0]);
	cout << T->val << endl;
	dfs(T->ch[1]);
}
int main() {
	int n, m;
	read(n, m);
	rep(i, 1, n) num[i] = i;
	Splay T = init(1, n), L = nullptr, R = nullptr, M = nullptr, O = nullptr;
	while (m-- > 0) {
		int a, b;
		read(a, b);
		split(T, L, O, a - 1);
		split(O, M, R, b - a + 1);
		M->flip ^= 1;
		merge(L, R, O);
		merge(O, M, T);
		//cout << 10 - m << " || ";
		//dfs(T); cout << endl;
	}
	dfs(T);
}