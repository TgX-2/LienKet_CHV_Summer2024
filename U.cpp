const int maxn = 1e5 + 6;
int n, m, a[maxn];
 
int seg[maxn << 2];
void build(int id, int l, int r) {
	if (l == r) return seg[id] = a[l], void();
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
	seg[id] = seg[id << 1] + seg[id << 1 | 1];
}
 
int get(int id, int l, int r, int u, int v) {
	if (v < l or r < u) return 0;
	if (u <= l and r <= v) return seg[id];
	int mid = (l + r) >> 1;
	return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}
 
 
bool check(int tar) {
	FOR(i, 1, n - tar + 1)
		if (get(1, 1, n, i, i + tar - 1) < m) return 0;
	return 1;
}
 
void process() {
	cin >> m >> n;
	FOR(i, 1, n) cin >> a[i];
	build(1, 1, n);
	int l = 1, r = n, ans = n;
	while(l <= r) {	
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
 
	cout << ans;
}
