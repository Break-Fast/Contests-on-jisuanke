/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-03-04 18:38:41
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

namespace Geo{
	#include <cmath>
	#include <cstdio>
	#include <cassert>
	#include <vector>
	typedef double db;
	const db eps = 0.01, P = acos(-1);
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
		Point roate(db ac) {return Point(x * cos(ac) - y * sin(ac), y * cos(ac) + x * sin(ac));}
	};
	typedef Point Vector;
	typedef std::vector<Point> Polygon;
	struct Line {
		Point u, v;
		Line(const Point& _a, const Point& _b) : u(_a), v(_b) {}
		Line() = default;
		Vector getVec() {return Vector(v - u);}
		bool isPoint() {return u == v;}
		db length() {return u.dis(v);}
		void print() {u.print(), v.print();}
		void scan() {u.scan(), v.scan();}
	};
	inline db dot(Point ab, Point ac) {return ab.x*ac.x+ab.y*ac.y;} //|ab|*|ac|*cosθ
	inline int dotOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(dot(b-a,c-a));} //+ : 1,4 - : 2,3
	inline db cross(Point ab, Point ac) {return ab.x*ac.y-ab.y*ac.x;} //|ab|*|ac|*sinθ
	inline int crossOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(cross(b-a,c-a));} //+ : 1,2 -: 3,4
	inline int Op(Point c, Point a={0,0}, Point b={0,1e5}) { // 相对象限
		int lr = dotOp(c,a,b), ud = crossOp(c,a,b);
		if(lr==0 or ud == 0) return 0;
		return lr + ud == 2 ? 1 : (lr + ud == -2 ? 3 : (lr == -1 ? 2 : 1));
	}
	inline int Quadrant(Point a) { // 象限
		if (a.x > 0 and a.y >= 0) return 1;
		if (a.x <= 0 and a.y > 0) return 2;
		if (a.x < 0 and a.y <= 0) return 3;
		if (a.x >= 0 and a.y < 0) return 4;
	}
	inline db disPtoL(Point c, Line a) { // 点到直线距离
		return fabs(cross(a.v - a.u, c - a.u)) / a.length();
	}
	struct Circle {
		Point o; db r;
		Circle(Point _t, db _r) : o(_t), r(_r) {}
		Circle() = default;
		int intersect(Line t) { // 0 相切 1 相离 -1 相交
			return cmp(disPtoL(o, t), r);
		}
		bool intersect_seg(Line t) {
			if(cmp(o.dis(t.v), r) != 1 or cmp(o.dis(t.u), r) != 1)
				return sign(o.dis(t.v)) != -1 or sign(o.dis(t.u) != -1);
			Point pv = Point(o.x + t.u.y - t.v.y, o.y + t.v.x - t.u.x);
			return sign(cross(t.u - pv, o - pv)) * sign(cross(t.v - pv, o - pv)) <= 0 and
				   this->intersect(t) != 1;
		}
	};
	inline Point pjPoint(Point c, Point a, Point b) { // 投影点
		return a + (b - a).unit() * dot(c - a, b - a) / (b - a).length();
	}
	inline Point symPoint(Point c, Point a, Point b) { // 对称点
		return pjPoint(c, a, b) * 2.0 - c;
	}
	inline bool ckpar(Point a, Point b, Point c, Point d) { // 检查直线平行
		return cmp(cross(c-a,d-a), cross(c-b,d-b)) == 0;
	}
	inline bool ckpar(Line a, Line b) {return ckpar(a.u, a.v, b.u, b.v);}
	inline Point getInsec(Point a, Point b, Point c, Point d) { // 获取交点
		db w1 = cross(a-c,d-c), w2 = cross(d-c,b-c);
		return (a * w2 + b * w1) / (w1 + w2);
	}
	inline Point getInsec(Line a, Line b) {return getInsec(a.u, a.v, b.u, b.v);}
	inline bool inseg(Point c, Point a, Point b) { //点在直线a, b上
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
	inline int spanLine(Line a, Line b) {
		return spanLine(a.u, a.v, b.u, b.v);
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
	inline int contains(const Polygon& ps, Point q) { // 内部1 外部-1 边上0 点于多边形
		int n = ps.size();
		int res = -1;
		for(int i = 0; i < n; i++) {
			Vector a = ps[i] - q, b = ps[(i + 1) % n] - q;
			if (cmp(a.y, b.y) == 1)	swap(a.y, b.y);
			if (sign(a.y) != 1 and sign(b.y) == 1 and sign(cross(a, b)) == 1)
				res = -res;
			if (sign(cross(a, b)) == 0 and sign(dot(a, b)) != 1) return 0;
		}

		return res;
	}
	bool cmpAtan(Point a, Point b) {
		if(atan2(a.y, a.x) != atan2(b.y, b.x))
			return atan2(a.y, a.x) < atan2(b.y, b.x);
		return a.x < b.x;
	}
	struct CMP {
		Point o;
		CMP(Point t=Point(0, 0)) : o(t) {};
		bool operator () (const Point& a, const Point& b) {
			if(crossOp(b, o, a) == 0)
				return a.x < b.x;
			return crossOp(b, o, a) == 1;
		}
	};
	bool isConvex(const Polygon& ps) { // 1 凸多边形
		int s[3] = {1, 1, 1}; int n = ps.size();
		for(int i = 0; i < n and s[0] | s[2]; ++i)
			s[sign(cross(ps[(i + 1) % n] - ps[i], ps[(i + 2) % n] - ps[i])) + 1] = 0;
		return s[0] | s[2];
	}
	Point nearestPoint(Point c, Line ab) {
		db t = dot(c - ab.u, ab.getVec()) / dot(ab.getVec(), ab.getVec());
		if(0 <= t and t <= 1) return ab.u + (ab.v - ab.u) * t;
		return c.dis(ab.u) > c.dis(ab.v) ? ab.v : ab.u;
	}
}

typedef Geo::Point point;
typedef Geo::Line line;
typedef Geo::Circle circle;
function<int(db)> sign = Geo::sign;
function<int(db,db)> cmp = Geo::cmp;

const int Ma = 100, inf = 0x3f3f3f3f, mod = 1e9 + 7;
circle cam[Ma];
point rode[Ma];
int ans[Ma];

int c, p;

bool check(int id) {
	rep(i, p - 1) {
		if(cam[id].intersect_seg(line(rode[i], rode[i + 1]))) {
			//cam[id].o.print(); cout << cam[id].r << endl;
			//line(rode[i], rode[i + 1])
			return true;
		}
	}
	return false;
}

signed main() {
	#if SYNC==1
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	int n, To = 0;
	scanf("%d", &n);
	while(n--) {
		scanf("%d%d", &c, &p);
		rep(i, c) {
			cam[i].o.scan();
			scanf("%lf", &cam[i].r);
		}
		rep(i, p)
			rode[i].scan();
		//sort(rode, rode + p, Geo::CMP());
		int cnt = 0;
		rep(i, c) if(check(i)) ans[cnt++] = i + 1;
		if(cnt) {
			printf("Compound #%d: Reptile triggered these cameras:", ++To);
			rep(i, cnt) printf(" %d", ans[i]);
			puts("");
		} else printf("Compound #%d: Rigid Reptile was undetected\n", ++To);
		puts("");
	}
    
    return 0;
}
