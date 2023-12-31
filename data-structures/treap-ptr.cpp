//Reference: http://blog.csdn.net/chen_tr/article/details/50924073
//VERIFY RELIABILITY BEFORE USE.
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = int(1e5) + 5;

struct node{
    int key, prio, size;
    node* ch[2];
};

typedef node* tree;
node base[maxn], nil;
tree top, null, root;

inline int rand(){
    static int seed=703;
    return seed=int(seed*48271LL%2147483647);
}

inline void init(){
    top = base;
    root = null = &nil;
    null -> ch[0] = null -> ch[1] = null;
    null -> key = null -> prio = 2147483647;
    null -> size = 0;
}

inline tree newNode(int k){
    top -> key = k;
    top -> size = 1;
    top -> prio = (int) rand();
    top -> ch[0] = top -> ch[1] = null;
    return top++;
}

inline void rotate(tree &x, bool d){
    //bool d: direction. 0 for left, 1 for right
    tree y = x -> ch[!d];
    x -> ch[d] = y -> ch[!d];
    y -> ch[d] = x;
    x -> size = x -> ch[0] -> size + 1 + x -> ch[1] -> size;
    y -> size = y -> ch[0] -> size + 1 + y -> ch[1] -> size;
    x = y;
}

inline void insert(tree &t, int key){
    if (t == null) t = newNode(key);
    else{
        bool d = key > t -> key;
        insert(t -> ch[d], key);
        t -> size++;
        if (t -> prio < t -> ch[d] -> prio) rotate(t, !d);
    }
}

void erase(tree &t, int key){
    if (t -> key != key){
        erase(t -> ch[key > t -> key], key);
        t -> size--;
    }
    else if (t -> ch[0] == null) t = t->ch[1];
    else if (t -> ch[1] == null) t = t->ch[0];
    else{
        bool d = t-> ch[0] -> prio < t-> ch[1] -> prio;
        rotate(t, d);
        erase(t -> ch[d], key);
    }
}