const int maxn = 1007;
int n, b[maxn];
bool a[maxn][maxn];
 
void process() {
	cin >> n;
	FOR(i, 1, n) FOR(j, 1, n)
		cin >> a[i][j];
 
	iota(b + 1, b + 1 + n, 1);
	FOR(i, 1, n - 1) FOR(j, 2, n) {
		if (a[b[j]][b[j - 1]]) swap(b[j], b[j - 1]);
	}
 
	cout << n __ ;
	FOR(i, 1, n)
		cout << b[i] << " ";
}
