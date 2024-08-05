const int mod  = 1e9 + 7;
const int maxn = 1e5 + 7;
int n,  f[maxn][207];

int dq(int id, int modd) {
	if (id > n)
		return (modd == 0);

	int &ans = f[id][modd];
	if (ans != -1) return ans;

	ans = 0;
	FOR(i, (id == 1), 9) if (i != 1 and i != 3) {
		ans += dq(id + 1, (modd * 10 + i) % 13);
		ans %= mod;
	}

	return ans;
}

void process() {
	cin >> n;
	memo(f, -1);
	cout << dq(1, 0);
}
