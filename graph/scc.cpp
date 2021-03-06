/**
 * Description: Tarjan's, DFS once to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 	* Uses less memory than Kosaraju b/c doesn't store reverse edges.
 * Time: O(N+M)
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
 * Verification: https://cses.fi/problemset/task/1686/
 */

struct SCC {
	int N, ti = 0; vector<vi> adj;
	vi disc, comp, st, comps;
	void init(int _N) { N = _N; adj.resize(N), disc.resize(N), comp = vi(N,-1); }
	void ae(int x, int y) { adj[x].pb(y); }
	int dfs(int x) {
		int low = disc[x] = ++ti; st.pb(x); // disc[y] != 0 -> in stack
		trav(y,adj[x]) if (comp[y] == -1) chkmin(low,disc[y]?:dfs(y)); 
		if (low == disc[x]) { // make new SCC, pop off stack until you find x
			comps.pb(x); for (int y = -1; y != x;) 
				comp[y = st.bk] = x, st.pop_back();
		}
		return low;
	}
	void gen() {
		rep(i,0,N) if (!disc[i]) dfs(i);
		reverse(all(comps));
	}
}