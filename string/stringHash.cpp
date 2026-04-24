std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

const int m1 = findPrime(rng() % 900000000 + 100000000);
const int m2 = findPrime(m1 + 114514);
const int base = 131;

pair<vector<int>, vector<int>> stringHash(string s) {
    int n = s.size();
    s = " " + s;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = (1LL * a[i - 1] * base + int(s[i] - '0')) % m1;
        b[i] = (1LL * b[i - 1] * base + int(s[i] - '0')) % m2;
    }
    return make_pair(a, b);
}