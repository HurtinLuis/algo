constexpr i64 inf = 1E18;

struct Tag {
    i64 add = 0;
    i64 mul = 1;
    int lazy = 0;
    void apply(const Tag &t) & {
        mul *= t.mul;
        add = add * t.mul + t.add;
        lazy = 1;
    }
};

struct Info {
    i64 sum = 0;
    int len = 0;
    i64 max = -inf;
    i64 min = inf;
    void apply(const Tag &t) & {
        sum = sum * t.mul + t.add * len;
        max = std::max(max * t.mul, min * t.mul) + t.add;
        min = std::min(max * t.mul, min * t.mul) + t.add;
    }
};

Info operator+(const Info &l, const Info &r) {
    return {l.sum + r.sum, l.len + r.len, std::max(l.max, r.max), std::min(l.min, r.min)};
}