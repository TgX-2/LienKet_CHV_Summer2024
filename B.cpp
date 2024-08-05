const int maxn = 1e5 + 7;
int n, m, ans[maxn];
vector<int> g[maxn];

int par[maxn];
void dfs(int u, int pre) {
	par[u] = pre;
	for(int v : g[u]) if (v != pre) 
		dfs(v, u);
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
	}

	dfs(1, -1);
	LCA lca(n);

	while(m--) {
		int u, v; cin >> u >> v;
		int k = lca.lca(u, v);

		int cur = u;
		while(cur != k) {
			ans[cur]++;
			cur = par[cur];
		}

		cur = v;
		while(cur != k) {
			ans[cur]++;
			cur = par[cur];
		}
	}

	int res = 0;
	FOR(i, 1, n)
		maxi(res, ans[i]);

	cout << res;
}
