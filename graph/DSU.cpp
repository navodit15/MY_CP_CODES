struct DSU {
	vi e; void init(int n) { e = vi(n,-1); }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); } 
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	bool unite(int x, int y) { // union-by-rank
		x = find(x), y = find(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};
