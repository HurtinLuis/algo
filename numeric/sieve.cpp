std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i * i <= n; i++) {
        if (minp[i] == 0) {
            for (int j = i * i; j <= n; j += i) {
                if (minp[j] == 0) {
                    minp[j] = i;
                }
            }
        }
    }
    primes.clear();
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
    }
}

bool isPrime(int x) {
    return x == minp[x];
}