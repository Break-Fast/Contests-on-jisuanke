/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-02-26 16:11:08
 ************************************************************************/

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define endl '\n'
#define fep(i,b,e) for(int i=(b);i<=(e);++i)
#define rep(i,x) for(int i=0;i<(x);++i)
#define rap(i,x) for(auto& i : (x))
#define seg(t) (t).begin(), (t).end()
#define ep(x) emplace_back((x))
#define mkp(a,b) make_pair((a),(b))
#define qxx(i,x) for(int i = head[x]; ~i; i = node[i].nex)
#define F first
#define S second
#define lowbit(x) ((-(x))&(x))

typedef pair<int, int> pa;
typedef std::string str;
typedef long long ll;
typedef __gnu_pbds::priority_queue<int> pq;
typedef double db;

const double P = acos(-1.0), eps = 1e-9;
struct point { db x ,y;};
inline int sign(db a) {return a < -eps ? -1 : a > eps;}
#define dot(p1,p2,p3) ((p2.x-p1.x)*(p3.x-p1.x)+(p2.y-p1.y)*(p3.y-p1.y))
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

const int Ma = 505, inf = 0x3f3f3f3f, mod = 1e9 + 7;

int mz[Ma][Ma], n;
bool vis[Ma];
rope<int> ans;

void insert(int id) {
	int indx = ans.size() - 1;
	while(indx >= 0 and mz[id][ans.at(indx)]) --indx;
	ans.insert(indx + 1, id);
}

signed main() {
   	int T;
	scanf("%d", &T);
	while(T--) {
		memset(vis, 0, sizeof vis);
		ans.clear();
		scanf("%d", &n);
		rep(i, n)
			rep(j, n)
			scanf("%d", &mz[i][j]);
		rep(i, n)
			insert(i);
		rep(i, n)
			cout << ans[i] + 1 << ' ';
		cout << endl;
	}

    return 0;
}
