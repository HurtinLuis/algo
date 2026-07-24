constexpr int mod = 998244353;

struct Z {
    i64 x;
    Z(i64 y = 0) : x(y % mod) { if (x < 0) x += mod; }
    Z operator+(const Z &o) const { return Z(x + o.x); }
    Z operator-(const Z &o) const { return Z(x - o.x); }
    Z operator*(const Z &o) const { return Z(x * o.x); }
};

Z power(Z a, int b) {
    Z res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

using poly = std::vector<Z>;

void fft(poly &a, bool invert = false) {
    int n = a.size();
    assert((mod - 1) % n == 0);
    poly b(n);
    for (int d = n / 2; d; d /= 2, std::swap(a, b)) {
        Z w = power(Z(3), (mod - 1) / n * d), m = 1;
        for (int i = 0; i < n; i += d * 2, m = m * w) {
            for (int j = 0; j < d; j++) {
                Z u = a[i + j], v = a[i + j + d] * m;
                b[i / 2 + j] = u + v;
                b[i / 2 + j + n / 2] = u - v;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        Z inv = power(n, mod - 2);
        for (auto& t : a) t = t * inv;
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
        a[i] = a[i] * b[i];
    }
    fft(a, true), a.resize(m);
    return a;
}
