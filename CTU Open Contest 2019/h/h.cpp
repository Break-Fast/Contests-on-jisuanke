/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-02-22 13:55:14
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

const int Ma = 1e6, inf = 0x3f3f3f3f, mod = 1e9 + 7;

int t, n, m;

char mz[30][30], mzw[30][30];
char dx[30][30];
int cao[30][30];

void update() {
	rep(i, n) rep(j, m) if(cao[i][j] > 0){
		--cao[i][j];
		if(!cao[i][j])dx[i][j] = '#';
	}
}

struct Sheep {
	int x, y, life;
	Sheep(int _x, int _y) : x(_x), y(_y), life(5) {}
	void run() {
		if(life == 0) return;
		--life;

		y = (y + 1) % n;
        
		if(mzw[y][x] == 'W') life = 0;
        else if(dx[y][x] == '#') life = 5, dx[y][x] = '.', cao[y][x] = 4;

		if(life)mzw[y][x] = 'S';

		if(life == 0) dx[y][x] = '*', cao[y][x] = 0;
	}
};

vector<Sheep> sheep;

struct Wolf {
	int x, y, life;
	Wolf(int _x, int _y) : x(_x), y(_y), life(10) {}
	void run() {
		if(life == 0) return ;
		--life;
		
        x = (x + 1) % m;
        
		if(mz[((y - 1) % n + n) % n][x] == 'S') life = 10;
		
        if(life)mzw[y][x] = 'W';
		
		if(life == 0) dx[y][x] = '*', cao[y][x] = 0;
	}
};

vector<Wolf> wolf;

void readmap() {
	rep(i, n) {
		fgets(mz[i], sizeof mz[i], stdin);
		//scanf("%s", mz[i]);
		rep(j, m) {
			dx[i][j] = '.';
			cao[i][j] = 3;
			if(mz[i][j] == 'W') wolf.ep(Wolf(j, i));
			else if(mz[i][j] == 'S') sheep.ep(Sheep(j, i));
		}
	}
}

void print() {
	rep(i, n) printf("%s\n", mz[i]);
}

signed main() {
	scanf("%d%d%d", &t, &n, &m);
	readmap();
	while(t--) {
		rap(i, wolf)
			i.run();
		rap(i, sheep)
			i.run();
		update();
        rep(i, n) rep(j, m) {
            if(mzw[i][j] == 'W' or mzw[i][j] == 'S')
                mz[i][j] = mzw[i][j];
            else mz[i][j] = dx[i][j];
            mzw[i][j] = 0;
        }
	}
    print();

    return 0;
}

