std::vector<Z> fact, ifact;

void init() {
    const int n = 1E6 + 1;
    fact.resize(n); ifact.resize(n);
    fact[0] = 1;
    for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i;
    ifact.back() = 1 / fact.back();
    for (int i = n - 1; i > 0; i--) ifact[i - 1] = ifact[i] * i;
}

Z comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] * ifact[n - k];
}