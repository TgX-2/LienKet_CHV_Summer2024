const int maxn = 1e5 + 7;
int n, q, qq[maxn];
bool is[maxn];
array<int, 2> g[maxn];
int ans[maxn];

int child[maxn], par[maxn];
void init() {
	FOR(i, 1, n) {
		par[i] = i;
		child[i] = 1;
	}
}
 
int find(int u) {
	return (u == par[u] ? u : find(par[u]));
}
 
void merge(int a, int b) {
	int u = find(a), v = find(b);
	if (u != v) {
		if (child[u] < child[v]) swap(u, v);
		child[u] += child[v];		
		par[v] = u;
	}
}
 
 
int get(int a, int b) {
	int u = find(a), v = find(b);
	if (u != v) {
		if (child[u] < child[v]) swap(u, v);
		int ans = child[u] * child[v];
		child[u] += child[v];
		par[v] = u;
		return ans;
	}
}
 
 
void process() {
	cin >> n;
	FOR(i, 2, n) {
		int u, v; cin >> u >> v;
		g[i - 1] = {u, v};
	}
 
	cin >> q;
	FOR(i, 1, q) {
		cin >> qq[i];
		is[qq[i]] = 1;
	}
 
	init();
	FOR(i, 1, n - 1) if (!is[i])	
		merge(g[i][0], g[i][1]);
 
 
	FORD(i, q, 1)
		ans[i] = get(g[qq[i]][0], g[qq[i]][1]);
 
	FOR(i, 1, q)
		cout << ans[i] __ ;
 
}
