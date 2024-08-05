void process() {
	int n; cin >> n;
	vector<int> neg;
	int sum = 0, cnt = 0, ans = 0;
	int sumn = 0;
	FOR(i, 1, n) {
		int x; cin >> x;
		if (x < 0) {
			neg.pb(x);
			sumn += x;
		} else {
			cnt++;
			sum += x;
		}
	}
	sort(all(neg), greater<int>());
	ans = sumn + (cnt * sum);
 
	for(int val : neg) {
		int curs = sum + val, curc = cnt + 1, curn = sumn - val;
		int curv = curn + (curs * curc);
		if (curv >= ans) {
			ans = curv;
			sum = curs;
			cnt = curc;
			sumn = curn;
		}
	}
	cout << ans;
}
