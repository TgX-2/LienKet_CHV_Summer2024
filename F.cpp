const int maxn = 1e5 + 7;
int n, m;
vector<int> g[maxn];
pair<int, int> e[maxn];
 
int sta[maxn], fin[maxn], cnt = 0, par[maxn];
void dfs(int u, int pre) {
	par[u] = pre;
	sta[u] = ++cnt;
	for(int v : g[u]) if (v != pre) 
		dfs(v, u);
	fin[u] = cnt;
}
 
int lazy[maxn << 2], seg[maxn << 2];
 
void down(int id) {
	int x = lazy[id];
	seg[id << 1] += x;
	seg[id << 1 | 1] += x;
	lazy[id << 1] += x;
	lazy[id << 1 | 1] += x;
	lazy[id] = 0;
}
 
void update(int id, int l, int r, int u, int v, int val) {
	if (v < l or r < u) return;
	if (u <= l and r <= v) {
		seg[id] += val;
		lazy[id] += val;
		return;
	}
 
	down(id);
	int mid = (l + r) >> 1;
	update(id << 1, l, mid, u, v, val);
	update(id << 1 | 1, mid + 1, r, u, v, val);
	seg[id] = seg[id << 1] + seg[id << 1 | 1];
}
 
int get(int id, int l, int r, int u, int v) {
	if (v < l or r < u) return 0;
	if (u <= l and r <= v) return seg[id];
	down(id);
	int mid = (l + r) >> 1;
	return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}
 
struct LCA {
    vector<int> euler, h, d;
    vector<vector<int>> st;
    int timer = 0;
 
    void dfs(int u, int cnt) {
        d[u] = euler.size();
        euler.push_back(u);
        h[u] = cnt;
        for (int v : g[u]) {
            if (h[v] == -1) {
                dfs(v, cnt + 1);
                euler.push_back(u); 
            }
        }
    }
 
    #define mmin(x, y) (h[x] < h[y]) ? x : y
 
    void buildSparseTable() {
        int m = euler.size();
        st.assign(m, vector<int>(20));
 
        for (int i = 0; i < m; i++) 
            st[i][0] = euler[i];
 
        for (int j = 1; (1 << j) <= m; j++) 
            for (int i = 0; i + (1 << j) - 1 < m; i++) 
                st[i][j] = mmin(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
 
    }
 
    int query(int l, int r) {
        int j = __lg(r - l + 1);
        return mmin(st[l][j], st[r - (1 << j) + 1][j]);
    }
 
    int lca(int u, int v) {
        int left = d[u];
        int right = d[v];
        if (left > right) swap(left, right);
        return query(left, right);
    }
 
    LCA(int n) : h(n + 7, -1), d(n + 7) {
        dfs(1, 0);
        buildSparseTable();
    }
};
 
void process() {
	cin >> n >> m;
	FOR(i, 2, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
		e[i - 1] = {u, v};
	}
 
	dfs(1, -1);
	LCA lca(n);=
 
	while(m--) {
		int typ; cin >> typ;
		if (typ == 1) {
			int u, v; cin >> u >> v;
			int k = lca.lca(u, v);
 
			update(1, 1, n, sta[u], sta[u], 1);
			update(1, 1, n, sta[v], sta[v], 1);
			update(1, 1, n, sta[k], sta[k], -2);
		} else {
			int x; cin >> x;
			int u = e[x].fi, v = e[x].se;
			if (u == par[v])
				cout << get(1, 1, n, sta[v], fin[v]) __ ;
			else
				cout << get(1, 1, n, sta[u], fin[u]) __ ;
		}
	}
 
}
 
