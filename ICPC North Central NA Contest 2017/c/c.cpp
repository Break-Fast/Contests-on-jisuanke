/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-02-29 14:40:19
 ************************************************************************/

#define GOODOJ
#define SYNC 1
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

namespace Geo{
	#include <cmath>
	#include <cstdio>
	#include <cassert>
	#include <vector>
	typedef double db;
	const db eps = 1e-9, P = acos(-1);
	inline int sign(db a) {return a < -eps ? -1 : a > eps;}
	inline int cmp(db a, db b) {return sign(a - b);}
	inline bool inmid(db k, db a, db b) {return sign(a - k) * sign(b - k) <= 0;}
	struct Point{
		db x, y;
		Point(db _x, db _y) : x(_x), y(_y) {}
		Point() = default;
		Point operator + (const Point& b) const{return {x + b.x, y + b.y};}
		Point operator - (const Point& b) const{return {x - b.x, y - b.y};}
		Point operator * (const db& b) const{return {x * b, y * b};}
		Point operator / (const db& b) const{return {x / b, y / b};}
		bool operator == (const Point& b) const{return cmp(x,b.x)==0&&cmp(y,b.y)==0;}
		bool operator != (const Point& b) const{return not (*this == b);}
		bool operator < (const Point& b) const {
			int c = cmp(x, b.x);
			if (c) return c == -1;
			return cmp(y, b.y) == -1;
		}
		bool operator > (const Point& b) const {return b < *this;}
		Point right(const db& len) {return Point(x + len, y);}
		Point up(const db& len) {return Point(x, y + len);}
		db length() const {return sqrt(x*x+y*y);}
		Point unit() const {return *this / this->length();}
		void print() const {printf("%.11f %.11f\n", x, y);}
		void scan() {scanf("%lf%lf", &x, &y);}
		db dis(Point b) {return (*this - b).length();}
	};
	typedef Point Vector;
	typedef std::vector<Point> Polygon;
	struct Line {
		Point u, v;
		Line(const Point& _a, const Point& _b) : u(_a), v(_b) {}
		Line() = default;
		Vector getVec() {
			return Vector(v - u);
		}
		bool isPoint() {
			return u == v;
		}
		void print() {
			u.print();
			v.print();
		}
	};
	inline db dot(Point ab, Point ac) {return ab.x*ac.x+ab.y*ac.y;} //|ab|*|ac|*cosθ
	inline int dotOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(dot(b-a,c-a));} //+ : 1,4 - : 2,3
	inline db cross(Point ab, Point ac) {return ab.x*ac.y-ab.y*ac.x;} //|ab|*|ac|*sinθ
	inline int crossOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(cross(b-a,c-a));} //+ : 1,2 -: 3,4
	inline int Op(Point c, Point a={0,0}, Point b={0,1e5}) {
		int lr = dotOp(c,a,b), ud = crossOp(c,a,b);
		if(lr==0 or ud == 0) return 0;
		return lr + ud == 2 ? 1 : (lr + ud == -2 ? 3 : (lr == -1 ? 2 : 1));
	}
	inline Point pjPoint(Point c, Point a, Point b) { // 投影点
		return a + (b - a).unit() * dot(c - a, b - a) / (b - a).length();
	}
	inline Point symPoint(Point c, Point a, Point b) { // 对称点
		return pjPoint(c, a, b) * 2.0 - c;
	}
	inline bool ckpar(Point a, Point b, Point c, Point d) { // 检查平行
		return cmp(cross(c-a,d-a), cross(c-b,d-b)) == 0;
	}
	inline Point getInsec(Point a, Point b, Point c, Point d) { // 获取交点
		db w1 = cross(a-c,d-c), w2 = cross(d-c,b-c);
		return (a * w2 + b * w1) / (w1 + w2);
	}
	inline bool inseg(Point c, Point a, Point b) { //点在直线上
		if (c == a or c == b) return true;
		return sign(cross(b - a, c - a)) == 0 and sign(dot(a - c, b - c)) == -1;
	}
	inline bool inseg(Point c, Line p) {
		return inseg(c, p.u, p.v);
	}
	inline bool intersect(db l1, db r1, db l2, db r2) { // 排斥 [l1,r1] [l2,r2]有交集
		if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2);
		return cmp(r2, l1) != -1 and cmp(r1, l2) != -1;
	}
	inline int spanLine(Point a, Point b, Point c, Point d) { // ab跨立cd直线 跨立实验<0成功=0在直线上
		return sign(cross(a - c, d - c)) * sign(cross(b - c, d - c));
	}
	inline bool checkSS(Point a, Point b, Point c, Point d) { // 线段相交 非规范
		return intersect(a.x, b.x, c.x, d.x) and intersect(a.y, b.y, c.y, d.y) and
			spanLine(a, b, c, d) <= 0 and spanLine(c, d, a, b) <= 0;
	}
	inline bool checkSSsp(Point a, Point b, Point c, Point d) { // 线段相交 非规范
		return spanLine(a, b, c, d) < 0 and spanLine(c, d, a, b) < 0;
	}
	inline bool checkSS(Line a, Line b, bool Notsp=true) {
		if(Notsp)return checkSS(a.u, a.v, b.u, b.v);
		else return checkSSsp(a.u, a.v, b.u, b.v);
	}
	inline db areaPol(const Polygon& v) { // area of Polygon
		db ans = 0; int len = v.size();
		for(int i = 0; i < len; i++) ans += cross(v[i], v[(i+1)%len]);
		return ans / 2;
	}
	inline int contains(const Polygon& ps, Point q) {
		int n = ps.size();
		int res = -1;
		for(int i = 0; i < n; i++) {
			Vector a = ps[i] - q, b = ps[(i + 1) % n] - q;
			if (cmp(a.y, b.y) == 1)	swap(a.y, b.y);
		}

		return res;
	}
}

typedef Geo::Point point;
typedef Geo::Line line;
function<int(db)> sign = Geo::sign;
function<int(db,db)> cmp = Geo::cmp;

const int Ma = 1e6, inf = 0x3f3f3f3f, mod = 1e9 + 7;

line sp[10000];
int s;

bool check(line t) {
	int now = 0;
	rep(i, s) if(Geo::spanLine(t.u, t.v, sp[i].u, sp[i].v) <= 0) ++now;
	return now % 2 != 1;
}

signed main() {
	#if SYNC==0
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	scanf("%d", &s);
	rep(i, s) {
		point a, b;
		a.scan(), b.scan();
		sp[i] = line(a, b);
	}
	int n;
	scanf("%d", &n);
	rep(i, n) {
		point a, b;
		a.scan(), b.scan();
		if(check(line(a, b))) puts("same");
		else puts("different");
	}

    return 0;
}
