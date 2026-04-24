constexpr int N = 3E6 + 10;

int tot;
int trie[N][75];
int f[N];

int newNode() {
    int x = ++tot;
    fill(trie[x], trie[x] + 75, 0);
    f[x] = 0;
    return x;
}

void insert(string s) {
    int p = 1;
    for (auto c : s) {
        int x = int(c - '0');
        if (!trie[p][x]) {
            trie[p][x] = newNode();
        }
        p = trie[p][x];
        f[p] += 1;
    }
}

int query(string s) {
    int p = 1;
    for (auto c : s) {
        int x = int(c - '0');
        if (!trie[p][x]) {
            return 0;
        }
        p = trie[p][x];
    }
    return f[p];
}