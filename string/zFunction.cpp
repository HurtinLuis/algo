vector<int> zFunction(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    for (int i = 1, l = 1, r = 0; i < n; i++) {
        int len = (i > r ? 0 : std::min(r - i + 1, z[i - l]));
        while (i + len < n && s[len] == s[i + len]) {
            len++;
        }
        z[i] = len;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}