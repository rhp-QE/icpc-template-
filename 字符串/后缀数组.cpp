#include<iostream>
using namespace::std;
//是通过处理   文本串   的   多模板   匹配算法
//sa[i]  表示排名为i的后缀（s+sa[i]）
//求出 sa[i] 后就可以通过二分的方法在文本串中查找 模板串。
//后缀排序后，模板串在后缀中 是聚集的，因此用二分法求上下界即可
//排名为【L , R) 的后缀  ，即为匹配位置
const int N = 2e5 + 11;//
char s[N]; int n;//文本串长度
namespace SA {
    int sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N],height[N];//和前一个串最长公共前缀
    bool cmp(int x, int y, int w) {
        return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }
    void build(int m) {
        int i, p, w, k;
        mem(cnt, 0); mem(id, 0);
        for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
        for (w = 1;; w <<= 1, m = p) {  // m=p 就是优化计数排序值域
            for (p = 0, i = n; i > n - w; --i) id[++p] = i;
            for (i = 1; i <= n; ++i)
                if (sa[i] > w) id[++p] = sa[i] - w;
            memset(cnt, 0, sizeof(cnt));
            for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
            for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
            memcpy(oldrk, rk, sizeof(rk));
            for (p = 0, i = 1; i <= n; ++i)
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
            if (p == n) {
                for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
                break;
            }
        }
        height[1] = 0;
        for (i = 1, k = 0; i <= n; ++i) {
            if (k)  k--;
            int j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            height[rk[i]] = k;
        }
    }
}
int m;  char pat[33];//模板串长度
int cmp_suffix(char* pat, int p) {
    return strncmp(pat, s + SA::sa[p], m);
}
int find_l_r(char* p,int k) {
    m = strlen(p);
    if (cmp_suffix(p, 1) < 0)  return -1;
    if (cmp_suffix(p, n) > 0) return -1;
    int l = 1, r = n + 1;
    while (r > l) {
        int M = l + ((r - l) >> 1);
        if (cmp_suffix(p, M) < 0) r = M;
        else if (cmp_suffix(p, M) > 0) l = M + 1;
        else {
            if (k == 0)  r = M;
            else l = M + 1;
        }
    }
    return r;
}
