const int maxn = 1e4 + 7;
const int mod  = 1e9 + 7;
int a[maxn], f[maxn][20][2][2][2][2];
int n;
 
int dp(int id, int modd, bool isless, bool tar, bool is0, bool is1, bool is2) {
	if (id == 0) return (modd == 0);
 
	if (!isless and f[id][modd][tar][is0][is1][is2] != -1)
		return f[id][modd][tar][is0][is1][is2];
 
	int ans = 0;
 
	int lim = (isless == 1 ? a[id] : 9);
	FOR(i, 0, lim) {
		int new_isless, new_tar;
		if (tar == 1) {
			if (i % 3 == 0 and is0 == 1) continue;
			if (i % 3 == 1 and is2 == 1) continue;
			if (i % 3 == 2 and is1 == 1) continue;
		}
 
		if (i > 0 or tar == 1) new_tar = 1;
		else new_tar = 0;
 
		if (isless and i == lim)
			new_isless = 1;
		else new_isless = 0;
 
		if (i % 3 == 0) {
			if (new_tar == 1)
				ans = (ans + dp(id - 1, (modd * 10 + i) % 19, new_isless, new_tar, 1, is1, is2)) % mod;
			else 
				ans = (ans + dp(id - 1, (modd * 10 + i) % 19, new_isless, new_tar, is0, is1, is2)) % mod;
		} else if (i % 3 == 1) 
			ans = (ans + dp(id - 1, (modd * 10 + i) % 19, new_isless, new_tar, is0, 1, is2)) % mod;
		else 
			ans = (ans + dp(id - 1, (modd * 10 + i) % 19, new_isless, new_tar, is0, is1, 1)) % mod;
	}
 
	if (!isless)
		f[id][modd][tar][is0][is1][is2] = ans;
 
	return ans;
}
 
int get(string s, bool is) {
	int id = 0;
	FOR(i, 0, len(s) - 1) {
		id++;
		a[id] = s[i] - '0';
	}
 
	n = id;
	if (is) {
		while(a[id] == 0) {
			a[id] = 9;
			id--;
		}
		a[id]--;
	}
 
	reverse(a + 1, a + 1 + n);
 
	return dp(n, 0, 1, 0, 0, 0, 0);
}
 
void process() {
	memo(f, -1);
	int t; cin >> t;
	while(t--) {
		string l, r; cin >> l >> r;
		cout << (get(r, 0) - get(l, 1) + mod) % mod __ ;
	}
}
