template <typename T>
std::vector<Point<T>> getHull(std::vector<Point<T>> &a) {
    std::sort(a.begin(), a.end(), [&](auto u, auto v) {
        if (u.x != v.x) {
            return u.x < v.x;
        } else {
            return u.y < v.y;
        }
    });
    a.erase(std::unique(a.begin(), a.end()), a.end());
    if (a.size() <= 1) {
        return a;
    }

    std::vector<Point<T>> lo, hi;
    for (auto p : a) {
        while (lo.size() > 1 && cross(lo.back() - lo[lo.size() - 2], p - lo[lo.size() - 2]) <= 0) {
            lo.pop_back();
        }
        while (hi.size() > 1 && cross(hi.back() - hi[hi.size() - 2], p - hi[hi.size() - 2]) >= 0) {
            hi.pop_back();
        }
        lo.push_back(p);
        hi.push_back(p);
    }

    lo.pop_back();
    reverse(hi.begin(), hi.end());
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}