template <class T>
auto CartesianTree(const vector<T> &as, int gr = 0) {
    int n = as.size();
    vector<int> ls(n, -1), rs(n, -1), stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && ((as[i] < as[stk.back()]) ^ gr)) {
            ls[i] = stk.back();
            stk.pop_back();
        }
        if (!stk.empty()) rs[stk.back()] = i;
        stk.push_back(i);
    }
    return make_tuple(stk[0], ls, rs);
}