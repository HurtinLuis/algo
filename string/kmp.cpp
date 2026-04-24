vector<int> kmp(string s) {
    int n = s.size();
    s = " " + s;
    vector<int> next(n + 1);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) {
            j = next[j];
        }
        j += (s[i] == s[j + 1]);
        next[i] = j;
    }
    return next;
}