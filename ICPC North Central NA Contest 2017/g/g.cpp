/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-02-29 12:42:47
 ************************************************************************/

#define GOODOJ
#define SYNC 0
#include <bits/stdc++.h>
#ifdef GOODOJ
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
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

const int Ma = 120, inf = 0x3f3f3f3f, mod = 1e9 + 7;

str mz[120];
bool vis[Ma][Ma];
int n, m;

bool check(int r, int c) {
	return r >= 0 and r < n and c >= 0 and c < m and !vis[r][c] and mz[r][c] == '#';
}

int xz[] = {1, 1, 1, 0, 0, -1, -1, -1},
	yz[] = {-1, 0, 1, 1, -1, -1, 0, 1};

void dfs(int r, int c) {
	vis[r][c] = true;
	rep(i, 8) {
		int y = r + yz[i], x = c + xz[i];
		if (check(y, x)) dfs(y, x);
	}
}

signed main() {
	#if SYNC==0
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	cin >> n >> m;
	rep(i, n) cin >> mz[i];
	int ans = 0;
	rep(i, n) rep(j, m) if(check(i, j))
		dfs(i, j), ++ans;
	cout << ans << endl;
    
    return 0;
}
