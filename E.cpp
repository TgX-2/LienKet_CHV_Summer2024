const int maxn = 1e4 + 7;
const int mod  = 1e9 + 7;
int a[maxn];
int f[maxn][15][20][3][3];
long long dp(int id, int pre, int modd, bool isless, bool islead) {
	if (id < 0) {
		return (modd == 0 and islead);
	} 
 
	int &ans = f[id][pre][modd][isless][islead];
	if (ans != -1) return ans;
 
	ans = 0;
	if (isless) {
		FOR(i, 0, 9) if (i != pre or (islead == 0 and i == 0 and i == pre)) {
			ans += dp(id - 1, i, (modd * 10 + i) % 17, isless, islead | (i != 0));
			ans %= mod;
		}
	} else {
		int lim = a[id];
		FOR(i, 0, lim) if (i != pre or (islead == 0 and i == 0 and i == pre)) {
			ans += dp(id - 1, i, (modd * 10 + i) % 17, i < lim, islead | (i != 0));
			ans %= mod;
		}
	}
	return ans;
}
 
long long get(string s) {
	int id = 0;
	FORD(i, len(s) - 1, 0) {
		a[id] = s[i] - '0';
		id++;	
	}
	memo(f, -1);
	return dp(len(s) - 1, 11, 0, 0, 0);
}
 
void process() {
	string l, r; cin >> l >> r;
 
	int modd = 0;
	FOR(i, 0, len(l) - 1) {
		if (i != 0) {
			if (l[i] == l[i - 1]) {
				modd = 100;
				break;
			}
		}
		modd = (modd * 10 + (l[i] - '0')) % 17;
	}
 
	int ans = (modd == 0);
	ans += (get(r) - get(l) + mod) % mod;
	cout << ans;
}
