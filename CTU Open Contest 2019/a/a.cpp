/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-02-22 11:59:44
 ************************************************************************/

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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

const int Ma = 1000, inf = 0x3f3f3f3f;
const ll mod = 1000000007;

ll C[1001][1001];

void init() {
	C[0][0] = 1;
	fep(i, 1, Ma) {
		C[i][0] = 1;
		fep(j, 1, i)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	init();
	int a, b, k, c;
	cin >> a >> b >> k >> c;
	if(not(a == c || b == c)) cout << 0 << endl;
	else {
		ll ans = 0;
		fep(i, 1, k) {
			(ans += C[k][i] * i % mod) %= mod;
		}
		if(a == b) ans = ans * 2 % mod;
		cout << ans << endl;
	}
    
    return 0;
}
