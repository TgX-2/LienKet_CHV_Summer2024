const int maxn = 107;
int n, m, a[maxn], b[maxn];
int f[maxn][maxn][maxn] ;
 
int dq(int i, int j, int pre) {
	if (i > n or j > m) return 0;
 
	int &ans = f[i][j][pre];
	if (ans != -1) return ans;
 
	ans = 0;
	if (a[i] == b[j] and a[i] > a[pre]) 
		maxi(ans, dq(i + 1, j + 1, i) + 1);
	
	maxi(ans, dq(i + 1, j + 1, pre));	
	maxi(ans, dq(i + 1, j, pre));
	maxi(ans, dq(i, j + 1, pre));
 
	return ans;
}
 
void process() {
	cin >> n >> m;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, m) cin >> b[i];
 
	memo(f, -1);
	cout << dq(1, 1, -1);
}
 
