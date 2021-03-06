#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for(int i = a ; i <= b ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define fst first
#define snd second
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
typedef long long ll;typedef pair<int, int> pii;typedef vector<int> vi;typedef long double ld;
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ "; for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") "; return os<<"}";}
namespace fio{
	template <typename T> void scan(T &x) { cin >> x ;}
	template<class T> void scan(vector<T>& a);
	template<class T> void scan(vector<T>& a) { rep(i,0,sz(a)) scan(a[i]); }
	template<class T, class... Ts> void scan(T& t, Ts&... ts) { scan(t); scan(ts...);}
	template <typename T> void print(T x) { cout << x << endl;}
	template<class T, class... Ts> void print(const T& t, const Ts&... ts) { print(t); print(ts...); }
} 
using namespace fio; 
   
#ifdef np
#define trace(...) cout<<"Line:"<<__LINE__<<" "; __f(#__VA_ARGS__, __VA_ARGS__)
template<typename Arg1>void __f(const char *name, Arg1 &&arg1) { cout<<name<<" : "<<arg1<<endl;}
template<typename Arg1, typename ... Args>void __f(const char *names, Arg1 &&arg1, Args &&... args) {
    const char *comma=strchr(names+1,','); cout.write(names,comma-names)<<" : "<<arg1<<" | ";
    __f(comma+1,args...);
}
#else
#define trace(...)
#define endl '\n'
#endif

double INF = 1e100;
double EPS = 1e-12;
#define x fst 
#define y snd 
namespace point{
	typedef pair<ld,ld> PT;
	PT conj(PT x) { return PT(x.fst,-x.snd); }
    ld norm(PT x) { return x.fst*x.fst+x.snd*x.snd; }
    ld abs(PT x) { return sqrt(norm(x)); }
	PT operator+(const PT& l, const PT& r) { return PT(l.fst+r.fst,l.snd+r.snd); }
    PT operator-(const PT& l, const PT& r) { return PT(l.fst-r.fst,l.snd-r.snd); }
    PT operator*(const PT& l, const ld& r) { return PT(l.fst*r,l.snd*r); }
    PT operator*(const ld& l, const PT& r) { return r*l; }
    PT operator/(const PT& l, const ld& r) { return PT(l.fst/r,l.snd/r); }
    PT operator*(const PT& l, const PT& r) { return PT(l.fst*r.fst-l.snd*r.snd,l.snd*r.fst+l.fst*r.snd); }
    PT operator/(const PT& l, const PT& r) { return l*conj(r)/norm(r); }
    PT& operator+=(PT& l, const PT& r) { return l = l+r; }
    PT& operator-=(PT& l, const PT& r) { return l = l-r; }
    PT& operator*=(PT& l, const ld& r) { return l = l*r; }
    PT& operator/=(PT& l, const ld& r) { return l = l/r; }
    PT& operator*=(PT& l, const PT& r) { return l = l*r; }
    PT& operator/=(PT& l, const PT& r) { return l = l/r; }
    ld cross(PT a, PT b) { return (conj(a)*b).snd; }
    ld cross(PT p, PT a, PT b) { return cross(a-p,b-p); }
    ld dist(PT p, PT a, PT b) { return std::abs(cross(p,a,b))/abs(a-b); }
    PT rotate(PT a, ld b) { return a*PT(cos(b),sin(b)); }
    PT reflect(PT p, PT a, PT b) { return a+conj((p-a)/(b-a))*(b-a); }
    ld dot(PT p, PT q)     { return p.fst*q.fst+p.snd*q.snd; }
    ld dist2(PT p, PT q)   { return dot(p-q,p-q); }
    
    ostream &operator<<(ostream &os, const PT &p) {return os << "(" << p.fst << "," << p.snd << ")";}
}
 
using namespace point ;

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) { 
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}
 
// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}
 
// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}
 
// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}
 
// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}
 
// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}
 
bool LinesCollinear(PT a, PT b, PT c, PT d) { 
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS; 
}
 
// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}
 
// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}
 
// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
  b=(a+b)/2;
  c=(a+c)/2;
  return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}
 
// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for (int i = 0; i < (int)p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y || 
      p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}
 
// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
  for (int i = 0; i < (int)p.size(); i++)
    if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
      return true;
    return false;
}
 
// position of point P wrt line a----b 
double Pos_wrt_line(PT a , PT b , PT p){
	ld res = ((p.x-a.x)*(b.y-a.y))-((p.y-a.y)*(b.x-a.x));
	return res;
}

PT centroid(const vector<PT>& v) { 
        PT cen(0,0); ld area = 0; // 2*signed area
        for(int i = (sz(v))-1; i >= 0; i--) {
            int j = (i+1)%sz(v); ld a = cross(v[i],v[j]);
            cen += a*(v[i]+v[j]); area += a;
        }
        return cen/area/(ld)3;
}
vector<PT> convex_hull(vector<PT> P) { 
    sort(all(P)); P.erase(unique(all(P)),P.end());
    int n = sz(P); if (n <= 1) return P; 
    vector<PT> bot = {P[0]};
    rep(i,1,n) {
        while (sz(bot) > 1 && cross(bot[sz(bot)-2], bot.back(), P[i]) <= 0) bot.pop_back();
        bot.pb(P[i]);
    }
    bot.pop_back();
    
    vector<PT> up = {P[n-1]};
    for(int i = (n-1)-1; i >= 0; i--) {
        while (sz(up) > 1 && cross(up[sz(up)-2], up.back(), P[i]) <= 0) up.pop_back();
        up.pb(P[i]);
    }
    up.pop_back();
    
    bot.insert(bot.end(),all(up)); return bot;
}


int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
	
	int m ; scan(m);
	vector<PT> wek;
	fr(i,1,m){
		int x , y ;
		scan(x,y);
		PT a(x,y) ;
		wek.pb(a);
	}
	vector<PT> hull = convex_hull(wek);
	print(sz(hull));
	trace(hull);
	for(PT a : hull){
		cout << a.x << " " << a.y << endl;
	}



#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }

