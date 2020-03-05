/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-03-04 19:09:13
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

const int Ma = 1e3 + 100, inf = 0x3f3f3f3f, mod = 1e9 + 7;

int midp(int len, int sel, int be=0) {
	return be + (len - sel) / 2;
}

char g[Ma][Ma];

struct GZ {
	vector<str> name;
	int len; int high = 8;
	void getlen() {
		len = 0;
		rap(i, name)
			len = max(int(i.length()), len);
		len += 2;
	}
	void print(int xb, int yb) {
		int pos = midp(8, name.size(), 0);
		//cout << xb << ' ' << yb << endl;
		rep(i, 8) {
			//rep(j, len + 1)
			//	g[xb + i][yb + j] = ' ';
			g[xb + i][yb] = g[xb + i][yb + len - 1] = '#';
			if(i == 0 or i == 7) {
				rep(j, len)
					g[xb + i][yb + j] = '#';
				continue;
			}
			if(i >= pos and i - pos < name.size()) {
				int slen = name[i - pos].length();
				int xp = midp(len, slen, 0);
				rep(j, slen)
					g[xb + i][yb + xp + j] = (name[i - pos][j] == '_' ? ' ' : name[i - pos][j]);
			}
		}
	}
};

const int HMax = 80;

struct Dui {
	int mi, h, l, r;
	vector<int> son;
	void print() {
		cout << l << ' ' << r << endl;
	}
};

signed main() {
	#if SYNC==1
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	int T, To = 0;
	scanf("%d", &T);
	while(T--) {
		vector<GZ> gz;
		vector<Dui> dui;
		int n;
		scanf("%d\n", &n);
		memset(g, ' ', sizeof g);
		rep(i, n) {
			str t;
			getline(cin, t);
			while(t.find(' ') != string::npos)
				t[t.find(' ')] = '_';
			while(t.find('#') != string::npos)
				t[t.find('#')] = ' ';
			istringstream it(t);
			GZ temp;
			while(it >> t)temp.name.ep(t);
			gz.ep(temp); gz.back().getlen();
			bool can = false;
			rap(j, dui) if(j.mi > gz.back().len and j.h < HMax){
				j.son.ep(i);
				j.mi = gz.back().len;
				j.h += gz.back().high;
				can = true;
				break;
			}
			if(not can) {
				Dui tp;
				tp.l = dui.empty() ? 0 : (dui.back().r + 1);
				tp.r = tp.l + gz.back().len;
				tp.mi = gz.back().len;
				tp.h = gz.back().high;
				tp.son.ep(i);
				dui.ep(tp);
			}
		}
		printf("Can Stack #%d:\n", ++To);
		puts("         1         2         3         4         5         6");
		puts("123456789012345678901234567890123456789012345678901234567890");
		//rap(i, dui) i.print();
		int xb = -1; int high = 0;
		rap(i, dui) high = max(high, i.h);
		//cout << high << endl;
		rap(i, dui) {
			++xb; int yb = high;
			int pl = i.l, pr = i.r;
			rap(j, i.son) {
				yb -= gz[j].high;
				gz[j].print(yb, xb + midp(pr - pl, gz[j].len, pl - i.l));
				pl = xb + midp(pr - pl, gz[j].len, pl - i.l);
				pr = pl + gz[j].len;
			}
			xb = i.r;
		}
		//gz[0].print(0, 0); gz[1].print(0, 11);
		
		
		rep(i, high) {
			for(int j = xb; j >= 0; j--) if(g[i][j] != ' ') {
				g[i][j + 1] = 0;
				break;
			}
		}
		rep(i, high)printf("%s\n", g[i]);
		//printf("%d, %s\n", high, g[7]);
		//putchar(g[7][0]);
		puts("");
	}
    
    return 0;
}
