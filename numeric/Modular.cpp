// ------------------------- Modular -------------------------
template<typename T>
T power(T a, i64 b) {
    T res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

template<i64 M>
struct Modular {
    i64 x;
    Modular() : x(0) {}
    Modular(i64 y) : x(normalize(y % M)) {}

    i64 normalize(i64 y) {
        if (y < 0) {
            y += M;
        }
        if (y >= M) {
            y -= M;
        }
        return y;
    }
    explicit operator i64() const {
        return x;
    }
    Modular inv() const {
        return power(Modular(x), M - 2);
    }

    Modular operator-() const {
        Modular res;
        res.x = normalize(-x);
        return res;
    }
    Modular& operator+=(Modular rhs) {
        x = normalize(x + rhs.x);
        return *this;
    }
    Modular& operator-=(Modular rhs) {
        x = normalize(x - rhs.x);
        return *this;
    }
    Modular& operator*=(Modular rhs) {
        x = x * rhs.x % M;
        return *this;
    }
    Modular& operator/=(Modular rhs) {
        return *this *= rhs.inv();
    }

    friend Modular operator+(Modular lhs, const Modular& rhs) {
        return lhs += rhs;
    }
    friend Modular operator-(Modular lhs, const Modular& rhs) {
        return lhs -= rhs;
    }
    friend Modular operator*(Modular lhs, const Modular& rhs) {
        return lhs *= rhs;
    }
    friend Modular operator/(Modular lhs, const Modular& rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(const Modular& lhs, const Modular& rhs) {
        return lhs.x == rhs.x;
    }
    friend bool operator!=(const Modular& lhs, const Modular& rhs) {
        return lhs.x != rhs.x;
    }

    friend std::istream& operator>>(std::istream& is, Modular& a) {
        i64 v;
        is >> v;
        a = Modular(v);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Modular& a) {
        return os << a.x;
    }
};

template <i64 M>
std::string to_string(const Modular<M>& number) {
    return std::to_string(i64(number));
}

constexpr i64 mod = 998244353;
using Z = Modular<mod>;
