// ------------------------- LazySegmentTree -------------------------
template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;

    LazySegmentTree(int n_, Info v = Info()) {
        init(std::vector(n_, v));
    }

    template<class T>
    LazySegmentTree(std::vector<T> a) {
        init(a);
    }

    template<class T>
    void init(std::vector<T> a) {
        n = a.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        auto build = [&](auto &&self, int p, int l, int r) {
            if (r - l == 1) {
                info[p] = a[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }
    
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        if (tag[p].lazy != 0) {
            apply(2 * p, tag[p]);
            apply(2 * p + 1, tag[p]);
            tag[p] = Tag();
        }
    }

    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }

    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }

    Info query(int l, int r) {
        return query(1, 0, n, l, r + 1);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r + 1, v);
    }
};

struct Tag {
    int x = 0;
    int lazy = 0;
    void apply(const Tag &t) & {
        x = t.x;
        lazy = 1;
    }
};

struct Info {
    int sum = 0;
    int cnt = 1;
    void apply(const Tag &t) & {
        sum = t.x * cnt;
    }
};

Info operator+(const Info &l, const Info &r) {
    return {l.sum + r.sum, l.cnt + r.cnt};
}
