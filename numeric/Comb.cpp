std::vector<Z> fact, ifact;

Z comb(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * ifact[k] * ifact[n-k];
}

void init(int n = 1E6 + 10) {
    fact.resize(n), ifact.resize(n);
    fact[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = i * fact[i - 1];
    }
    ifact.back() = 1 / fact.back();
    for(int i = n - 1; i > 0; i--) {
        ifact[i - 1] = i * ifact[i];
    }
}
