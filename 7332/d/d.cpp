/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-03-04 17:59:52
 ************************************************************************/

#define GOODOJ
#define SYNC 0

#ifdef GOODOJ
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#else
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <cassert>
#endif
using namespace std;

#define endl '\n'
#define fep(i,b,e) for(int i=(b);i<=(e);++i)
#define rep(i,x) for(int i=0;i<(x);++i)
#define rap(i,x) for(auto& i : (x))
#define seg(t) (t).begin(), (t).end()
#define ep emplace_back
#define mkp make_pair
#define qxx(i,x) for(int i = head[x]; ~i; i = node[i].nex)
#define F first
#define S second
#define lowbit(x) ((-(x))&(x))
#define RE register

typedef pair<int, int> pa;
typedef std::string str;
typedef long long ll;
#ifdef GOODOJ
typedef __gnu_pbds::priority_queue<int> pq;
#endif
typedef double db;

const double P = acos(-1.0), eps = 1e-9;
struct point { db x ,y;};
inline int sign(db a) {return a < -eps ? -1 : a > eps;}
#define dot(p1,p2,p3) ((p2.x-p1.x)*(p3.x-p1.x)+(p2.y-p1.y)*(p3.y-p1.y))
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

const int Ma = 1e3, inf = 0x3f3f3f3f, mod = 1e9 + 7;

int pool[Ma], n, ans;
bool xin[Ma];

int now = 0;

void init()	{
	rep(i, n) pool[i] = 0, xin[i] = 0;
	now = 0; ans = 0;
}

bool check(int aim) {
	rep(i, n) {
		if(pool[i] == aim) {
			printf("Access page %d in cell %d.\n", aim, i + 1);
			xin[i] = true;
			return true;
		}
	}
	return false;
}

void solve(int aim) {
	if(check(aim)) return ;
	rep(i, n) {
		if(pool[i] == 0) {
			printf("Page %d loaded into cell %d.\n", aim, i + 1);
			xin[i] = true;
			pool[i] = aim;
			++ans;
			return ;
		}
	}
	while(true) {
		if(xin[now] == 0) {
			printf("Page %d loaded into cell %d.\n", aim, now + 1);
			pool[now] = aim;
			xin[now] = true;
			++now;
			now %= n;
			++ans;
			return ;
		} else xin[now] = false;
		++now;
		now %= n;
	}
}

signed main() {
	#if SYNC==1
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	int m; int To = 0;
	while(scanf("%d%d", &n, &m) and (n + m)) {
		init();
		printf("Program %d\n", ++To);
		while(m--) {
			int aim;
			scanf("%d", &aim);
			solve(aim);
		}
		printf("There are a total of %d page faults.\n\n", ans);
	}
    
    return 0;
}
