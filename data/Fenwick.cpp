template <class T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n = 0) : n(n), a(n + 1, T{}) {}

    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] += v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i];
        }
        return ans;
    }

    T query(int l, int r) { return sum(r) - sum(l - 1); }
};