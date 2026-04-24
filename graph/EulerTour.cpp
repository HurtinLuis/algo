template <class T>
auto EulerTour(const vector<vector<T>>& g, int s) {
    vector<int> head(g.size());
    vector<int> res;
    auto dfs = [&](auto &&self, int x) -> void {
        while (head[x] < g[x].size()) {
            int to = g[x][head[x]++];
            self(self, to);
        }
        res.push_back(x);
    };
    dfs(dfs, s);
    reverse(res.begin(), res.end());
    return res;
};