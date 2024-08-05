const int maxn = 1e3 + 7;
const int mod  = 1e9 +  7;
string s;
int n;
 
int f[maxn][maxn];
int count(int id, int cnt) {
	if (id > n) return (cnt == 0);
 
	int &ans = f[id][cnt];
	if (ans != -1) return ans;
 
	ans = 0;
	ans += count(id + 1, cnt + 1);
	ans %= mod;
	if (cnt != 0) {
		ans += count(id + 1, cnt - 1);
		ans %= mod;
	}
 
	return ans;
}
 
int ans = 0;
void get(int id, int cnt) {
	if (id > n) return;
 
	for(int i : {0, 1})  {
		if ((i == 0 and s[id] == '(') or (i == 1 and s[id] == ')')) {
			get(id + 1, cnt + (i == 0 ? 1 : -1));
			break;
		}
 
		if (cnt != 0 and i == 1) {
			int x = count(id + 1, cnt - 1);
			ans += x;
			ans %= mod;
		}
 
		if (i == 0) {
			int x = count(id + 1, cnt + 1);
			ans += x;
			ans %= mod;
		}
 
	}
}
 
void process() {
	cin >> s; n = len(s); s = " " + s;
	memo(f, -1);
	get(1, 0);
	cout << ans + 1;
}
