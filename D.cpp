const int maxn = 2e5 + 7;
vector<int> b[maxn];
int id[maxn];

void pre() {
    FOR(i, 1, 1000) id[i ^ (i >> 1)] = i;
    FOR(i, 0, 2000) FOR(j, 0, 9)
        if (BIT(j, i) and id[i] != 0)
            b[j].pb(id[i]);
}

void process() {
    pre();
    int q; cin >> q;
    while(q--) {
        FOR(i, 0, 9) {
            cout << len(b[i]) << " ";
            for(auto val : b[i]) cout << val << " ";
            cout << "\n";
            flush(cout);
        }

        string s; cin >> s;
        int ans = 0;
        FOR(i, 0, len(s) - 1) {
            if (s[i] == '+')
                ans += (1 << i);
        }
        cout << id[ans] __ ;
        flush(cout);
    }
}
