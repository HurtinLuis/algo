// ------------------------- Polynomial -------------------------
constexpr int mod = 998244353;

int add(int x, int y) { x += y; return x >= mod ? x - mod : x; }
int sub(int x, int y) { x -= y; return x < 0 ? x + mod : x; }
int mul(int x, int y) { return 1LL * x * y % mod; }

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int inv(int a) { return power(a, mod - 2); }

using poly = std::vector<int>;

void fft(poly &a, bool invert = false) {
    int n = a.size();
    assert((mod - 1) % n == 0);
    poly b(n);
    for (int d = n / 2; d; d /= 2, std::swap(a, b)) {
        int w = power(3, (mod - 1) / n * d), m = 1;
        for (int i = 0; i < n; i += d * 2, m = mul(m, w)) {
            for (int j = 0; j < d; j++) {
                int u = a[i + j], v = mul(a[i + j + d], m);
                b[i / 2 + j] = add(u, v);
                b[i / 2 + j + n / 2] = sub(u, v);
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        int z = inv(n);
        for (auto& t : a) t = mul(t, z);
    }
}

poly convolution(poly a, poly b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    int n = 1, m = a.size() + b.size() - 1;
    while (n < m) {
        n *= 2;
    }
    a.resize(n), fft(a);
    b.resize(n), fft(b);
    for (int i = 0; i < n; i++) {
        a[i] = mul(a[i], b[i]);
    }
    fft(a, true), a.resize(m);
    return a;
}