const int maxn = 1e6 + 7;
int n, k, tmp[maxn];
pair<int, int> a[maxn];

int par[maxn], child[maxn];
void dsu_make() {
	FOR(i, 1, n) {
		par[i] = i;
		child[i] = 1;
	}
}

int dsu_find(int u) {
	return (u == par[u] ? u : par[u] = dsu_find(par[u]));
}

bool dsu_merge(int a, int b) {
	int u = dsu_find(a);
	int v = dsu_find(b);
	if (u != v) {
		if (child[u] < child[v]) swap(u, v);
		child[u] += child[v];
		par[v] = u;
		return 1;
	} else return 0;
}

int bit[maxn];
void bit_upd(int id) {
	for(; id <= n; id += id & (-id))
		bit[id]++;
}

int bit_get(int id) {
	int ans = 0;
	for(; id > 0; id -= id & (-id))
		ans += bit[id];
	return ans;
}


bool vis[maxn];
array<int, 4> dd[maxn];
vector<array<int, 3>> v;

void process() {
	cin >> n >> k;
	FOR(i, 1, n) {
		cin >> a[i].fi;
		a[i].se = i;
		tmp[i] = a[i].fi;
	}

	sort(a + 1, a + 1 + n, [](const pair<int, int> &a, const pair<int, int> &b) {
		return a.fi > b.fi;
	});

	dsu_make();

	FOR(i, 1, n) {
		int id = a[i].se;
		vis[id] = 1;
		if (vis[id - 1] and vis[id + 1]) {
			int l = dsu_find(id - 1);
			int r = dsu_find(id + 1);

			if (child[l] < child[r]) {
				FOR(j, id - child[l], id) 
					v.pb({id, id + child[r], k - tmp[j] - a[i].fi});
			} else {
				FOR(j, id, id + child[r])
					v.pb({id - child[l], id, k - tmp[j] - a[i].fi});
			}

			dsu_merge(id, id + 1);
			dsu_merge(id, id - 1);
		} else if (vis[id - 1]) {
			int l = dsu_find(id - 1);
			v.pb({id - child[l], id, k - 2 * a[i].fi});
			dsu_merge(id, id - 1);
		} else if (vis[id + 1])  {
			int r = dsu_find(id + 1);
			v.pb({id, id + child[r], k - 2 * a[i].fi});
			dsu_merge(id, id + 1);
		} else v.pb({id, id, k - 2 * a[i].fi});
	}

	int lenn = len(v);
	FOR(i, 0, lenn - 1)
		dd[i + 1] = {v[i][0], v[i][1], v[i][2], i + 1};
	sort(dd + 1, dd + 1 + lenn, [](const array<int, 4> &a, const array<int, 4> &b) {
		return a[2] < b[2];
	});


	int id = n, ans = 0;
	FOR(i, 1, lenn) {
		while(id >= 1 and a[id].fi <= dd[i][2]) bit_upd(a[id--].se);
		ans += bit_get(dd[i][1]) - bit_get(dd[i][0] - 1);
	}

	cout << ans;
}
