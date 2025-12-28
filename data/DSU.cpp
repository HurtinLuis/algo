struct DSU {
    std::vector<int> f, siz;

    DSU(int n) : f(n), siz(n, 1) {
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        f[y] = x;
        siz[x] += siz[y];
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    int size(int x) { return siz[find(x)]; }
};