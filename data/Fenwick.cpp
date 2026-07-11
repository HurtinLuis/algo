template <class T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        a.assign(n + 1, T{});
    }

    void add(int x, const T &v) {
        assert(0 <= x && x < n);
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i] = a[i] + v;
        }
    }

    T sum(int x) {
        assert(0 <= x && x <= n);
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i];
        }
        return ans;
    }

    T query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }

    // returns the longest prefix length x such that sum(x) <= k.
    int maxPrefix(const T &k) {
        T cur{};
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i >>= 1) {
            if (x + i <= n && cur + a[x + i] <= k) {
                cur = cur + a[x + i];
                x += i;
            }
        }
        assert(0 <= x && x <= n);
        return x;
    }
};