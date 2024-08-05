const int mod = 1e9 + 7;
 
int n;
string s;
 
const int maxn = 1e5 + 7;
int f[maxn];
 
int dp(int id) {
	if (id > n) return 1;
 
	int &ans = f[id];
	if (ans != -1) return ans;
	ans = 0;
	ans = (ans + dp(id + 1)) % mod;
	if (s[id] != s[id + 1] and id != n)
		ans = (ans + dp(id + 2)) % mod;
	else {
	}
	return ans;
 
}
 
void process() {
	cin >> s;
	n = len(s); s = " " + s;
	memo(f, -1);
	cout << dp(1);
}
