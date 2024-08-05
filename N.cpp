int n, k;
 
const int maxn = 1e5 + 7;
int f[maxn][3];
 
int dp(int id, int pre) {
	if (id > n) return 1;
	int &ans = f[id][pre];
	if (ans != -1) return ans;
 
	ans = 0;
	for(int i : {0, 1}) if ((i and pre) == 0) 
		ans += dp(id + 1, i);
 
	return ans;
}
 
int chose[maxn];
void get(int id, int pre) {
	if (id > n) return;
 
	for(int i :  {0, 1}) if ((i and pre) == 0) {
		int w = dp(id + 1, i);
		if (w < k) k -= w;
		else {
			chose[id] = i;
			get(id + 1, i);
			break;
		}
	}
}
 
/* 40 : 267914296 */
 
void process() {
	cin >> n >> k;
	memo(f, -1);
    
	chose[1] = -1;
	get(1, 0);
	if (chose[1] == -1) return cout << "-1", void();
	FOR(i, 1, n)
		cout << chose[i];
}
