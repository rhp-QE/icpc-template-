#include "std.h"
/*
* 1）线段树只可以维护可加类信息。所谓可加类信息就是大区间的信息可以由若干子区间的信息合并得到，比如区间和，区间最小值和
* 区间最大值。
* 2）要注意懒惰标记的使用，懒惰标记就是还欠子区间的操作。当有多个懒惰标记时，要提前定义好懒惰标记的下放顺序。
* 3）node节点内记录两种信息，懒惰标记和需要查询的信息
*   懒惰标记对应 修改； 需要查询的信息对应查询；
*/
using namespace ::std;
const int N = 1e5 + 11;
int ql, qr;
ll qv, md;
struct node {
    ll sum;
    ll lazy1, lazy2;
} tr[N << 2];
int num[N];

//当该节点收到 修改标记时 要如何做（会影响 懒惰标记和查询信息 ）
void calc_mult(int v, ll op) {
    tr[v].lazy1 = tr[v].lazy1 * op % md;
    tr[v].lazy2 = tr[v].lazy2 * op % md;
    tr[v].sum = tr[v].sum * op % md;
}
void calc_add(int v, ll op, int len) {
    tr[v].lazy2 += op;
    tr[v].lazy2 %= md;
    tr[v].sum += op * len;
    tr[v].sum %= md;
}

void pushdown(int v, int l, int r) {
    int m = l + ((r - l) >> 1);
    if (tr[v].lazy1 != 1) {
        calc_mult(lv, tr[v].lazy1);
        calc_mult(rv, tr[v].lazy1);
        tr[v].lazy1 = 1;
    }
    if (tr[v].lazy2 != 0) {
        calc_add(lv, tr[v].lazy2, m - l + 1);
        calc_add(rv, tr[v].lazy2, r - m);
        tr[v].lazy2 = 0;
    }
}

//自下而上 维护 需要查询的信息
void pushup(int v) {
    tr[v].sum = (tr[lv].sum + tr[rv].sum) % md;
}

ll query(int v, int l, int r) {
    if (ql <= l && qr >= r)
        return tr[v].sum;
    int m = l + ((r - l) >> 1);
    pushdown(v, l, r);
    ll ans = 0;
    if (ql <= m)
        ans += query(lv, l, m);
    if (qr > m)
        ans += query(rv, m + 1, r);
    pushup(v);
    return ans % md;
}

void update1(int v, int l, int r) {
    if (ql <= l && r <= qr) {
        calc_mult(v, qv);
        return;
    }
    pushdown(v, l, r);
    int m = l + ((r - l) >> 1);
    if (ql <= m)
        update1(lv, l, m);
    if (qr > m)
        update1(rv, m + 1, r);
    pushup(v);
    return;
}

void update2(int v, int l, int r) {
    if (ql <= l && r <= qr) {
        calc_add(v, qv, r - l + 1);
        return;
    }
    pushdown(v, l, r);
    int m = l + ((r - l) >> 1);
    if (ql <= m)
        update2(lv, l, m);
    if (qr > m)
        update2(rv, m + 1, r);
    pushup(v);
    return;
}
void init(int v, int l, int r) {
    tr[v].lazy2 = 0;
    tr[v].lazy1 = 1;
    if (l == r) {
        tr[v].sum = num[l];
        return;
    }
    int m = l + ((r - l) >> 1);
    init(lv, l, m);
    init(rv, m + 1, r);
    pushup(v);
}
int main() {
    int n, m;
    read(n, m, md);
    rep(i, 1, n) read(num[i]);
    init(1, 1, n);
    int c;
    rep(i, 1, m) {
        read(c);
        if (c == 1) {
            read(ql, qr, qv);
            update1(1, 1, n);
        } else if (c == 2) {
            read(ql, qr, qv);
            update2(1, 1, n);
        } else {
            read(ql, qr);
            cout << query(1, 1, n) % md << endl;
        }
    }
    ps;
}
