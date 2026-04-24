template <class T>
struct Fenwick2D {
    int n, m;
    std::vector<std::vector<T>> a;

    Fenwick2D(int n = 0, int m = 0) : n(n), m(m) {
        a.assign(n + 1, std::vector<T>(m + 1));
    }

    void add(int x, int y, const T &v) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                a[i][j] += v;
            }
        }
    }

    T sum(int x, int y) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                ans += a[i][j];
            }
        }
        return ans;
    }

    T query(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};