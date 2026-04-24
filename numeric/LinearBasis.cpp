struct LinearBasis {
    const int N = 32;
    vector<int> p;
    vector<int> from;
    vector<int> mask;

    LinearBasis() : p(N), from(N, -1), mask(N) {}

    bool insert(int x, int id) {
        int pick = 0;
        for (int i = N - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (p[i] == 0) {
                    p[i] = x;
                    from[i] = id;
                    mask[i] = pick | (1 << i);
                    return true;
                } else {
                    x ^= p[i];
                    pick ^= mask[i];
                }
            }
        }
        return false;
    }

    bool calc(int tar, vector<int> a, vector<int> &ans) {
        int pick = 0;
        for (int i = N - 1; i >= 0; i--) {
            if (tar >> i & 1) {
                if (p[i] == 0) {
                    return false;
                }
                tar ^= p[i];
                pick ^= mask[i];
            }
        }
        for (int i = 0; i < N; i++) {
            if (pick >> i & 1) {
                int id = from[i];
                if (id != -1) {
                    ans[id] = a[id];
                }
            }
        }
        return true;
    }
};