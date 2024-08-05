const int maxn = 1e3 + 7;
const int mod  = 1e9 +  7;
string s;
int n, a[maxn];

int f[maxn][maxn], vis[maxn][maxn], cur = 0;
int count(int id, int sum, int lim) {
	if(id<1)
		return (sum==0);
    
	if(sum < 0)return 0;
	if(!lim and f[id][sum] != -1)
        return f[id][sum];
    
	int c, res=0;
	if(lim==1) c = a[id];
	else c = 2;
    FOR(i, 1, c) {
        int new_lim  = 0;
        if(lim == 1 and i == c) new_lim = 1;
        else new_lim = 0;
        
        if (i == 1)
            res += count(id - 1, sum + 1, new_lim);
        else res += count(id - 1, sum - 1, new_lim);
        res %= mod;

    }
	if(!lim) f[id][sum]=res;
	return res;
}
 
int get(string x) {
	int cnt = 0;
	FOR(i, 1, n) {
    	if(s[i] == '(') a[++cnt] = 1;
    	else a[++cnt] = 2;
    }
    reverse(a + 1, a + 1 + n);
    return count(n, 0, 1);
}
 
void process() {
	int t; cin >> t;
    memo(f,-1);
	while(t--) {
		cin >> s; n = len(s); s = " " + s;
		cout << get(s) __ ;
	}
}
