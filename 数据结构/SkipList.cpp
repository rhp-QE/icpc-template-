#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <unordered_map>
using namespace ::std;

#define MX_LEV 40

template <typename _Key, typename _Val>
class skipList;

template <typename _Key, typename _Val>
class skipNode {
private:
    _Key key;
    _Val val;
    int level;
    /* int cnt; */
    skipNode** next;

public:
    friend class skipList<_Key, _Val>;
    skipNode<_Key, _Val>() = default;
    skipNode<_Key, _Val>(_Key key, _Val val, int level, skipNode<_Key, _Val>* nxt = nullptr)
        : key(key)
        , val(val)
        , level(level)
        , next(new skipNode<_Key, _Val>*[level + 1])
    /* , cnt(1) */
    {
        for (int i = 0; i <= level; ++i)
            next[i] = nxt;
    }
    ~skipNode<_Key, _Val>()
    {
        if (next)
            delete[] next;
    }
};

template <typename _Key, typename _Val>
class skipList {
public:
    skipList<_Key, _Val>()
    {
        tail = new skipNode<_Key, _Val>(_Key(), _Val(), 0);
        head = new skipNode<_Key, _Val>(_Key(), _Val(), MX_LEV, tail);
        level = len = 0;
    }
    ~skipList<_Key, _Val>()
    {
        delete tail;
        delete head;
    }

    bool erase(const _Key& key);
    _Val& operator[](const _Key& key);
    bool find(const _Key& key);
    /* int count(const _Key& key); */

private:
    void insert(const _Key& key, const _Val& val);

private:
    skipNode<_Key, _Val>* head;
    skipNode<_Key, _Val>* tail;
    inline int getRandomLevel();
    static const int RANG;
    static const int _RANG;
    int level, len;

private:
    skipNode<_Key, _Val>* path[MX_LEV];
};

template <typename _Key, typename _Val>
const int skipList<_Key, _Val>::RANG = 100000;

template <typename _Key, typename _Val>
const int skipList<_Key, _Val>::_RANG = RANG / 4;

template <typename _Key, typename _Val>
bool skipList<_Key, _Val>::erase(const _Key& key)
{
    int ret = find(key);
    if (false == ret)
        return false;
    skipNode<_Key, _Val>* ptr = path[0]->next[0];

    /* if (--ptr->cnt > 0) */
    /*     return true; */

    for (int i = 0, lv = ptr->level; i <= lv; ++i) {
        path[i]->next[i] = path[i]->next[i]->next[i];
    }
    delete ptr;
    return true;
}

template <typename _Key, typename _Val>
bool skipList<_Key, _Val>::find(const _Key& key)
{
    skipNode<_Key, _Val>* ptr = head;
    for (int i = level; i >= 0; --i) {
        while (ptr->next[i] != tail && ptr->next[i]->key < key)
            ptr = ptr->next[i];
        path[i] = ptr;
    }
    return ptr->next[0]->key == key;
}

/* template<typename _Key,typename _Val> */
/* int skipList<_Key,_Val>::count(const _Key& key) */
/* { */
/*    int ret=find(key); */
/*    if(!ret) return 0; */
/*    return path[0]->next[0]->cnt; */
/* } */

template <typename _Key, typename _Val>
void skipList<_Key, _Val>::insert(const _Key& key, const _Val& val)
{
    int ret = find(key);

    if (ret) {
        /* ++path[0]->next[0]->cnt; */
        path[0]->next[0]->val = val;
        return;
    }

    int lv = getRandomLevel();
    if (lv > level)
        lv = ++level, path[lv] = head;
    skipNode<_Key, _Val>* ptr = new skipNode<_Key, _Val>(key, val, lv);
    for (int i = 0; i <= lv; ++i) {
        ptr->next[i] = path[i]->next[i];
        path[i]->next[i] = ptr;
    }
    ++len;
}

template <typename _Key, typename _Val>
int skipList<_Key, _Val>::getRandomLevel()
{
    int lv = 1;
    while (rand() % RANG < _RANG)
        ++lv;
    return min(lv, MX_LEV);
}

template <typename _Key, typename _Val>
_Val& skipList<_Key, _Val>::operator[](const _Key& key)
{
    int ret = find(key);
    if (ret)
        return path[0]->next[0]->val;
    insert(key, _Val());
    return path[0]->next[0]->val;
}

int test()
{
    unordered_map<int, int> mp;
    skipList<int, int> my_mp;

    for (int i = 0; i < 1000000; ++i) {
        int key = rand() % 1000;
        int val = rand() % 1000;
        int op = rand() % 3;
        if (op == 0) {
            mp[key] = val;
            my_mp[key] = val;
        } else if (op == 1) {
            if (mp.erase(key) != my_mp.erase(key)) {
                printf("error\n");
                return 0;
            }
        } else {
            if ((mp.find(val) != mp.end()) != my_mp.find(val)) {
                printf("error\n");
                return 0;
            }
        }
    }
    printf("success\n");
    return 1;
}
